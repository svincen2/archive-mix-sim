#include "Instruction.h"

namespace MIX
{
	namespace Instruction
	{
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
