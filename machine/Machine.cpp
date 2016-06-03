#ifndef MIX_SIM_MACHINE_MACHINE_H
#define MIX_SIM_MACHINE_MACHINE_H

#include "Machine.h"

namespace machine
{
  /*
  * Construct a MIX machine.
  * All registers are cleared to +0.
  * All memory words are also cleared to +0.
  */
  Machine::Machine()
    : _accumulator{},
      _extension{},
      _jump{},
      _index_registers(num_index_registers),
      _memory(memory_size)
  {
  }

  /*
  * Return the index register at the given index.
  * Index is 1 based because register names are [I1, I6].
  * Register names are defined by Knuth, Volume 1, Chapter 3.1
  */
  const Half_word& Machine::index_register(int index) const
  {
    if(index < 1 || num_index_registers < index)
      throw std::invalid_argument{"Index register index out of bounds"};
    return _index_registers[index + 1];
  }

  /*
  * Return the memory word at the given index.
  */
  const Word& Machine::memory(int index) const
  {
    if(index < 0 || memory_size <= index)
      throw std::invalid_argument{"Memory index out of bounds"};
  }

  /*
  * Return the address specification of the given instruction word.
  */
  const int Machine::read_address(const Word& instruction) const
  {
    int a{(instruction[address_msb] & bit_mask) << byte_size};
    a |= instruction[address_lsb];
    return (instruction.sign() == Sign::Plus ? a : -a);
  }

  /*
  * Return the index specification of the given instruction word.
  */
  const unsigned int Machine::read_index(const Word& instruction) const
  {
    return instruction[index];
  }

  /*
  * Return the modification specification of the given instruction word.
  */
  const unsigned int Machine::read_modification(const Word& instruction) const
  {
    return instruction[modification];
  }

  /*
  * Return the field specification of the given instruction word.
  */
  const Instruction::Field Machine::read_field(const Word& instruction) const
  {
    return Instruction::to_field_spec(instruction[modification]);
  }

  /*
  * Return the operation code of the given instruction word.
  */
  const unsigned int Machine::read_op_code(const Word& instruction) const
  {
    return instruction[op_code];
  }
}

#endif

