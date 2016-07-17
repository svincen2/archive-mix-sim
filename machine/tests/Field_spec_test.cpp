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

SCENARIO("Decoding encoded field spec")
{
	GIVEN("A field spec encoding of 0")
	{
		int encoded{0};
		WHEN("Decoded")
		{
			Field_spec fs{decode_field_spec(encoded)};
			THEN("The default field spec is returned")
			{
				REQUIRE(fs == Field_spec::DEFAULT);
			}
		}
	}
	GIVEN("A field spec encoding of 36")
	{
		int encoded{36};
		WHEN("Decoded")
		{
			Field_spec fs{decode_field_spec(encoded)};
			THEN("A field spec of (4:4) is returned")
			{
				Field_spec expected{4, 4};
				REQUIRE(fs == expected);
			}
		}
	}
}

SCENARIO("Testing equality")
{
	GIVEN("A field specification")
	{
		Field_spec fs1{0, 5};
		WHEN("Compared to a field spec with same left and right values")
		{
			Field_spec fs2{0, 5};
			THEN("Equality operator returns true")
			{
				REQUIRE((fs1 == fs2) == true);
			}
		}
		WHEN("Compared to a field spec with different left and right values")
		{
			Field_spec fs2{1, 3};
			THEN("Equality operator return false")
			{
				REQUIRE((fs1 == fs2) == false);
			}
		}
	}
}

SCENARIO("Field_spec sizes")
{
	GIVEN("A field spec")
	{
		Field_spec fs{0, 5};
		WHEN("Asked for the size of the field spec")
		{
			THEN("The size includes all bytes and the sign, if included")
			{
				REQUIRE(fs.size() == 6);
			}
		}
		WHEN("Asked for the bytes of the field spec")
		{
			THEN("The size includes only the bytes")
			{
				REQUIRE(fs.bytes() == 5);
			}
		}
	}
}
