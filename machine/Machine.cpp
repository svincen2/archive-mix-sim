#include "Instruction.h"
#include "Machine.h"
#include "Op_code.h"
#include <fstream>

namespace mix
{
	/* Constant definitions. */
	const unsigned int Machine::MEM_SIZE{4000};
	const unsigned int Machine::NUM_INDEX_REGISTERS{6};

	/*
	* Construct a mix machine.
	*/
	Machine::Machine()
		: pc{0},
		  overflow{Bit::Off},
		  compare{Comparison_value::Equal},
		  jump{},
		  accum{},
		  exten{},
		  index(NUM_INDEX_REGISTERS),
		  memory(MEM_SIZE),
		  instruction_buffer{},
		  content_buffer{},
		  load_ops{},
		  store_ops{},
		  ops{}
	{
		init_load_ops();
		init_store_ops();
		init_ops();
	}

	/*
	* Initialize operations.
	*/
	void Machine::init_ops()
	{
		ops[Op_class::LOAD] = &Machine::execute_load;
		ops[Op_class::LOAD_NEG] = &Machine::execute_load_negative;
		ops[Op_class::STORE] = &Machine::execute_store;
	}

	/*
	* Initialize load operations map.
	*/
	void Machine::init_load_ops()
	{
		load_ops[Op_code::LDA] = [this](){ accum = content_buffer; };
		load_ops[Op_code::LD1] = [this](){ index[0] = content_buffer; };
		load_ops[Op_code::LD2] = [this](){ index[1] = content_buffer; };
		load_ops[Op_code::LD3] = [this](){ index[2] = content_buffer; };
		load_ops[Op_code::LD4] = [this](){ index[3] = content_buffer; };
		load_ops[Op_code::LD5] = [this](){ index[4] = content_buffer; };
		load_ops[Op_code::LD6] = [this](){ index[5] = content_buffer; };
		load_ops[Op_code::LDX] = [this](){ exten = content_buffer; };
	}

	/*
	* Initialize store operations map.
	*/
	void Machine::init_store_ops()
	{
		store_ops[Op_code::STA] = [this](){ buffer_reg_content(accum); };
		store_ops[Op_code::ST1] = [this](){ buffer_reg_content(index[0]); };
		store_ops[Op_code::ST2] = [this](){ buffer_reg_content(index[1]); };
		store_ops[Op_code::ST3] = [this](){ buffer_reg_content(index[2]); };
		store_ops[Op_code::ST4] = [this](){ buffer_reg_content(index[3]); };
		store_ops[Op_code::ST5] = [this](){ buffer_reg_content(index[4]); };
		store_ops[Op_code::ST6] = [this](){ buffer_reg_content(index[5]); };
		store_ops[Op_code::STX] = [this](){ buffer_reg_content(exten); };
		store_ops[Op_code::STJ] = [this](){ buffer_reg_content(jump); };
	}

	/*
	* Read the necessary number of bytes from the rightmost bytes of
	* the given register, left shifting if necessary into the field
	* specified by the instruction in the instruction buffer.
	* Parameters:
	*	reg - Register to get contents.
	*/
	void Machine::buffer_reg_content(const Word& reg)
	{
		Field_spec field{get_field_spec(instruction_buffer)};
		if (field.contains_sign()) {
			content_buffer = reg.rightmost_with_sign(field.bytes());
		}
		else {
			content_buffer = reg.rightmost_bytes(field.bytes());
		}
		int shift_amount{static_cast<int>(Word::num_bytes) - field.right};
		content_buffer.shift_left(shift_amount);
	}

	/*
	* Start the machine with the given arguments.
	* Parameters:
	*	args - Machine arguments.
	*/
	void Machine::start(std::vector<std::string>& args)
	{
		check_arguments(args);
		std::ifstream program_file{args[0]};
		load_program(&program_file);
		run_program();
	}

	/*
	* Check the machine arguments.
	* Parameters:
	*	args - Machine arguments.
	*/
	void Machine::check_arguments(const std::vector<std::string>& args) const
	{
		if (args.size() < 1) {
			throw std::invalid_argument{"Expected at least 1 argument"};
		}
	}

	/*
	* Loads a program into memory.
	* Parameters:
	*	filename - Name of program file.
	*/
	void Machine::load_program(std::istream* program)
	{
		check_program_input_stream(program);
		int curr_address{0};
		Word next_instruction{};
		while (*program) {
			*program >> next_instruction;
			if (!next_instruction.is_valid()) {
				throw Invalid_basic_word{};
			}
			memory[curr_address++] = next_instruction;
			if (program->peek() == EOF) {
				break;
			}
		}
	}

	/*
	* Check the program file.
	* If the file cannot be opened, throws an exception.
	* If the file is empty, throws an exception.
	*/
	void Machine::check_program_input_stream
			(std::istream* program_input_stream) const
	{
		if (program_input_stream->fail()) {
			throw std::invalid_argument{"Cannot read program"};
		}
		if (program_input_stream->peek() == EOF) {
			throw std::invalid_argument{"Program file is empty"};
		}
	}

