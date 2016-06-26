#ifndef MIX_MACHINE_WORD_H
#define MIX_MACHINE_WORD_H

#include "Byte.h"
#include <stdexcept>
#include <vector>

namespace mix
{
	// Possible values of the sign of a basic word.
	enum class Sign : Byte { Plus = '+', Minus = '-' };


	// A mix basic word.
	template<unsigned int Num_bytes>
	class Basic_word
	{
	public:
		// Number of bytes.
		const unsigned int num_bytes = Num_bytes;


		// Constructors.
		Basic_word(Sign, std::vector<Byte>);
		Basic_word(const Basic_word&);
		Basic_word(Basic_word&&);


		/* Operators. */

		// Assignments.
		Basic_word& operator=(const Basic_word&);
		Basic_word& operator=(Basic_word&&);

		// Conversion.
		template<unsigned int N>
		explicit operator Basic_word<N>();


		/* Functions. */

		// Byte accessors.
		Byte byte(int) const;
		Byte& byte(int);

		// Sign accessors.
		Sign sign() const;
		Sign& sign();


	private:
		// Implementation.
		Sign sign_byte;
		std::vector<Byte> bytes;


		// Helper functions.
		void check_byte_index(int) const;
	};


	/*** Constructors and destructor. ***/

	/*
	* Fully parameterized constructor.
	* Template parameters:
	*	N - Number of bytes.
	* Parameters:
	*	s - Sign.
	*	byte_vec - Bytes.
	*/
	template<unsigned int N>
	Basic_word<N>::Basic_word(Sign s = Sign::Plus,
							  std::vector<Byte> byte_vec = {})
		: sign_byte{s}, bytes{}
	{
		if (byte_vec.size() > num_bytes)
			throw std::invalid_argument{"Too many bytes in initializer list."};
		for (auto p = byte_vec.begin(); p != byte_vec.end(); ++p)
			bytes.push_back(*p);
		while (bytes.size() < num_bytes)
			bytes.push_back(0);
	}

	/*
	* Construct a basic word by copying the given basic word.
	* Template parameters:
	*	N - Number of bytes.
	* Parameters:
	*	bw - Basic word.
	*/
	template<unsigned int N>
	Basic_word<N>::Basic_word(const Basic_word& bw)
		: sign_byte{bw.sign_byte}, bytes{bw.bytes}
	{
	}

	/*
	* Construct a basic word by moving the given basic word.
	* Template parameters:
	*	N - Number of bytes.
	* Parameters:
	*	bw - Basic word.
	*/
	template<unsigned int N>
	Basic_word<N>::Basic_word(Basic_word&& bw)
		: sign_byte{bw.sign_byte}, bytes{std::move(bw.bytes)}
	{
	}


	/*** Operators. ***/

	/* Conversion. */

	/*
	* Convert this basic word to a basic word with a different number of bytes.
	* If narrowing, the left-most bytes that don't fit will be dropped.
	* If widening, the left-most bytes will by filled with 0s.
	* Template parameters:
	*	N1 - Number of bytes of the basic word to be converted.
	*	N2 - Number of bytes of the new basic word.
	*/
	template<unsigned int N1>
	template<unsigned int N2>
	Basic_word<N1>::operator Basic_word<N2>()
	{
		Basic_word<N2> bw{};
		bw.sign() = sign_byte;
		for (int i = num_bytes, j = bw.num_bytes; i > 0 && j > 0; --i, --j) {
			bw.byte(j) = byte(i);
		}
		return bw;
	}


	/* Assignments. */

	/*
	* Copy assignment.
	* Template parameters:
	*	N - Number of bytes.
	* Parameters:
	*	bw - Basic word to copy assign.
	*/
	template<unsigned int N>
	Basic_word<N>& Basic_word<N>::operator=(const Basic_word<N>& bw)
	{
		sign_byte = bw.sign_byte;
		bytes = bw.bytes;
		return *this;
	}

	/*
	* Move assignment.
	* Template parameters:
	*	N - Number of bytes.
	* Parameters:
	*	bw - Basic word to move assign.
	*/
	template<unsigned int N>
	Basic_word<N>& Basic_word<N>::operator=(Basic_word<N>&& bw)
	{
		sign_byte = bw.sign_byte;
		bytes = std::move(bw.bytes);
		return *this;
	}


	/*** Functions. ***/

	/* Byte accessors. */

	/*
	* Returns the byte at the given index.
	* Parameters:
	*	index - Index of the byte to return, in range [1, N].
	*/
	template<unsigned int N>
	Byte Basic_word<N>::byte(int index) const
	{
		check_byte_index(index);
		return bytes[index - 1];
	}

	/*
	* Checks if the given index is in range [1, N].
	* If not, throws an exception.
	* Template parameters:
	*	N - Number of bytes.
	*/
	template<unsigned int N>
	void Basic_word<N>::check_byte_index(int index) const
	{
		if (index == 0)
			throw std::invalid_argument{"Cannot access sign with operator[]"};
		if (index < 1 || num_bytes < index)
			throw std::invalid_argument{"Invalid byte index"};
	}

	/*
	* Returns the byte at the given index.
	* Template parameters:
	*	N - Number of bytes.
	* Parameters:
	*	index - Index of the byte to return, in range [1, N].
	*/
	template<unsigned int N>
	Byte& Basic_word<N>::byte(int index)
	{
		check_byte_index(index);
		return bytes[index - 1];
	}

	
	/* Sign accessors. */

	/*
	* Returns the sign of the basic word.
	* Template parameters:
	*	N - Number of bytes.
	*/
	template<unsigned int N>
	Sign Basic_word<N>::sign() const
	{
		return sign_byte;
	}

	/*
	* Returns the sign of the basic word.
	* Template parameters:
	*	N - Number of bytes.
	*/
	template<unsigned int N>
	Sign& Basic_word<N>::sign()
	{
		return sign_byte;
	}
}
#endif

