#ifndef MIX_MACHINE_LOAD_NEG_OPERATION_H
#define MIX_MACHINE_LOAD_NEG_OPERATION_H

#include "Instruction.h"
#include "Machine.h"
#include "Operation.h"

namespace mix
{
	class Load_neg_operation : public Operation
	{
	public:
		void execute(Machine*, const Instruction&) override;
	};
}
#endif

