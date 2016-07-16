#ifndef MIX_MACHINE_INSTRUCTION_H
#define MIX_MACHINE_INSTRUCTION_H

#include "Byte.h"
#include "Field_spec.h"
#include "Word.h"

namespace mix
{
	// Constants for the parts of an instruction.
	const Field_spec ADDRESS_FIELD{0, 2};
	const unsigned int INDEX_SPEC{3};
	const unsigned int FIELD_SPEC{4};
	const unsigned int OP_CODE{5};

	// Functions for accessing named parts of a word.
	template<unsigned int N>
	int get_address(const Basic_word<N>& bw)
	{
		return bw.to_int(ADDRESS_FIELD);
	}

	template<unsigned int N>
	Byte get_index_spec(const Basic_word<N>& bw)
	{
		return bw.byte(INDEX_SPEC);
	}

	template<unsigned int N>
	Byte get_field_spec(const Basic_word<N>& bw)
	{
		return bw.byte(FIELD_SPEC);
	}

	template<unsigned int N>
	Byte get_op_code(const Basic_word<N>& bw)
	{
		return bw.byte(OP_CODE);
	}
}
#endif

