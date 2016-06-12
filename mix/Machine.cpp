#include "Machine.h"

#include <iostream>

namespace MIX
{
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
		int a{to_int(instruction, Field::address())};
		const unsigned int i{read_index(instruction)};
		if(i > 0)
			a += to_int(index_register(i), Field::address());
		return a;
	}

	/*
	* Return the index specification of the given instruction word.
	*/
	const unsigned int Machine::read_index(const Word& instruction) const
	{
		const unsigned int i{instruction.byte(Instruction::index)};
		if(num_index_registers < i)
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

	/*
	* Execute the given instruction.
	*/
	void Machine::execute_instruction(const Word& instruction)
	{
		const unsigned int op_code{read_op_code(instruction)};
		if(Instruction::is_load(op_code))
			load(Instruction::load_register(op_code), instruction);
		else if(Instruction::is_load_neg(op_code))
			load_neg(Instruction::load_neg_register(op_code), instruction);
	}

	/*
	* Load the specified register according to the instruction.
	*/
	void Machine::load(unsigned int register_code, const Word& instruction)
	{
		const int address{read_address(instruction)};
		const Field field{read_field(instruction)};
		const Word contents{right_shift(memory(address), field)};
		if(register_code == Instruction::accumulator)
			accumulator() = contents;
		else if(register_code == Instruction::extension)
			extension() = contents;
		else
			index_register(register_code) = contents;
	}

	/*
	* Same as load, except the opposite sign is used.
	*/
	void Machine::load_neg(unsigned int register_code, const Word& instruction)
	{
		load(register_code, instruction);
		if(register_code == Instruction::accumulator)
			accumulator().negate();
		else if(register_code == Instruction::extension)
			extension().negate();
		else
			index_register(register_code).negate();
	}

	/*
	* Get the contents of the field of the given word, right shifted.
	*/
	const Word Machine::right_shift(const Word& word, const Field& field)
	{
		unsigned int left{field.left == 0 ? 1 : field.left};
		Word result{};
		result.set_right(word.get_bytes(left, field.right));
		if(field.left == 0) result.sign(word.sign());
		return result;
	}
}
