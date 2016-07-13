#ifndef MIX_MACHINE_BYTE_H
#define MIX_MACHINE_BYTE_H

#include <cmath>

namespace mix
{
	// A machine byte.
	using Byte = unsigned char;

	// Size of a machine byte.
	const int BYTE_SIZE{6};

	// Keeps BYTE_SIZE bits, clears unused bits.
	const int BYTE_MASK{static_cast<int>(std::pow(2, BYTE_SIZE)) - 1};

	// Invalid byte indicator.
	const Byte INVALID_BYTE{-1};
}
#endif

