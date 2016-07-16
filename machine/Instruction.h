#ifndef MIX_MACHINE_INSTRUCTION_H
#define MIX_MACHINE_INSTRUCTION_H

#include "Byte.h"
#include "Field_spec.h"
#include "Word.h"

namespace mix
{
	// A wrapper class to add functions to a Word representing
	// a machine instruction.
	class Instruction : public Word
	{
	public:
		// Constants for the parts of an instruction.
		static const Field_spec ADDRESS_FIELD;
		static const unsigned int INDEX_SPEC{3};
		static const unsigned int FIELD_SPEC{4};
		static const unsigned int OP_CODE{5};

		/* Constructors. */

		// Wrapper.
		Instruction(const Word&);

		// Bring base constructors into scope.
		using Word::Word;

		// Functions for accessing parts of an instruction.
		int address() const;
		Byte index_spec() const;
		Byte field_spec() const;
		Byte op_code() const;
	};
}
#endif

