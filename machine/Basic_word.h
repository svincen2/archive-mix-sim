#ifndef MIX_SIM_MACHINE_BASIC_WORD_H
#define MIX_SIM_MACHINE_BASIC_WORD_H

#include "Byte.h"
#include "Sign.h"
#include <stdexcept>
#include <vector>

namespace machine
{
  template<unsigned int Size>
  class Basic_word
  {
    public:
      static const unsigned int num_bytes = Size;

      // Constructors.
      Basic_word();
      Basic_word(const Basic_word&);
      Basic_word(Basic_word&&) = delete;

      // Assignments.
      Basic_word& operator=(const Basic_word&);
      Basic_word& operator=(Basic_word&&) = delete;

      // Accessors.
      const Sign& sign() const { return _sign; }
      Sign& sign() { return _sign; }
      const std::vector<Byte>& bytes() const { return _bytes; }
      std::vector<Byte>& bytes() { return _bytes; }
      const Byte& operator[](int) const;
      Byte& operator[](int);

      // Mutators.
      void sign(Sign);

    private:
      Sign _sign;
      std::vector<Byte> _bytes;
  };

  /*
  * Construct a word with all bits cleared to 0,
  * and the sign set to plus (+).
  */
  template<unsigned int Size>
  Basic_word<Size>::Basic_word() : _sign{Sign::Plus}, _bytes(num_bytes)
  {
  }

  /*
  * Copy the given word.
  */
  template<unsigned int Size>
  Basic_word<Size>::Basic_word(const Basic_word<Size>& copy)
    : _sign{copy._sign}, _bytes{copy._bytes}
  {
  }

  /*
  * Copy assignment.
  */
  template<unsigned int Size>
  Basic_word<Size>& Basic_word<Size>::operator=(
      const Basic_word<Size>& wt)
  {
    _sign = wt._sign;
    _bytes = wt._bytes;
    return *this;
  }

  /*
  * Get the byte at the given index.
  */
  template<unsigned int Size>
  const Byte& Basic_word<Size>::operator[](int index) const
  {
    if(index < 0 || num_bytes <= index)
      throw std::invalid_argument{"Index out of bounds"};
    return _bytes[index];
  }

  /*
  * Get the byte at the given index.
  */
  template<unsigned int Size>
  Byte& Basic_word<Size>::operator[](int index)
  {
    if(index < 0 || num_bytes <= index)
      throw std::invalid_argument{"Index out of bounds"};
    return _bytes[index];
  }

  /*
  * Set the sign to the given sign value.
  */
  template<unsigned int Size>
  void Basic_word<Size>::sign(Sign s)
  {
    if(s != Sign::Plus && s != Sign::Minus)
      throw std::invalid_argument{"Unknown sign value"};
    _sign = s;
  }

}
#endif

