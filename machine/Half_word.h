#ifndef MIX_HALF_WORD_H
#define MIX_HALF_WORD_H

#include "Basic_word.h"

namespace MIX
{
    class Half_word : public Basic_word<2>
    {
    public:
        Half_word(Sign s = Sign::Plus,
                  Byte b1 = 0,
                  Byte b2 = 0);
    };
}
#endif

