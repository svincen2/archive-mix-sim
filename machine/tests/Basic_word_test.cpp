#include "catch.hpp"
#include "../Basic_word.h"

using namespace mix;

SCENARIO("Copying a basic word")
{
	GIVEN("A basic word")
	{
		Basic_word<5> bw{Sign::Plus, {1, 2, 3, 4, 5}};
		WHEN("The word is copied with a constructor")
		{
			Basic_word<5> copy{bw};
			THEN("All the bytes are the same")
			{
				REQUIRE(copy.sign() == bw.sign());
				REQUIRE(copy.byte(1) == bw.byte(1));
				REQUIRE(copy.byte(2) == bw.byte(2));
				REQUIRE(copy.byte(3) == bw.byte(3));
				REQUIRE(copy.byte(4) == bw.byte(4));
				REQUIRE(copy.byte(5) == bw.byte(5));
			}
		}
		WHEN("The word is copied with an assignment")
		{
			Basic_word<5> copy{};
			copy = bw;
			THEN("All the bytes are the same")
			{
				REQUIRE(copy.sign() == bw.sign());
				REQUIRE(copy.byte(1) == bw.byte(1));
				REQUIRE(copy.byte(2) == bw.byte(2));
				REQUIRE(copy.byte(3) == bw.byte(3));
				REQUIRE(copy.byte(4) == bw.byte(4));
				REQUIRE(copy.byte(5) == bw.byte(5));
			}
		}
	}
}

SCENARIO("Moving a basic word")
{
	GIVEN("A basic word")
	{
		Basic_word<5> bw{Sign::Plus, {1, 2, 3, 4, 5}};
		WHEN("The word is moved with a constructor")
		{
			Basic_word<5> moved{std::move(bw)};
			THEN("All bytes are the same")
			{
				REQUIRE(moved.sign() == Sign::Plus);
				REQUIRE(moved.byte(1) == 1);
				REQUIRE(moved.byte(2) == 2);
				REQUIRE(moved.byte(3) == 3);
				REQUIRE(moved.byte(4) == 4);
				REQUIRE(moved.byte(5) == 5);
			}
		}
		WHEN("The word is moved with an assignment")
		{
			Basic_word<5> moved{};
			moved = std::move(bw);
			THEN("All bytes are the same")
			{
				REQUIRE(moved.sign() == Sign::Plus);
				REQUIRE(moved.byte(1) == 1);
				REQUIRE(moved.byte(2) == 2);
				REQUIRE(moved.byte(3) == 3);
				REQUIRE(moved.byte(4) == 4);
				REQUIRE(moved.byte(5) == 5);
			}
		}
	}
}

SCENARIO("Converting basic words")
{
	GIVEN("A basic word")
	{
		Basic_word<3> bw{Sign::Minus, {1, 2, 3}};
		WHEN("Converting to a smaller word")
		{
			Basic_word<2> smaller{bw};
			THEN("The left-most bytes are dropped")
			{
				REQUIRE(smaller.sign() == Sign::Minus);
				REQUIRE(smaller.byte(1) == bw.byte(2));
				REQUIRE(smaller.byte(2) == bw.byte(3));
			}
		}
		WHEN("Converting to a larger word")
		{
			Basic_word<4> larger{bw};
			THEN("The left-most bytes are set to 0")
			{
				REQUIRE(larger.sign() == Sign::Minus);
				REQUIRE(larger.byte(1) == 0);
				REQUIRE(larger.byte(2) == bw.byte(1));
				REQUIRE(larger.byte(3) == bw.byte(2));
				REQUIRE(larger.byte(4) == bw.byte(3));
			}
		}
	}
}
