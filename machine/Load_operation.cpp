#include "Load_operation.h"
#include <sstream>

namespace mix
{
	void Load_operation::execute(Machine* mix_machine, const Instruction& inst)
	{
		// Perform a load operation.
		const Word content{
			mix_machine->memory_content(inst.address, inst.field)
		};
		switch (inst.op_code)
		{
		case Op_code::LDA:
			mix_machine->accumulator(content);
			break;
		case Op_code::LD1:
			mix_machine->index_register(1, content);
			break;
		case Op_code::LD2:
			mix_machine->index_register(2, content);
			break;
		case Op_code::LD3:
			mix_machine->index_register(3, content);
			break;
		case Op_code::LD4:
			mix_machine->index_register(4, content);
			break;
		case Op_code::LD5:
			mix_machine->index_register(5, content);
			break;
		case Op_code::LD6:
			mix_machine->index_register(6, content);
			break;
		case Op_code::LDX:
			mix_machine->extension_register(content);
			break;
		default:
			std::stringstream message{};
			message << "Op code is not a load: " << inst.op_code;
			throw std::invalid_argument{message.str()};
		}
	}
}

