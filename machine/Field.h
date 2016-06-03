#ifndef MIX_SIM_MACHINE_FIELD_H
#define MIX_SIM_MACHINE_FIELD_H

namespace machine
{
  namespace Instruction
  {
    /*
    * A MIX machine instruction field specification.
    * Specifies the bytes of a word to be utilized in an instruction.
    */
    struct Field
    {
      unsigned int left;
      unsigned int right;

      Field();
      Field(unsigned int, unsigned int);
      Field(const Field&);
    };

    // Convert a number to a field specification.
    Field to_field_spec(const unsigned int);

    // Convert a field specification to a number.
    unsigned int to_uint(const Field&);
  }
}
#endif

