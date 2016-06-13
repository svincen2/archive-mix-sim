#ifndef MIX_INSTRUCTION_H
#define MIX_INSTRUCTION_H

#include "Op_code.h"

namespace MIX
{
	/*
	* Constants related to instructions.
	*/
	namespace Instruction
	{
		// Byte indices of instruction parts.
		const unsigned int address_msb{1};
		const unsigned int address_lsb{2};
		const unsigned int index{3};
		const unsigned int modification{4};
		const unsigned int op_code{5};

		// Operation code ranges.
		const unsigned int load_lower{Op_code::LDA};
		const unsigned int load_upper{Op_code::LDX};
		const unsigned int load_neg_lower{Op_code::LDAN};
		const unsigned int load_neg_upper{Op_code::LDXN};
		const unsigned int store_lower{Op_code::STA};
		const unsigned int store_upper{Op_code::STZ};

		bool is_load(const unsigned int);
		bool is_load_neg(const unsigned int);
		//bool is_store(const unsigned int);

		// Register codes.
		const unsigned int accumulator{0};
		const unsigned int extension{7};

		// Get register codes from operation code.
		const unsigned int load_register(const unsigned int);
		const unsigned int load_neg_register(const unsigned int);
	}
}
#endif
