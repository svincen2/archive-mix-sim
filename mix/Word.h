#ifndef MIX_WORD_H
#define MIX_WORD_H

#include "Basic_word.h"

namespace MIX
{
	// A word has a sign and 5 bytes.
	class Word : public Basic_word<5>
	{
	public:
		// Inherit constructors.
		using Basic_word<5>::Basic_word;
	
		// Parameterized constructor with default values.
		Word(Sign s = Sign::Plus,
			 Byte b1 = 0,
			 Byte b2 = 0,
			 Byte b3 = 0,
			 Byte b4 = 0,
			 Byte b5 = 0);
		};
}
#endif
