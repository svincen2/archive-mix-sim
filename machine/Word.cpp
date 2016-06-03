#include "Word.h"

namespace machine
{
  /* Indexes of the different part of a word. */

  // Most significant byte of address part of an instruction.
  const unsigned int address_msb_index{0};
  // Least significant byte of address part of an instruction.
  const unsigned int address_lsb_index{1};
  // Index part of an instruction.
  const unsigned int index_index{2};
  // Modification part of an instruction.
  const unsigned int modification_index{3};
  // Operation code part of an instruction.
  const unsigned int op_code_index{4};

  /*
  * Return the address part of the word.
  */
  unsigned int Word::address() const
  {
    unsigned int address{0};
    unsigned char bit_mask{0x3f};
    address = (operator[](address_msb_index) & bit_mask) << byte_size;
    address |= operator[](address_lsb_index) & bit_mask;
    return address;
  }

  /*
  * Return the index specification part of a word.
  */
  unsigned int Word::index() const
  {
    return operator[](index_index);
  }

  /*
  * Return the modification specification part of a word.
  */
  unsigned int Word::field() const
  {
    return operator[](modification_index);
  }

  /*
  * Return the operation code part of a word.
  */
  unsigned int Word::op_code() const
  {
    return operator[](op_code_index);
  }

}
