#include "Half_word.h"

namespace MIX
{
    /*
    * Construct a half word with the given values.
    */
    Half_word::Half_word(Sign s, Byte b1, Byte b2)
        : Basic_word{}
    {
        sign(s);
        byte(0) = b1;
        byte(1) = b2;
    }
}
