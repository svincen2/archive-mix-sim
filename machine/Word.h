#ifndef MIX_WORD_H
#define MIX_WORD_H

#include "Basic_word.h"

namespace MIX
{
    class Word : public Basic_word<5>
    {
    public:
        // Parameterized constructor.
        Word(Sign s = Sign::Plus,
             Byte b1 = 0,
             Byte b2 = 0,
             Byte b3 = 0,
             Byte b4 = 0,
             Byte b5 = 0);
        };
}
#endif

