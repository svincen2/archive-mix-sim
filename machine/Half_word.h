#ifndef MIX_SIM_MACHINE_HALF_WORD_H
#define MIX_SIM_MACHINE_HALF_WORD_H

#include "Basic_word.h"

namespace machine
{
  // Half word has two bytes and a sign.
  class Half_word : public Basic_word<2>
  {
  };
}

#endif

