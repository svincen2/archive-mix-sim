#include "Instruction.h"

namespace mix
{
	// Field specification of the address part of an instruction.
	const Field_spec Instruction::ADDRESS_FIELD{0, 2};

	/*
	* Construct an instruction by copying the given word.
	*/
	Instruction::Instruction(const Word& w)
		: Word{w}
	{
	}

	/*
	* Returns the address part of the given instruction.
	*/
	int Instruction::address() const
	{
		return to_int(ADDRESS_FIELD);
	}

	/*
	* Return the index specification part of the given instruction.
	*/
	Byte Instruction::index_spec() const
	{
		return byte(INDEX_SPEC);
	}

	/*
	* Return the field specification of the given instruction.
	*/
	Byte Instruction::field_spec() const
	{
		return byte(FIELD_SPEC);
	}

	/*
	* Return the operation code of the given instruction.
	*/
	Byte Instruction::op_code() const
	{
		return byte(OP_CODE);
	}
}

