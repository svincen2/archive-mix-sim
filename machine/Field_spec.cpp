#include "Field_spec.h"
#include <stdexcept>

namespace mix
{
	// Address field specification.
	Field_spec Field_spec::ADDRESS{0, 2};

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
