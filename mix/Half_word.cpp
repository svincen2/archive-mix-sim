#include "Half_word.h"

namespace MIX
{
	/*
	* Construct a half word with the given values.
	*/
	Half_word::Half_word(Sign s, Byte b1, Byte b2)
		: Basic_word{}
	{
		sign(s);
		byte(1) = b1;
		byte(2) = b2;
	}

	/*
	* Narrows a word to fit into a half word.
	* Everything from the word is copied except bytes 1, 2, and 3.
	*/
	Half_word& Half_word::operator=(const Word& word)
	{
		sign(word.sign());
		byte(1) = word.byte(4);
		byte(2) = word.byte(5);
	}
}
