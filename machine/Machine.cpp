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
}

#endif

