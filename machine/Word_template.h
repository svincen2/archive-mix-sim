#ifndef MIX_SIM_MACHINE_WORD_TEMPLATE_H
#define MIX_SIM_MACHINE_WORD_TEMPLATE_H

#include "Byte.h"
#include "Sign.h"
#include <stdexcept>
#include <vector>

namespace machine
{
  template<unsigned int Size>
  class Word_template
  {
    public:
      static const unsigned int num_bytes = Size;

      // Constructors.
      Word_template();
      Word_template(const Word_template&);
      Word_template(Word_template&&) = delete;

      // Accessors.
      const Sign& sign() const { return _sign; }
      Sign& sign() { return _sign; }

      const std::vector<Byte>& bytes() const { return _bytes; }
      std::vector<Byte>& bytes() { return _bytes; }

      const Byte& operator[](int) const;
      Byte& operator[](int);

    private:
      Sign _sign;
      std::vector<Byte> _bytes;
  };

  /*
  * Construct a word with all bits cleared to 0,
  * and the sign set to plus (+).
  */
  template<unsigned int Size>
  Word_template<Size>::Word_template() : _sign{Sign::Plus}, _bytes(num_bytes)
  {
  }

  /*
  * Copy the given word.
  */
  template<unsigned int Size>
  Word_template<Size>::Word_template(const Word_template<Size>& copy)
    : _sign{copy._sign}, _bytes{copy._bytes}
  {
  }

  /*
  * Get the byte at the given index.
  */
  template<unsigned int Size>
  const Byte& Word_template<Size>::operator[](int index) const
  {
    if(index < 0 || num_bytes <= index)
      throw std::invalid_argument{"Index out of bounds"};
    return _bytes[index];
  }

  /*
  * Get the byte at the given index.
  */
  template<unsigned int Size>
  Byte& Word_template<Size>::operator[](int index)
  {
    if(index < 0 || num_bytes <= index)
      throw std::invalid_argument{"Index out of bounds"};
    return _bytes[index];
  }

}
#endif

