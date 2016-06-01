#ifndef MIX_SIM_MACHINE_HALF_WORD_H
#define MIX_SIM_MACHINE_HALF_WORD_H

#include "Word_template.h"

namespace machine
{
  // Half word has two bytes and a sign.
  using Half_word = Word_template<2>;
}

#endif

