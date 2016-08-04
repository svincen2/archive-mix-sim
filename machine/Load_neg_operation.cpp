#include "Load_neg_operation.h"
#include <sstream>

namespace mix
{
	/*
	* Perform a load negative operation.
	* Parameters:
	*	mix_machine - Mix machine which is target of operation.
	*	inst - Instruction to execute.
	*/
	void Load_neg_operation::execute(Machine* mix_machine,
									 const Instruction& inst)
	{
		Word content{
			mix_machine->memory_content(inst.address, inst.field)
		};
		if (inst.field.contains_sign()) {
			content.negate();
		}
		switch (inst.op_code)
		{
		case Op_code::LDAN:
			mix_machine->accumulator(content);
			break;
		case Op_code::LD1N:
			mix_machine->index_register(1, content);
			break;
		case Op_code::LD2N:
			mix_machine->index_register(2, content);
			break;
		case Op_code::LD3N:
			mix_machine->index_register(3, content);
			break;
		case Op_code::LD4N:
			mix_machine->index_register(4, content);
			break;
		case Op_code::LD5N:
			mix_machine->index_register(5, content);
			break;
		case Op_code::LD6N:
			mix_machine->index_register(6, content);
			break;
		case Op_code::LDXN:
			mix_machine->extension_register(content);
			break;
		default:
			std::stringstream message{};
			message << "Op code is not a load negative: " << inst.op_code;
			throw std::invalid_argument{message.str()};
		}
	}
}

