#include "Field_spec.h"

namespace mix
{
	/*
	* Encode the field specification.
	*/
	int Field_spec::encode() const
	{
		int encoded = right;
		encoded += (left * 8);
		return encoded;
	}

	/*
	* Decode an encoded field specification.
	* Parameters:
	*	encoded - Encoded field spec.
	*/
	Field_spec decode_field_spec(int encoded)
	{
		int left{encoded / 8};
		int right{encoded % 8};
		return Field_spec{left, right};
	}
}
