#include "catch.hpp"
#include "../Field_spec.h"

using namespace mix;

SCENARIO("Constructing a field spec")
{
	GIVEN("Nothing")
	{
		WHEN("Construting an invalid field spec")
		{
			THEN("An invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(Field_spec(-1, 0),
								  std::invalid_argument);
				REQUIRE_THROWS_AS(Field_spec(4, 2),
								  std::invalid_argument);
			}
		}
	}
}

SCENARIO("Encoding a field spec")
{
	GIVEN("A field specification")
	{
		WHEN("Field spec of (0:5) is encoded")
		{
			Field_spec fs{0, 5};
			int encoded{fs.encode()};
			THEN("The encoded field is 5")
			{
				REQUIRE(encoded == 5);
			}
		}
		WHEN("Field spec of (4:4) is encoded")
		{
			Field_spec fs{4, 4};
			int encoded{fs.encode()};
			THEN("The encoded field is 36")
			{
				REQUIRE(encoded == 36);
			}
		}
		WHEN("Field spec of (1:5) is encoded")
		{
			Field_spec fs{1, 5};
			int encoded{fs.encode()};
			THEN("The encoded field is 13")
			{
				REQUIRE(encoded == 13);
			}
		}
	}
}
