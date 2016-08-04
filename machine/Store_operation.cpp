#include "Store_operation.h"
#include <sstream>

namespace mix
{
	/*
	* Perform a store operation with the given machine.
	* Parameters:
	*	mix_machine - Mix machine to execute store operation on.
	*	inst - Instruction to execute.
	*/
	void Store_operation::execute(Machine* mix_machine, const Instruction& inst)
	{
		Word content{};
		Word mem_cell{mix_machine->memory_cell(inst.address)};
		switch (inst.op_code)
		{
		case Op_code::STA:
			content = register_content(mix_machine->accumulator(), inst);
			break;
		case Op_code::ST1:
			content = register_content(mix_machine->index_register(1), inst);
			break;
		case Op_code::ST2:
			content = register_content(mix_machine->index_register(2), inst);
			break;
		case Op_code::ST3:
			content = register_content(mix_machine->index_register(3), inst);
			break;
		case Op_code::ST4:
			content = register_content(mix_machine->index_register(4), inst);
			break;
		case Op_code::ST5:
			content = register_content(mix_machine->index_register(5), inst);
			break;
		case Op_code::ST6:
			content = register_content(mix_machine->index_register(6), inst);
			break;
		case Op_code::STX:
			content = register_content(mix_machine->extension_register(), inst);
			break;
		case Op_code::STJ:
			content = register_content(mix_machine->jump_register(), inst);
			break;
		case Op_code::STZ:
			// Store zero, so no need to change content.
			break;
		default:
			std::stringstream message{};
			message << "Op code is not a store operation: " << inst.op_code;
			throw std::invalid_argument{message.str()};
		}
		mem_cell.copy_range(content, inst.field);
		mix_machine->memory_cell(inst.address, mem_cell);
	}

	/*
	* Get the contents of the given register.
	* Parameters:
	*	reg - Register.
	*	inst - Instruction.
	*/
	Word Store_operation::register_content(const Word& reg,
										   const Instruction& inst) const
	{
		Word content{};
		if (inst.field.contains_sign()) {
			content = reg.rightmost_with_sign(inst.field.bytes());
		}
		else {
			content = reg.rightmost_bytes(inst.field.bytes());
		}
		int shift_amount{static_cast<int>(Word::num_bytes) - inst.field.right};
		content.shift_left(shift_amount);
		return content;
	}
}

