#ifndef MIX_OP_CODE_H
#define MIX_OP_CODE_H

#include "Byte.h"

namespace MIX
{
	enum Op_code : Byte
	{
		// Load op codes.
		LDA = 8, LD1, LD2, LD3, LD4, LD5, LD6, LDX,
		// Load negative op codes.
		LDAN, LD1N, LD2N, LD3N, LD4N, LD5N, LD6N, LDXN,
		// Store op codes.
		STA, ST1, ST2, ST3, ST4, ST5, ST6, STX, STJ, STZ
	};
}
#endif
