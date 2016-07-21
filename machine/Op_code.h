#ifndef MIX_MACHINE_OP_CODE_H
#define MIX_MACHINE_OP_CODE_H

#include "Byte.h"

namespace mix
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
		LDXN,

		// Store operations.
		STA
	};
}
#endif

