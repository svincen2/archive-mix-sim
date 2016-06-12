#ifndef MIX_HALF_WORD_H
#define MIX_HALF_WORD_H

#include "Basic_word.h"
#include "Word.h"

namespace MIX
{
	// A half word has a sign and 2 bytes.
	class Half_word : public Basic_word<2>
	{
	public:
		// Parameterized constructor with default values.
		Half_word(Sign s = Sign::Plus,
				  Byte b1 = 0,
				  Byte b2 = 0);

		// Narrow to a half word.
		Half_word& operator=(const Word&);
	};
}
#endif
