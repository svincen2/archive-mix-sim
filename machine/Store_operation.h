#ifndef MIX_MACHINE_STORE_OPERATION_H
#define MIX_MACHINE_STORE_OPERATION_H

#include "Instruction.h"
#include "Machine.h"
#include "Operation.h"

namespace mix
{
	class Store_operation : public Operation
	{
	public:
		void execute(Machine*, const Instruction&) override;

	private:
		Word register_content(const Word&, const Instruction&) const;
	};
}
#endif

