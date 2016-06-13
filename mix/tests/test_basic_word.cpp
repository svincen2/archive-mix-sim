#include "catch.hpp"
#include "../Basic_word.h"
#include <sstream>

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

SCENARIO("Constructing with a variable number of arguments")
{
	GIVEN("Argument list {1, 2, 3}")
	{
		std::initializer_list<Byte> list{1, 2, 3};
		WHEN("Used to construct a basic word with 5 bytes")
		{
			Basic_word<5> bw{list};
			THEN("The word [+|1|2|3|0|0] is constructed")
			{
				REQUIRE(bw.sign() == Sign::Plus);
				REQUIRE(bw.byte(1) == 1);
				REQUIRE(bw.byte(2) == 2);
				REQUIRE(bw.byte(3) == 3);
				REQUIRE(bw.byte(4) == 0);
				REQUIRE(bw.byte(5) == 0);
			}
		}
	}

	GIVEN("An argument list of {1, 2, 3, 4, 5} and a sign of Sign::Minus")
	{
		std::initializer_list<Byte> list{1, 2, 3, 4, 5};
		Sign s{Sign::Minus};
		WHEN("Used to construct a basic word with 5 bytes")
		{
			Basic_word<5> bw{s, list};
			THEN("The word [-|1|2|3|4|5] is constructed")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 1);
				REQUIRE(bw.byte(2) == 2);
				REQUIRE(bw.byte(3) == 3);
				REQUIRE(bw.byte(4) == 4);
				REQUIRE(bw.byte(5) == 5);
			}
		}
	}

	GIVEN("An argument list that is too big")
	{
		std::initializer_list<Byte> list{1, 2, 3, 4, 5, 6};
		WHEN("Used to construct a basic word that is too small")
		{
			THEN("An invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(Basic_word<2>(Sign::Plus, list),
								  std::invalid_argument);
				REQUIRE_THROWS_AS((Basic_word<2>{list}), std::invalid_argument);
			}
		}
	}
}

SCENARIO("Testing equality")
{
	GIVEN("Two identical basic words")
	{
		Basic_word<2> bw1{Sign::Plus, {1, 2}};
		Basic_word<2> bw2{Sign::Plus, {1, 2}};
		WHEN("Compared for equality")
		{
			bool equal{bw1 == bw2};
			THEN("The two are equal")
			{
				REQUIRE(equal == true);
			}
		}
	}

	GIVEN("Two different basic words of the same size")
	{
		Basic_word<5> bw1{Sign::Plus, {1, 2, 3, 4, 5}};
		Basic_word<5> bw2{};
		WHEN("Compared for equality")
		{
			bool equal{bw1 == bw2};
			THEN("The two are not equal")
			{
				REQUIRE(equal == false);
			}
		}
	}
}

SCENARIO("Setting rightmost bytes")
{
	GIVEN("A word of +0")
	{
		Basic_word<5> bw{};
		WHEN("{1, 2, 3} is set to right bytes of word")
		{
			bw.set_right(std::vector<Byte>{1, 2, 3});
			THEN("The word becomes [+|0|0|1|2|3]")
			{
				REQUIRE(bw.byte(1) == 0);
				REQUIRE(bw.byte(2) == 0);
				REQUIRE(bw.byte(3) == 1);
				REQUIRE(bw.byte(4) == 2);
				REQUIRE(bw.byte(5) == 3);
			}
		}
	}
}

SCENARIO("Outputing a basic word")
{
	GIVEN("A word with 5 bytes")
	{
		Basic_word<5> bw{Sign::Plus, {1, 2, 3, 4, 5}};
		WHEN("Output to a string")
		{
			std::ostringstream oss{};
			oss << bw;
			THEN("[+|1|2|3|4|5] is output")
			{
				REQUIRE("[+|1|2|3|4|5]" == oss.str());
			}
		}
	}
}
