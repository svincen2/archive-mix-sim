#ifndef MIX_INSTRUCTION_H
#define MIX_INSTRUCTION_H

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
		const unsigned int load_lower{8};
		const unsigned int load_upper{15};
		const unsigned int load_neg_lower{16};
		const unsigned int load_neg_upper{23};
		const unsigned int store_lower{24};
		const unsigned int store_upper{33};

		bool is_load(const unsigned int);
		bool is_load_neg(const unsigned int);
		//bool is_store(const unsigned int);

		// Register codes.
		const unsigned int accumulator{0};
		const unsigned int extension{7};
	}
}
#endif
