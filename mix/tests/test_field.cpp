#include "catch.hpp"
#include "../Field.h"
#include "../Word.h"

using namespace MIX;

SCENARIO("Invalid fields")
{
	GIVEN("A field where the left value is negative")
	{
		WHEN("The fully parameterized constructor is called")
		{
			THEN("An range_error exception is thrown")
			{
				REQUIRE_THROWS_AS(Field(-1, 5), std::range_error);
			}
		}

		WHEN("Field is changed to an invalid state")
		{
			Field f{};
			f.left = -1;
			THEN("Calling valid throws a range_error")
			{
				REQUIRE_THROWS_AS(f.validate(), std::range_error);
			}
		}
	}

	GIVEN("A field where the right value is too big")
	{
		WHEN("The fully parameterized constructor is called")
		{
			THEN("A range_error is thrown")
			{
				REQUIRE_THROWS_AS(Field(0, Word::num_bytes + 1),
								  std::range_error);
			}
		}

		WHEN("Field is changed to an invalid state")
		{
			Field f{};
			f.right = Word::num_bytes + 1;
			THEN("Calling valid throws a range_error")
			{
				REQUIRE_THROWS_AS(f.validate(), std::range_error);
			}
		}
	}

	GIVEN("A field where left is bigger than right")
	{
		WHEN("The fully parameterized constructor is called")
		{
			THEN("A range_error is thrown")
			{
				REQUIRE_THROWS_AS(Field(2, 1), std::range_error);
			}
		}

		WHEN("Field is changed to an invalid state")
		{
			Field f{};
			f.left = 2;
			f.right = 1;
			THEN("Calling valid throws a range_error")
			{
				REQUIRE_THROWS_AS(f.validate(), std::range_error);
			}
		}
	}
}
