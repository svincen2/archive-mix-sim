#ifndef MIX_SIM_BYTE_H
#define MIX_SIM_BYTE_H

#include <cmath>

namespace machine
{
  // Alias for a Byte.
  using Byte = unsigned char;

  // The number of bits in a byte.
  const int byte_size{6};

  // Mask to read only byte_size number of bits from a Byte.
  const int bit_mask{static_cast<int>(std::pow(2, byte_size)) - 1};
}
#endif

