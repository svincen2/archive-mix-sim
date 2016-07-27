#ifndef MIX_MACHINE_BASIC_WORD_H
#define MIX_MACHINE_BASIC_WORD_H

#include "Byte.h"
#include "Field_spec.h"
#include "Sign.h"
#include <iostream>
#include <stdexcept>
#include <vector>

namespace mix
{
	// Invalid basic word exception.
	class Invalid_basic_word{};


	// A mix basic word.
	template<unsigned int Num_bytes>
	class Basic_word
	{
	public:
		// Number of bytes.
		static const unsigned int num_bytes = Num_bytes;


		// Constructors.
		Basic_word(Sign s = Sign::Plus, std::vector<Byte> vb = {});
		Basic_word(const Basic_word&);
		Basic_word(Basic_word&&);


		/* Operators. */

		// Assignments.
		Basic_word& operator=(const Basic_word&);
		Basic_word& operator=(Basic_word&&);

		// Comparison.
		bool operator==(const Basic_word&) const;

		// Conversion.
		template<unsigned int N>
		operator Basic_word<N>() const;


		/* Functions. */

		// Byte accessors.
		Byte byte(int) const;
		Byte& byte(int);

		// Sign accessors.
		Sign sign() const;
		Sign& sign();

		// Byte shifting (mutating).
		void right_shift(int);
		void left_shift(int);

		// Byte shifted (non-mutating).
		Basic_word right_shifted(int) const;
		Basic_word left_shifted(int) const;

		// Rotating shifts.
		void rotate_right(int);
		void rotate_left(int);

		// Clear all bytes.
		void clear_bytes();

		// Range copy.
		void copy_range(const Basic_word&, int fist = 0, int last = Num_bytes);
		void copy_range(const Basic_word&, const Field_spec&);

		// Basic word validity check.
		bool is_valid() const;

		// Converting contiguous ranges to integer.
		int to_int(int first = 0, int last = Num_bytes) const;
		int to_int(const Field_spec&) const;

		// Negate the sign.
		Basic_word& negate();

		// Field alignment.
		Basic_word field_aligned_left(const Field_spec&) const;
		Basic_word field_aligned_right(const Field_spec&) const;

		// Left/right most bytes only.
		Basic_word leftmost_bytes(int) const;
		Basic_word rightmost_bytes(int) const;
		Basic_word leftmost_with_sign(int) const;
		Basic_word rightmost_with_sign(int) const;


	private:
		// Implementation.
		Sign sign_byte;
		std::vector<Byte> bytes;


		// Helper functions.
		void check_byte_index(int) const;
		void check_range(int, int) const;
		void check_rotate_amount(int&) const;
		void rotate_bytes_right(int);
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
	Basic_word<N>::Basic_word(Sign s, std::vector<Byte> byte_vec)
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
	Basic_word<N1>::operator Basic_word<N2>() const
	{
		Basic_word<N2> bw{};
		bw.sign() = sign_byte;
		for (int i = N1, j = N2; i > 0 && j > 0; --i, --j) {
			bw.byte(j) = byte(i);
		}
		return bw;
	}


	/* Comparisons. */

