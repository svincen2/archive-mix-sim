#include "Machine.h"

namespace mix
{
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
	* Loads a program into memory.
	* Parameters:
	*	input - Input to read program from.
	*/
	void Machine::load_program(std::istream& input)
	{
		int curr_address{0};
		Word next_instruction{};
		while (input) {
			input >> next_instruction;
			memory[curr_address] = next_instruction;
		}
	}

	/*
	* Run the machine with the given arguments.
	* Parameters:
	*	args - Machine arguments.
	*/
	int Machine::run(std::vector<std::string>& args)
	{
		return 0;
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
}