	/*
	* Runs the program currently loaded in memory.
	*/
	void Machine::run_program()
	{

	}

	/*
	* Execute the next instruction.
	*/
	void Machine::execute_next_instruction()
	{
		// Fetch next instruction and increment program counter.
		instruction_buffer = memory_cell(pc++);

		// Decode.
		Op_code op_code{get_op_code(instruction_buffer)};
		Op_class op_class{get_op_class(op_code)};

		// Execute.
		Base_operation base_op = ops[op_class];
		(this->*base_op)(op_code);
	}

	/*
	* Return the class of operation, such as LOAD or STORE.
	* Parameters:
	*	op_code - Operation code.
	*/
	Op_class Machine::get_op_class(Op_code op_code) const
	{
		Op_class op_class{};
		if (op_code < Op_code::LDAN) {
			op_class = Op_class::LOAD;
		}
		else if (op_code < Op_code::STA) {
			op_class = Op_class::LOAD_NEG;
		}
		else if (op_code <= Op_code::STJ) {
			op_class = Op_class::STORE;
		}
		return op_class;
	}

	/*
	* Execute the load operation specified by the given instruction.
	* Parameters:
	*	op - Operation code.
	*/
	void Machine::execute_load(Op_code op)
	{
		int address{read_address(instruction_buffer)};
		Field_spec field{get_field_spec(instruction_buffer)};
		content_buffer = memory_contents(address, field);
		load_ops[op]();
	}

	/*
	* Execute the load negative operation specified by the given
	* instruction.
	* Parameters:
	*	op - Operation code.
	*/
	void Machine::execute_load_negative(Op_code op)
	{
		int address{read_address(instruction_buffer)};
		Field_spec field{get_field_spec(instruction_buffer)};
		content_buffer = memory_contents(address, field);
		if (field.contains_sign()) {
			content_buffer.negate();
		}
		// Offset into regular load ops range.
		op = static_cast<Op_code>(op - Op_code::LDA);
		load_ops[op]();
	}

	/*
	* Execute the store operation specified by the given instruction.
	* Parameters:
	*	op - Operation code.
	*/
	void Machine::execute_store(Op_code op)
	{
		store_ops[op](); // Store the content of the desired register.
		int address{read_address(instruction_buffer)};
		Field_spec field{get_field_spec(instruction_buffer)};
		memory[address].copy_range(content_buffer, field);
	}

	/*
	* Read the address from the given instruction.
	* If the instruction specifies an index, offset by the
	* contents of the specified index register.
	* Parameters:
	*	instruction - Instruction to read address from.
	*/
	int Machine::read_address(const Word& instruction) const
	{
		int address{get_address(instruction)};
		int index_spec{get_index_spec(instruction)};
		if (index_spec != 0) {
			address += get_address(index_register(index_spec));
		}
		return address;
	}

	/*
	* Get the contents of the given field of the memory cell
	* at the given address.
	* Parameters:
	*	address - Address of memory cell.
	*	field - Field of memory cell to get.
	*/
	const Word Machine::memory_contents(int address,
										const Field_spec& field) const
	{
		return memory_cell(address).field_aligned_right(field);
	}

	/*
	* Load the index register specified by the given register number
	* with the given half word.
	* Parameters:
	*	register_num - Index register number, in range [1, 6].
	*	hw - Half word to load.
	*/
	void Machine::load_index_register(int register_num, const Half_word& hw)
	{
		check_index_register_number(register_num);
		index[register_num - 1] = hw;
	}

	/*
	* Check that the index register number is in range [1, 6].
	* Parameters:
	*	num - Index register numbers.
	*/
	void Machine::check_index_register_number(int num) const
	{
		if (num < 1 || NUM_INDEX_REGISTERS < num) {
			throw std::invalid_argument{"Invalid index register number"};
		}
	}

	/*
	* Dumps the contents of memory into the given stream.
	*/
	void Machine::dump_memory(std::ostream* stream) const
	{
		for (int i = 0; i < MEM_SIZE; ++i) {
			*stream << memory[i];
		}
	}

	/*
	* Returns the contents of the index register with the given number.
	* Index register number must be in range [1, 6].
	* Parameters:
	*	register_num - Index register number.
	*/
	Half_word Machine::index_register(int register_num) const
	{
		check_index_register_number(register_num);
		return index[register_num - 1];
	}

	/*
	* Returns the contents of memory at the given address.
	* Parameters:
	*	address - Memory address, in range [0, MEM_SIZE].
	*/
	Word Machine::memory_cell(int address) const
	{
		if (address < 0 || MEM_SIZE <= address) {
			throw std::invalid_argument{"Address out of bounds"};
		}
		return memory[address];
	}

	/*
	* Load the given word into the memory cell at the given address.
	* Parameters:
	*	address - Address of memory to be written to.
	*	w - Word to write to memory.
	*/
	void Machine::store_in_memory(int address, const Word& w)
	{
		if (address < 0 || MEM_SIZE <= address) {
			throw std::invalid_argument{"Address out of bounds"};
		}
		memory[address] = w;
	}
}

