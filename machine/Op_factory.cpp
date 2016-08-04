#ifndef MIX_MACHINE_OP_FACTORY_H
#define MIX_MACHINE_OP_FACTORY_H

#include "Op_factory.h"
#include "Operations.h"
#include <sstream>
#include <stdexcept>

namespace mix
{
	namespace Op_factory
	{
		// Make an appropriate operation functor.
		Operation* make(Op_code code)
		{
			if (is_math_op(code)) {
				return new Math_operation{};
			}
			else if (is_load_op(code)) {
				return new Load_operation{};
			}
			else if (is_load_neg_op(code)) {
				return new Load_neg_operation{};
			}
			else if (is_store_op(code)) {
				return new Store_operation{};
			}
			else {
				std::stringstream message{};
				message << "Unknown op code: " << code;
				throw std::invalid_argument{message.str()};
			}
		}
	}
}
#endif

