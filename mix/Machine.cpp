#include "Machine.h"

#include <iostream>

namespace MIX
{
	// Load op code range.
	const unsigned int load_lower{8};
	const unsigned int load_upper{23};

	/*
	* Construct a MIX machine.
	* All registers are cleared to +0.
	* All memory words are also cleared to +0.
	*/
	Machine::Machine()
		: _overflow{Bit::On},
		  _comparison_indicator{Comparison::Equal},
		  _accumulator{},
		  _extension{},
		  _jump{},
		  _index_registers(num_index_registers),
		  _memory(memory_size)
	{
	}

	/*
	* Return the index register at the given index.
	* Index is 1 based because register names are [I1, I6].
	* Register names are defined by Knuth, Volume 1, Chapter 3.1
	*/
	const Half_word& Machine::index_register(int index) const
	{
		if(index < 1 || num_index_registers < index)
			throw std::invalid_argument{"Index register index out of bounds"};
		return _index_registers[index - 1];
	}

	/*
	* Return the index register at the given index.
	* Allows the index register to be modified.
	* Index is 1 based because register names are [I1, I6].
	* Register names are defined by Knuth, Volum 1, Chapter 3.1
	*/
	Half_word& Machine::index_register(int index)
	{
		if(index < 1 || num_index_registers < index)
			throw std::invalid_argument{"Index register invalid"};
		return _index_registers[index - 1];
	}


	/*
	* Return the memory word at the given index.
	*/
	const Word& Machine::memory(int address) const
	{
		if(address < 0 || memory_size <= address)
			throw std::invalid_argument{"Memory index out of bounds"};
		return _memory[address];
	}

	/*
	* Return a reference to the memory word at the given address.
	* Allows the reference to be modified.
	*/
	Word& Machine::memory(int address)
	{
		if(address < 0 || memory_size <= address)
			throw std::invalid_argument{"Memory address out of bounds"};
		return _memory[address];
	}

	/*
	* Return the address specification of the given instruction word.
	* The address is offset by the contents of the index register
	* specified by the instruction's index specification on every instruction.
	* If the index specification is 0, there is no offset.
	*/
	const int Machine::read_address(const Word& instruction) const
	{
		int a{address(instruction)};
		const unsigned int i{read_index(instruction)};
		if(i > 0)
			a += address(index_register(i));
		return a;
	}

	/*
	* Return the index specification of the given instruction word.
	*/
	const unsigned int Machine::read_index(const Word& instruction) const
	{
		const unsigned int i{instruction.byte(Instruction::index)};
		if(i < 0 || num_index_registers < i)
			throw std::invalid_argument{"Index specification invalid"};
		return i;
	}

	/*
	* Return the field specification of the given instruction word.
	*/
	const Field Machine::read_field(const Word& instruction) const
	{
		return to_field(instruction.byte(Instruction::modification));
	}

	/*
	* Read the operation code part of the given instruction word.
	*/
	const unsigned int Machine::read_op_code(const Word& instruction) const
	{
		return instruction.byte(Instruction::op_code);
	}
}
