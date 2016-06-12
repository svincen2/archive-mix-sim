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

	GIVEN("A basic word with 2 bytes")
	{
		Basic_word<2> bw{};
		WHEN("The field to read is too large")
		{
			THEN("Invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(to_int(bw, Field(0, 3)),
								  std::invalid_argument);
			}
		}
	}
}

SCENARIO("Getting ranges of bytes")
{
	GIVEN("A basic word with 5 bytes")
	{
		Basic_word<5> bw{};
		bw.byte(1) = 1;
		bw.byte(2) = 2;
		bw.byte(3) = 3;
		bw.byte(4) = 4;
		bw.byte(5) = 5;
		WHEN("Get bytes [1, 5]")
		{
			std::vector<Byte> vb{bw.get_bytes(1, 5)};
			THEN("All bytes asked for are returned, in the right order")
			{
				REQUIRE(vb.size() == 5);
				REQUIRE(vb[0] == 1);
				REQUIRE(vb[1] == 2);
				REQUIRE(vb[2] == 3);
				REQUIRE(vb[3] == 4);
				REQUIRE(vb[4] == 5);
			}
		}
	}
}
