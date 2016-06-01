#ifndef MIX_SIM_MACHINE_MACHINE_H
#define MIX_SIM_MACHINE_MACHINE_H

#include "Machine.h"

namespace machine
{
  Machine::Machine()
    : _index_registers(num_index_registers),
      _memory(memory_size)
  {
  }
}

#endif

