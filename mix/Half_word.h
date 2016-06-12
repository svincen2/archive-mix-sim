#ifndef MIX_HALF_WORD_H
#define MIX_HALF_WORD_H

#include "Basic_word.h"
#include "Word.h"
#include <initializer_list>

namespace MIX
{
	// A half word has a sign and 2 bytes.
	class Half_word : public Basic_word<2>
	{
	public:
		// Inherit base constructors.
		using Basic_word<2>::Basic_word;

		// Narrowing conversion assignment.
		Half_word& operator=(const Word&);
	};
}
#endif
