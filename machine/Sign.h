#ifndef MIX_MACHINE_SIGN_H
#define MIX_MACHINE_SIGN_H

#include "Byte.h"
#include <iostream>

namespace mix
{
	// Possible values of the sign of a basic word.
	enum class Sign : Byte { Plus = '+', Minus = '-' };

	// Input/output.
	std::istream& operator>>(std::istream&, Sign&);
	std::ostream& operator<<(std::ostream&, const Sign&);

	// Validating a sign.
	bool valid(const Sign&);

	// Invalid sign exception.
	class Invalid_sign{};
}
#endif

