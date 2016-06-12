#include "catch.hpp"
#include "../Half_word.h"
#include "../Word.h"

using namespace MIX;

SCENARIO("Narrowing from Word")
{
	GIVEN("A word [+|1|2|3|4|5]")
	{
		Word w{1, 2, 3, 4, 5};
		WHEN("Converting to a half word using assignment operator")
		{
			Half_word hw{};
			hw = w;
			THEN("Only the rightmost 2 bytes and sign are copied")
			{
				REQUIRE(hw.sign() == Sign::Plus);
				REQUIRE(hw.byte(1) == 4);
				REQUIRE(hw.byte(2) == 5);
			}
		}
	}
}
