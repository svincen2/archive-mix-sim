#ifndef MIX_SIM_MACHINE_H
#define MIX_SIM_MACHINE_H

#include "Half_word.h"
#include "Word.h"
#include <vector>

namespace machine
{
  class Machine
  {
    public:
      // Constants.
      static const unsigned int num_index_registers{6};
      static const unsigned int memory_size{4000};

      // Constructors.
      Machine();
      Machine(const Machine&) = delete;
      Machine(Machine&&) = delete;

      // Destructor.
      ~Machine();

    private:
      std::vector<Word> _index_registers;
      std::vector<Word> _memory;
  };
}
#endif

