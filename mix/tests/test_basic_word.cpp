#include "catch.hpp"
#include "../Basic_word.h"

using namespace MIX;

SCENARIO("Read a basic word field as an integer")
{
	GIVEN("A basic word with 2 bytes set to +0")
	{
		Basic_word<2> bw{};
		bw.byte(1) = 0;
		bw.byte(2) = 0;
		WHEN("The entire word is read as an integer")
		{
			int i{to_int(bw, Field{0, 2})};
			THEN("Integer read is +0")
			{
				REQUIRE(i == 0);
			}
		}
	}

	GIVEN("A basic word with 2 bytes set to [+|3f|3f]")
	{
		Basic_word<2> bw{};
		bw.byte(1) = 0x3f;
		bw.byte(2) = 0x3f;
		WHEN("The entire word is read as an integer")
		{
			int i{to_int(bw, Field{0, 2})};
			THEN("Integer read is +4095")
			{
				REQUIRE(i == 4095);
			}
		}
	}

	GIVEN("A basic word with 5 bytes set to [+|1|0|0|0|0]")
	{
		Basic_word<5> bw{};
		bw.byte(1) = 1;
		WHEN("The field (0:2) is read as an integer")
		{
			int i{to_int(bw, Field{0, 2})};
			THEN("Integer read is +0x40")
			{
				REQUIRE(i == 0x40);
			}
		}
	}

	GIVEN("A basic word with 5 bytes")
	{
		Basic_word<5> bw{};
		WHEN("The field to read is too large")
		{
			THEN("Invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(to_int(bw, Field(0, 6)),
								  std::invalid_argument);
			}
		}
	}
}
