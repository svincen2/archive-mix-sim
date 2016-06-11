#include "Field.h"

namespace MIX
{
    namespace Instruction
    {
        // Field specification's left part scaling factor.
        const unsigned int left_scale{8};

        /*
        * Construct the default field specification of (0:5).
        */
        Field::Field() : left{0}, right{5}
        {
        }

        /*
        * Construct a field with the given left and right values.
        */
        Field::Field(unsigned int l, unsigned int r) : left{l}, right{r}
        {
        }

        /*
        * Copy the given field.
        */
        Field::Field(const Field& f) : left{f.left}, right{f.right}
        {
        }

        /*
        * Convert the given number into a field specification.
        */
        Field to_field_spec(const unsigned int ui)
        {
            unsigned int left{ui / left_scale};
            unsigned int right{ui % left_scale};
            return Field{left, right};
        }

        /*
        * Convert the given field specification into an unsigned int.
        */
        Byte to_byte(const Field& fs)
        {
            return static_cast<Byte>(fs.left * left_scale + fs.right);
        }
    }
}
