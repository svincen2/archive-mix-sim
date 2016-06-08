#ifndef MIX_INSTRUCTION_H
#define MIX_INSTRUCTION_H

namespace MIX
{
    /*
    * Constants identifying parts of an instruction word.
    */
    namespace Instruction
    {
        const unsigned int index{3};
        const unsigned int modification{4};
        const unsigned int op_code{5};
    }
}
#endif

