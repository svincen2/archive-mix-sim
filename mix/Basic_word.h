#ifndef MIX_BASIC_WORD_H
#define MIX_BASIC_WORD_H

#include "Byte.h"
#include "Sign.h"
#include "Field.h"
#include <initializer_list>
#include <stdexcept>
#include <vector>

namespace MIX
{
	/*
	* Template for the basic format of MIX machine words.
	* Bytes are indexed starting at 1.
	*/
	template<unsigned int Size>
	class Basic_word
	{
	public:
		static const unsigned int num_bytes = Size;

		// Constructors.
		Basic_word();
		Basic_word(const std::initializer_list<Byte>&);
		Basic_word(Sign, const std::initializer_list<Byte>&);

		// Comparison operator.
		bool operator==(const Basic_word&);

		// Accessors.
		const Sign& sign() const { return _sign; }
		const Byte& byte(int) const;
		std::vector<Byte> get_bytes(int, int) const;
		std::vector<Byte> from_right(int) const;

		// Mutators.
		void sign(Sign);
		Byte& byte(int);
		void set_bytes(int, int, const std::vector<Byte>&);
		void set_right(const std::vector<Byte>&);
		void negate();

	private:
		Sign _sign;
		std::vector<Byte> _bytes;
	};

	/*
	* Empty constructor.
	* Sets basic word to +0.
	*/
	template<unsigned int Size>
	Basic_word<Size>::Basic_word()
		: _sign{Sign::Plus}, _bytes(num_bytes)
	{
	}

	/*
	* Variadic constructor with sign set to Sign::Plus.
	*/
	template<unsigned int Size>
	Basic_word<Size>::Basic_word(const std::initializer_list<Byte>& b)
		: Basic_word{Sign::Plus, b}
	{
	}

	/*
	* Variadic constructor with sign.
	*/
	template<unsigned int Size>
	Basic_word<Size>::Basic_word(Sign s, const std::initializer_list<Byte>& b)
		: _sign{s}, _bytes{}
	{
		if(Size < b.size())
			throw std::invalid_argument{"Too many bytes given to constructor"};
		for(auto pb = b.begin(); pb != b.end(); ++pb)
			_bytes.push_back(*pb);
		while(_bytes.size() < Size)
			_bytes.push_back(0);
	}

	/*
	* Returns whether or not the two basic words are identical.
	*/
	template<unsigned int Size>
	bool Basic_word<Size>::operator==(const Basic_word<Size>& other)
	{
		return _sign == other._sign && _bytes == other._bytes;
	}

	/*
	* Get the byte at the given index.
	* Read only.
	*/
	template<unsigned int Size>
	const Byte& Basic_word<Size>::byte(int index) const
	{
		if(index < 1 || num_bytes < index)
			throw std::invalid_argument{"Index out of bounds"};
		return _bytes[index - 1];
	}

	/*
	* Get the byte at the given index.
	* Read and write.
	*/
	template<unsigned int Size>
	Byte& Basic_word<Size>::byte(int index)
	{
		if(index < 1 || num_bytes < index)
			throw std::invalid_argument{"Index out of bounds"};
		return _bytes[index - 1];
	}

	/*
	* Return copies of the bytes in the given range: [begin, end].
	*/
	template<unsigned int Size>
	std::vector<Byte> Basic_word<Size>::get_bytes(int begin, int end) const
	{
		std::vector<Byte> vb{};
		for(int i = begin; i <= end; ++i)
			vb.push_back(byte(i));
		return vb;
	}

	/*
	* Return copies of the given amount of bytes, taken from the right.
	*/
	template<unsigned int Size>
	std::vector<Byte> Basic_word<Size>::from_right(int amount) const
	{
		std::vector<Byte> vb{};
		if(Size < amount)
			throw std::invalid_argument{"Amount too large"};
		for(int i = Size - amount + 1; i <= Size; ++i)
			vb.push_back(byte(i));
		return vb;
	}

	/*
	* Sets the bytes in the given range [begin, end] to the bytes given.
	*/
	template<unsigned int Size>
	void Basic_word<Size>::set_bytes(int begin,
									 int end,
									 const std::vector<Byte>& vb)
	{
		if(vb.size() != (end - begin + 1))
			throw std::invalid_argument{"Wrong number of bytes"};
		for(int i = begin, j = 0; i <= end; ++i, ++j)
		{
			byte(i) = vb[j];
		}
	}

	/*
	* Set the rightmost bytes to the given bytes.
	*/
	template<unsigned int Size>
	void Basic_word<Size>::set_right(const std::vector<Byte>& vb)
	{
		if(Size < vb.size())
			throw std::invalid_argument{"Too many bytes given"};
		auto pb = vb.begin();
		for(int i = Size - vb.size(); i < Size; ++i, ++pb)
			_bytes[i] = *pb;
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

	/*
	* Reads the field of the given word as an integer value.
	*/
	template<unsigned int Size>
	int to_int(const Basic_word<Size>& bw, const Field& field)
	{
		// Ensure word has enough bytes.
		if(Size + 1 < field.size())
			throw std::invalid_argument{"Field is too big"};
		int result{0};
		unsigned int begin = (field.left == 0 ? 1 : field.left);
		unsigned int num_bytes{field.right - begin};
		for(int i = begin; i <= field.right; ++i)
		{
			unsigned int bits{bw.byte(i) & bit_mask};
			bits <<= (byte_size * num_bytes--);
			result |= bits;
		}
		if(field.left == 0 && bw.sign() == Sign::Minus)
			result = -result;
		return result;
	}

	/*
	* Negates the sign of this basic word.
	*/
	template<unsigned int Size>
	void Basic_word<Size>::negate()
	{
		if(_sign == Sign::Plus) _sign = Sign::Minus;
		else _sign = Sign::Plus;
	}

}
#endif
