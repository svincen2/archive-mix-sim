#include "Instruction.h"

namespace MIX
{
	namespace Instruction
	{
		// Operation code ranges.
		const unsigned int load_lower{Op_code::LDA};
		const unsigned int load_upper{Op_code::LDX};
		const unsigned int load_neg_lower{Op_code::LDAN};
		const unsigned int load_neg_upper{Op_code::LDXN};
		const unsigned int store_lower{Op_code::STA};
		const unsigned int store_upper{Op_code::STZ};

		/*
		* Determine if the operation code is a load operation.
		*/
		bool is_load(const unsigned int op_code)
		{
			return load_lower <= op_code && op_code <= load_upper;
		}

		/*
		* Determine if the operation code is a load negative operation.
		*/
		bool is_load_neg(const unsigned int op_code)
		{
			return load_neg_lower <= op_code && op_code <= load_neg_upper;
		}

		/*
		* Returns the register code for a load operation.
		*/
		const unsigned int load_register(const unsigned int load_code)
		{
			return load_code - load_lower;
		}

		/*
		* Returns the register code for a load negative operation.
		*/
		const unsigned int load_neg_register(const unsigned int load_code)
		{
			return load_code - load_neg_lower;
		}
	}
}
