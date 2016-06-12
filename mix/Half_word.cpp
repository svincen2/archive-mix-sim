#include "Half_word.h"

namespace MIX
{
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
