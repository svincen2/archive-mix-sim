#include "Field_spec.h"
#include <stdexcept>

namespace mix
{
	/*
	* Construct a field specification.
	*/
	Field_spec::Field_spec(int l = 0, int r = 0)
		: left{l}, right{r}
	{
		if (!valid())
			throw std::invalid_argument{"Invalid field specification"};
	}

	/*
	* Checks if the field spec is valid.
	*/
	bool Field_spec::valid() const
	{
		bool is_valid{true};
		if (left < 0) is_valid = false;
		if (left > right) is_valid = false;
		return is_valid;
	}

	/*
	* Determines whether or not the given field spec is equal to this one.
	*/
	bool Field_spec::operator==(const Field_spec& fs) const
	{
		return left == fs.left && right == fs.right;
	}

	/*
	* Determines whether or not the given field spec is different to this one.
	*/
	bool Field_spec::operator!=(const Field_spec& fs) const
	{
		return !(*this == fs);
	}

	/*
	* Return the number of bytes included in the field specification.
	* Excludes the sign.
	*/
	int Field_spec::bytes() const
	{
		int bytes{size()};
		if (left == 0) --bytes;
		return bytes;
	}

	/*
	* Returns the number of bytes in the range specified by this field spec.
	*/
	int Field_spec::size() const
	{
		return right - left + 1;
	}

	/*
	* Encode the field specification.
	*/
	int Field_spec::encode() const
	{
		int encoded = right;
		encoded += (left * ENCODE_VALUE);
		return encoded;
	}

	/*
	* Returns whether or not the sign is part of the specified field.
	*/
	bool Field_spec::contains_sign() const
	{
		return left == 0;
	}

	/*
	* Decode an encoded field specification.
	* Parameters:
	*	encoded - Encoded field spec.
	*/
	Field_spec decode_field_spec(int encoded)
	{
		int left{encoded / Field_spec::ENCODE_VALUE};
		int right{encoded % Field_spec::ENCODE_VALUE};
		return Field_spec{left, right};
	}
}
