#ifndef MIX_FIELD_H
#define MIX_FIELD_H

#include "Byte.h"
#include "Instruction.h"

namespace MIX
{
	/*
	* A MIX machine instruction field specification.
	* Specifies the bytes of a word to be utilized in an instruction.
	*/
	struct Field
	{
		unsigned int left;
		unsigned int right;

		// Constructors.
		Field();
		Field(unsigned int, unsigned int);
		Field(const Field&);

		// Number of bytes in range specified by field.
		unsigned int size() { return right - left + 1; }

		// Static factory methods.
		static const Field address();
	};

	// Convert a number to a field specification.
	Field to_field(const unsigned int);

	// Convert a field specification to a number.
	Byte to_byte(const Field&);
}
#endif
