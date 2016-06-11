#include "Word.h"

namespace MIX
{
    /*
    * Construct a word with the given values.
    */
    Word::Word(Sign s, Byte b1, Byte b2, Byte b3, Byte b4, Byte b5)
        : Basic_word{}
    {
        sign(s);
        byte(1) = b1;
        byte(2) = b2;
        byte(3) = b3;
        byte(4) = b4;
        byte(5) = b5;
    }
}
