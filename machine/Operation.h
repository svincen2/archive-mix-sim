#ifndef MIX_MACHINE_OPERATION_H
#define MIX_MACHINE_OPERATION_H

#include "Instruction.h"
#include "Machine.h"

namespace mix
{
	// Machine operation interface.
	class Operation
	{
	public:
		virtual void execute(Machine*, const Instruction&) = 0;
	};
}
#endif

