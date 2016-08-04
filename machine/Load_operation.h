#include "Operation.h"
#include "Machine.h"

namespace mix
{
	// Load operation.
	class Load_operation : public Operation
	{
	public:
		void execute(Machine*, const Instruction&) override;
	};
}

