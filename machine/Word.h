#ifndef MIX_SIM_WORD_H
#define MIX_SIM_WORD_H

#include "Basic_word.h"

namespace machine
{
  class Word : public Basic_word<5>
  {
    public:
      // Word parts.
      unsigned int address() const;
      unsigned int field() const;
      unsigned int code() const;
      unsigned int index() const;
  };
}
#endif

