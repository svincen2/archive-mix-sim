#ifndef MIX_SIM_WORD_H
#define MIX_SIM_WORD_H

#include "Basic_word.h"

namespace machine
{
  using Word = Basic_word<5>;

  // Most significant byte of address specification of instruction.
  const unsigned int address_msb{0};
  // Least significant byte of address specification of instruction.
  const unsigned int address_lsb{1};
  // Index specification of instruction.
  const unsigned int index{2};
  // Modification specification of instruction.
  const unsigned int modification{3};
  // Operation code of instruction.
  const unsigned int op_code{4};
}
#endif

