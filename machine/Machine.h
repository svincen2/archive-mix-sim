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

      // Accessors.
      const Word& accumulator() const { return _accumulator; }
      const Word& extension() const { return _extension; }
      const Half_word& jump_register() const { return _jump; }
      const Half_word& index_register(int) const;
      const Word& memory(int) const;

      // Mutators.
      void accumulator(const Word& a) { _accumulator = a; }
      void extension(const Word& x) { _extension = x; }
      void jump_register(const Half_word& j) { _jump = j; }
      void index_register(int, const Word&);

    private:
      Word _accumulator;                        // Accumulator register (A).
      Word _extension;                          // Extension register (X).
      Half_word _jump;                          // Jump register (J).
      std::vector<Half_word> _index_registers;  // Index registers (I1-I6).
      std::vector<Word> _memory;                // 4000 word memory (0-3999).
  };
}
#endif