	/*
	* Tests two basic words for equality.
	* Template parameters:
	*	N - Number of bytes of both words.
	* Parameters:
	*	bw - Word to compare to.
	*/
	template<unsigned int N>
	bool Basic_word<N>::operator==(const Basic_word& bw) const
	{
		if (sign_byte == bw.sign_byte) {
			return bytes == bw.bytes;
		}
		return false;
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
			throw std::invalid_argument{"Cannot access sign with byte()"};
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

	/*
	* Shift bytes right by the given amount.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	n - Number of times to shift right.
	*/
	template<unsigned int N>
	void Basic_word<N>::right_shift(int n)
	{
		if (n > N) clear_bytes();
		if (n < 0)
			throw std::invalid_argument{"Cannot shift by negative amount"};

		// Move bytes that will not be shifted out.
		int i = N;
		for (int j = N - n; j > 0; --i, --j)
			byte(i) = byte(j);

		// Left-fill with 0s.
		for (int j = 1; j <= i; ++j)
			byte(j) = 0;
	}

	/*
	* Clear all bytes to 0.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	*/
	template<unsigned int N>
	void Basic_word<N>::clear_bytes()
	{
		for (int i = 1; i <= num_bytes; ++i) {
			byte(i) = 0;
		}
	}

	/*
	* Shift bytes left, right-filling with 0s.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	n - Number of times to left shift.
	*/
	template<unsigned int N>
	void Basic_word<N>::left_shift(int n)
	{
		if (n > N) clear_bytes();
		if (n < 0)
			throw std::invalid_argument{"Cannot shift by negative amount"};

		// Move bytes that will not be shifted out.
		int i = 1;
		for (int j = 1 + n; j <= N; ++i, ++j)
			byte(i) = byte(j);

		// Right fill with 0s.
		for (int j = N; j >= i; --j)
			byte(j) = 0;
	}

	/*
	* Returns a new word, which is a copy of this word, right shifted
	* by the given amount.
	* Template parameters:
	*	N - Number of bytes of this basic word, and the returned word.
	* Parameters:
	*	n - The amount the returned word will be shifted.
	*/
	template<unsigned int N>
	Basic_word<N> Basic_word<N>::right_shifted(int n) const
	{
		Basic_word<N> copy{*this};
		copy.right_shift(n);
		return copy;
	}

	/*
	* Returns a new word, which is a copy of this word, left shifted
	* by the given amount.
	* Template parameters:
	*	N - Number of bytes of this basic word, and the returned word.
	* Parameters:
	*	n - The amount the returned word will be shifted.
	*/
	template<unsigned int N>
	Basic_word<N> Basic_word<N>::left_shifted(int n) const
	{
		Basic_word<N> copy{*this};
		copy.left_shift(n);
		return copy;
	}

	/*
	* Rotate shift right all bytes n times.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	n - Number of times to rotate right.
	*/
	template<unsigned int N>
	void Basic_word<N>::rotate_right(int n)
	{
		check_rotate_amount(n);
		rotate_bytes_right(n);
	}

	/*
	* Check the amount to rotate by.
	* If the amount is negative, throws an exception.
	* Normalizes amount to be within range [0, N - 1].
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	n - Amount to rotate by.
	*/
	template<unsigned int N>
	void Basic_word<N>::check_rotate_amount(int& n) const
	{
		if (n < 0)
			throw std::invalid_argument{"Cannot rotate negative amount"};
		if (n >= N) n %= N;
	}

	/*
	* Rotate bytes right by the given amount.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	n - Number of times to rotate right.
	*/
	template<unsigned int N>
	void Basic_word<N>::rotate_bytes_right(int n)
	{
		if (n == 0) return;

		// Rotate bytes.
		std::vector<Byte> copy{bytes};
		for (int i = 0, j = n; i < N; ++i) {
			bytes[j] = copy[i];
			j = (j + 1) % N;
		}
	}

	/*
	* Rotate shift left all bytes n times.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	n - Number of times to rotate left.
	*/
	template<unsigned int N>
	void Basic_word<N>::rotate_left(int n)
	{
		// Rotating left by n is the same as rotating right by N - n.
		check_rotate_amount(n);
		rotate_bytes_right(N - n);
	}

	/*
	* Copies the given range [first, last] from the given word
	* into the same range of this word.
	* Template parameters:
	*	N - Number of bytes.
	* Parameters:
	*	bw - Word to be copied.
	*	first - First (lowest index) byte to be copied.
				If 0, the sign is copied.
	*	last - Last (highest index) byte to be copied.
	*/
	template<unsigned int N>
	void Basic_word<N>::copy_range(const Basic_word& bw, int first, int last)
	{
		check_range(first, last);
		if (first == 0) {
			sign_byte = bw.sign_byte;
			++first;
		}
		for (int i = first; i <= last; ++i)
			byte(i) = bw.byte(i);
	}

	/*
	* Makes sure the range [first, last] is valid.
	*/
	template<unsigned int N>
	void Basic_word<N>::check_range(int first, int last) const
	{
		if (first > last)
			throw std::invalid_argument{"Invalid range: first > last"};
		if (first < 0)
			throw std::invalid_argument{"Invalid range: first is negative"};
		if (last > num_bytes)
			throw std::invalid_argument{"Invalid range: last > num of bytes"};
	}

	/*
	* Copies the range of the given field spec from the given word
	* into the same range of this word.
	* Template parameters:
	*	N - Number of bytes.
	* Parameters:
	*	bw - Word to be copied.
	*	first - First (lowest index) byte to be copied.
				If 0, the sign is copied.
	*	last - Last (highest index) byte to be copied.
	*/
	template<unsigned int N>
	void Basic_word<N>::copy_range(const Basic_word& bw,
								   const Field_spec& field)
	{
		copy_range(bw, field.left, field.right);
	}

	/*
	* Checks if the basic word is valid.
	* Template paramters:
	*	N - Number of bytes of this basic word.
	*/
	template<unsigned int N>
	bool Basic_word<N>::is_valid() const
	{
		if (sign_byte == Sign::Invalid)
			return false;

		for (int i = 1; i <= N; ++i) {
			if (bytes[i] == INVALID_BYTE || bytes[i] > BYTE_MAX)
				return false;
		}
		return true;
	}

	/*
	* Reads a range of bytes as an integer
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	first - First byte in range.
	*	last - Last byte in range.
	*/
	template<unsigned int N>
	int Basic_word<N>::to_int(int first, int last) const
	{
		int first_byte{first == 0 ? 1 : first};
		check_range(first_byte, last);
		int result{};
		for (int i = first_byte; i <= last; ++i) {
			result <<= BYTE_SIZE;
			result += byte(i);
		}
		if (first == 0 && sign_byte == Sign::Minus) {
			result = -result;
		}
		return result;
	}

	/*
	* Read the field specification as an integer.
	* Parameters:
	*	fs - Field specification.
	*/
	template<unsigned int N>
	int Basic_word<N>::to_int(const Field_spec& fs) const
	{
		return to_int(fs.left, fs.right);
	}

	/*
	* Negate the sign of this basic word, returning a reference to it.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	*/
	template<unsigned int N>
	Basic_word<N>& Basic_word<N>::negate()
	{
		negate_sign(sign_byte);
		return *this;
	}

	/*
	* Return a new basic word of the same size, containing
	* only the given field, left shifted if necessary as far
	* as possible without losing any byte in the field.
	* Template parameters:
	*	N - Number of bytes of the basic word.
	* Parameters:
	*	field - Field to keep and left align.
	*/
	template<unsigned int N>
	Basic_word<N> Basic_word<N>::field_aligned_left(
			const Field_spec& field) const
	{
		Basic_word<N> copy{};
		copy.copy_range(*this, field);
		int shift_amount{(field.left == 0 ? 1 : field.left) - 1};
		copy.left_shift(shift_amount);
		return copy;
	}

	/*
	* Return a new basic word of the same size, containing
	* only the given field, right shifted if necessary as far
	* as possible without losing any byte in the field.
	* Template parameters:
	*	N - Number of bytes of the basic word.
	* Parameters:
	*	field - Field to keep and right align.
	*/
	template<unsigned int N>
	Basic_word<N> Basic_word<N>::field_aligned_right(
			const Field_spec& field) const
	{
		Basic_word<N> copy{};
		if (field.right != 0) {
			copy.copy_range(*this, field);
			int shift_amount{static_cast<int>(N) - field.right};
			copy.right_shift(shift_amount);
		}
		return copy;
	}

	/*
	* Return a new word containing only the given number of bytes
	* from this word taken from the left.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	amount - Number of left-most bytes desired.
	*/
	template<unsigned int N>
	Basic_word<N> Basic_word<N>::leftmost_bytes(int amount) const
	{
		if (amount > N)
			throw std::invalid_argument{"Requested too many bytes"};
		Basic_word copy{};
		copy.copy_range(*this, {1, amount});
		return copy;
	}

	/*
	* Return a new word containing the given number of bytes
	* from this word taken from the left, and the sign.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	amount - Number of left-most bytes desired.
	*/
	template<unsigned int N>
	Basic_word<N> Basic_word<N>::leftmost_with_sign(int amount) const
	{
		Basic_word copy{leftmost_bytes(amount)};
		copy.sign_byte = sign_byte;
		return copy;
	}

	/*
	* Return a new word containing the given number of bytes
	* taken from the right.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	amount - Number of right-most bytes desired.
	*/
	template<unsigned int N>
	Basic_word<N> Basic_word<N>::rightmost_bytes(int amount) const
	{
		if (amount > N)
			throw std::invalid_argument{"Requested too many bytes"};
		Basic_word copy{};
		copy.copy_range(*this, {static_cast<int>(N) - amount + 1, N});
		return copy;
	}

	/*
	* Return a new word containing the given number of bytes
	* taken from the right, and the sign.
	* Template parameters:
	*	N - Number of bytes of this basic word.
	* Parameters:
	*	amount - Number of right-most bytes desired.
	*/
	template<unsigned int N>
	Basic_word<N> Basic_word<N>::rightmost_with_sign(int amount) const
	{
		Basic_word copy{rightmost_bytes(amount)};
		copy.sign_byte = sign_byte;
		return copy;
	}


	/*** Basic_word input/output. ***/

	/*
	* Write the given basic word to the given output stream.
	* Template parameters:
	*	N - Number of bytes of the basic word.
	* Parameters:
	*	os - Output stream to write to.
	*	bw - Basic word to be written.
	*/
	template<unsigned int N>
	std::ostream& operator<<(std::ostream& os, const Basic_word<N>& bw)
	{
		// Save current formatting then set to not skip whitespace.
		std::ios_base::fmtflags f{os.flags()};
		os << std::noskipws;

		// Write basic word.
		os << bw.sign();
		for (int i = 1; i <= N; ++i)
			os << bw.byte(i);

		// Reset formatting.
		os.flags(f);

		return os;
	}

	/*
	* Read a basic word from the given input stream.
	* Template parameters:
	*	N - number of bytes of the basic word.
	* Parameters:
	*	is - Input stream to read from.
	*	bw - Basic word to read into.
	*/
	template<unsigned int N>
	std::istream& operator>>(std::istream& is, Basic_word<N>& bw)
	{
		// Create an invalid basic word to mark any input problems.
		Basic_word<N> temp{Sign::Invalid,
						   std::vector<Byte>(N, INVALID_BYTE)};

		// Save current formatting then set to not skip whitespace.
		std::ios_base::fmtflags f{is.flags()};
		is >> std::noskipws;

		// Read basic word.
		is >> temp.sign();
		for (int i = 1; i <= N; ++i) {
			is >> temp.byte(i);
		}

		// Reset formatting.
		is.flags(f);

		bw = temp;
		return is;
	}
}
#endif

