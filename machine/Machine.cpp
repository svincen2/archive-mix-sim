#include "Machine.h"
#include "Op_factory.h"
#include <fstream>
#include <iterator>
#include <memory>

namespace mix
{
	/* Constant definitions. */
	const unsigned int Machine::mem_size{4000};
	const unsigned int Machine::num_index_registers{6};

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
		  index(num_index_registers),
		  memory(mem_size),
		  program_finished{false}
	{
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
		std::istream_iterator<Word> instruction_iter{*program};
		std::istream_iterator<Word> eof{};
		while (instruction_iter != eof) {
			if (!instruction_iter->is_valid()) {
				throw Invalid_basic_word{};
			}
			memory[curr_address++] = *instruction_iter;
			++instruction_iter;
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
		pc = 0; // Start program counter at first memory cell.
		program_finished = false;
		while (!program_finished) {
			execute_next_instruction();
		}
	}

	/*
	* Execute the next instruction.
	*/
	void Machine::execute_next_instruction()
	{
		// Fetch, decode, and increment program counter.
		const Instruction next{decode(memory_cell(pc++))};

		// Execute.
		std::unique_ptr<Operation> op{Op_factory::make(next.op_code)};
		op->execute(this, next);
	}

	/*
	* Decode the word as an instruction.
	*/
	Instruction Machine::decode(const Word& word) const
	{
		return Instruction{
			read_address(word),
			get_index_spec(word),
			get_field_spec(word),
			get_modification(word),
			get_op_code(word)
		};
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
	const Word Machine::memory_content(
			int address,
			const Field_spec& field) const
	{
		return memory_cell(address).field_aligned_right(field);
	}

	/*
	* Set the overflow bit to the given bit.
	* Parameters:
	*	b - New state of overflow bit.
	*/
	void Machine::overflow_bit(Bit b)
	{
		overflow = b;
	}

	/*
	* Load the index register specified by the given register number
	* with the given half word.
	* Parameters:
	*	register_num - Index register number, in range [1, 6].
	*	hw - Half word to load.
	*/
	void Machine::index_register(int register_num, const Half_word& hw)
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
		if (num < 1 || num_index_registers < num) {
			throw std::invalid_argument{"Invalid index register number"};
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
	* Dumps the contents of memory into the given stream.
	*/
	void Machine::dump_memory(std::ostream* stream) const
	{
		for (int i = 0; i < mem_size; ++i) {
			*stream << memory[i];
		}
	}

	/*
	* Returns the contents of memory at the given address.
	* Parameters:
	*	address - Memory address, in range [0, mem_size].
	*/
	Word Machine::memory_cell(int address) const
	{
		check_memory_cell_address(address);
		return memory[address];
	}

	/*
	* Checks that the given memory cell address is valid.
	* Parameters:
	*	address - Memory cell address to check.
	*/
	void Machine::check_memory_cell_address(int address) const
	{
		if (address < 0 || mem_size <= address) {
			throw std::invalid_argument{"Address out of bounds"};
		}
	}

	/*
	* Load the given word into the memory cell at the given address.
	* Parameters:
	*	address - Address of memory to be written to.
	*	w - Word to write to memory.
	*/
	void Machine::memory_cell(int address, const Word& w)
	{
		check_memory_cell_address(address);
		memory[address] = w;
	}

	/*
	* Load the accumulator with the given word.
	* Parameters:
	*	w - Word to load into accumulator.
	*/
	void Machine::accumulator(const Word& w)
	{
		accum = w;
	}

	/*
	* Load the extension register with the given word.
	* Parameters:
	*	w - Word to load into extension register.
	*/
	void Machine::extension_register(const Word& w)
	{
		exten = w;
	}

	/*
	* Load the jump register with the given half word.
	* Parameters:
	*	hw - Half word to load into jump register.
	*/
	void Machine::jump_register(const Half_word& hw)
	{
		jump = hw;
	}
}

