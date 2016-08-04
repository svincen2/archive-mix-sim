#ifndef MIX_MACHINE_MATH_OPERATION_H
#define MIX_MACHINE_MATH_OPERATION_H

#include "Machine.h"
#include "Operation.h"

namespace mix
{
	class Math_operation : public Operation
	{
	public:
		void execute(Machine*, const Instruction&) override;

	private:
		void execute_add(Machine*, const Instruction&) const;
		void execute_sub(Machine*, const Instruction&) const;
		void execute_mul(Machine*, const Instruction&) const;
		void execute_div(Machine*, const Instruction&) const;
	};
}
#endif

