#ifndef MIX_MIXAL_OP_H
#define MIX_MIXAL_OP_H

#include "../machine/Byte.h"

namespace mixal
{
	// Mix assembly language op codes.
	enum Op_code : Byte
	{
		// Load operations.
		LDA = 8,
		LD1, LD2, LD3, LD4, LD5, LD6,
		LDX,

		// Load negative operations.
		LDAN,
		LD1N, LD2N, LD3N, LD4N, LD5N, LD6N,
		LDXN
	};
}
#endif

