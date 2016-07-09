#include "Machine.h"
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
		: overflow{Bit::Off},
		  compare{Comparison_value::Equal},
		  jump{},
		  accum{},
		  exten{},
		  pc{0},
		  index(NUM_INDEX_REGISTERS),
		  memory(MEM_SIZE)
	{
	}

	/*
	* Run the machine with the given arguments.
	* Parameters:
	*	args - Machine arguments.
	*/
	void Machine::run(std::vector<std::string>& args)
	{
		check_arguments(args);
		std::ifstream program_file{args[0]};
		load_program(&program_file);
	}

	/*
	* Check the machine arguments.
	* Parameters:
	*	args - Machine arguments.
	*/
	void Machine::check_arguments(const std::vector<std::string>& args) const
	{
		if (args.size() < 1)
			throw std::invalid_argument{"Expected at least 1 argument"};
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
			try {
				// Last input attempt will throw exception.
				*program >> next_instruction;
			}
			catch (Invalid_basic_word& e) {
				if (!program->eof()) throw e;
				else break;
			}
			memory[curr_address++] = next_instruction;
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
		if (program_input_stream->fail())
			throw std::invalid_argument{"Cannot read program"};
		if (program_input_stream->peek() == EOF)
			throw std::invalid_argument{"Program file is empty"};
	}

	/*
	* Execute the next instruction.
	*/
	void Machine::execute_next_instruction()
	{
		// Fetch.
		Word next_inst{memory_cell(pc)};

		// Execute.


		// Point to next instruction.
		++pc;
	}

	/*
	* Returns the program counter.
	*/
	int Machine::program_counter() const
	{
		return pc;
	}

	/*
	* Dumps the contents of memory into the given stream.
	*/
	void Machine::dump_memory(std::ostream* stream) const
	{
		for (int i = 0; i < MEM_SIZE; ++i)
			*stream << memory[i];
	}

	/*
	* Returns the state of the overflow bit.
	*/
	Machine::Bit Machine::overflow_bit() const
	{
		return overflow;
	}

	/*
	* Returns the state of the comparison indicator.
	*/
	Machine::Comparison_value Machine::comparison_indicator() const
	{
		return compare;
	}

	/*
	* Returns the contents of the jump register.
	*/
	Machine::Half_word Machine::jump_register() const
	{
		return jump;
	}

	/*
	* Returns the contents of the accumulator.
	*/
	Machine::Word Machine::accumulator() const
	{
		return accum;
	}

	/*
	* Returns the contents of the extension register.
	*/
	Machine::Word Machine::extension_register() const
	{
		return exten;
	}

	/*
	* Returns the contents of the index register with the given ID.
	*/
	Machine::Half_word Machine::index_register(int id) const
	{
		if (id < 1 || NUM_INDEX_REGISTERS < id)
			throw std::invalid_argument{"Index register ID does not exist"};
		return index[id - 1];
	}

	/*
	* Returns the contents of memory at the given address.
	* Parameters:
	*	address - Memory address, in range [0, MEM_SIZE].
	*/
	Machine::Word Machine::memory_cell(int address) const
	{
		if (address < 0 || MEM_SIZE <= address)
			throw std::invalid_argument{"Address out of bounds"};
		return memory[address];
	}

	/*
	* Load the given word into the memory cell at the given address.
	* Parameters:
	*	address - Address of memory to be written to.
	*	w - Word to write to memory.
	*/
	void Machine::store_in_memory(int address, Word& w)
	{
		if (address < 0 || MEM_SIZE <= address)
			throw std::invalid_argument{"Address out of bounds"};
		memory[address] = w;
	}
}

