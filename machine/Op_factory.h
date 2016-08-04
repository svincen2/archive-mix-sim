#ifndef MIX_MACHINE_OP_FACTORY_H
#define MIX_MACHINE_OP_FACTORY_H

#include "Operations.h" // For Operation interface and all implementors.
#include "Op_code.h"


namespace mix
{
	namespace Op_factory {
		Operation* make(Op_code);
	}
}
#endif

