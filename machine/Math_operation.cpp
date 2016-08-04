#include "Math_operation.h"
#include <sstream>

namespace mix
{
	/*
	* Perform an arithmetic operation on the given machine.
	* Parameters:
	*	mix_machine - Mix machine used to execute the instruction.
	*	inst - Instruction to execute.
	*/
	void Math_operation::execute(Machine* mix_machine, const Instruction& inst)
	{
		switch (inst.op_code)
		{
		case Op_code::ADD:
			execute_add(mix_machine, inst);
			break;
		case Op_code::SUB:
			execute_sub(mix_machine, inst);
			break;
		case Op_code::MUL:
			execute_mul(mix_machine, inst);
			break;
		case Op_code::DIV:
			execute_div(mix_machine, inst);
			break;
		default:
			std::stringstream message{};
			message << "Op code is not an arithmetic op: " << inst.op_code;
			throw std::invalid_argument{message.str()};
		}
	}

	/*
	*
	*/
	void Math_operation::execute_add(Machine* mix_machine,
									 const Instruction& inst) const
	{

	}

	/*
	*
	*/
	void Math_operation::execute_sub(Machine* mix_machine,
									 const Instruction& inst) const
	{

	}

	/*
	*
	*/
	void Math_operation::execute_mul(Machine* mix_machine,
									 const Instruction& inst) const
	{

	}

	/*
	*
	*/
	void Math_operation::execute_div(Machine* mix_machine,
									 const Instruction& inst) const
	{

	}
}

