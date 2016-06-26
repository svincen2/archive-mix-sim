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

SCENARIO("Shifting right")
{
	GIVEN("A basic word")
	{
		Basic_word<5> bw{Sign::Minus, {1, 2, 3, 4, 5}};
		WHEN("Shifting by more than the number of bytes")
		{
			bw.right_shift(bw.num_bytes + 1);
			THEN("All bytes are 0")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 0);
				REQUIRE(bw.byte(2) == 0);
				REQUIRE(bw.byte(3) == 0);
				REQUIRE(bw.byte(4) == 0);
				REQUIRE(bw.byte(5) == 0);
			}
		}
		WHEN("Shifting by less than the number of bytes")
		{
			bw.right_shift(bw.num_bytes - 2);
			THEN("Bytes are shifted, and left-filled with 0")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 0);
				REQUIRE(bw.byte(2) == 0);
				REQUIRE(bw.byte(3) == 0);
				REQUIRE(bw.byte(4) == 1);
				REQUIRE(bw.byte(5) == 2);
			}
		}
		WHEN("Shifting all bytes")
		{
			bw.right_shift(bw.num_bytes);
			THEN("All bytes are 0")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 0);
				REQUIRE(bw.byte(2) == 0);
				REQUIRE(bw.byte(3) == 0);
				REQUIRE(bw.byte(4) == 0);
				REQUIRE(bw.byte(5) == 0);
			}
		}
		WHEN("Shifting by a negative amount")
		{
			
			THEN("Invalid argument is thrown")
			{
				REQUIRE_THROWS_AS(bw.right_shift(-1), std::invalid_argument);
			}
		}
		WHEN("Shifting by 0")
		{
			bw.right_shift(0);
			THEN("Word is unnaffected")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 1);
				REQUIRE(bw.byte(2) == 2);
				REQUIRE(bw.byte(3) == 3);
				REQUIRE(bw.byte(4) == 4);
				REQUIRE(bw.byte(5) == 5);
			}
		}
		WHEN("Copy-shifting")
		{
			Basic_word<5> copy{bw.right_shifted(3)};
			THEN("The new word is shifted correctly, the old is unnaffected")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 1);
				REQUIRE(bw.byte(2) == 2);
				REQUIRE(bw.byte(3) == 3);
				REQUIRE(bw.byte(4) == 4);
				REQUIRE(bw.byte(5) == 5);

				REQUIRE(copy.sign() == Sign::Minus);
				REQUIRE(copy.byte(1) == 0);
				REQUIRE(copy.byte(2) == 0);
				REQUIRE(copy.byte(3) == 0);
				REQUIRE(copy.byte(4) == 1);
				REQUIRE(copy.byte(5) == 2);
			}
		}
	}
}

SCENARIO("Left shifting")
{
	GIVEN("A basic word")
	{
		Basic_word<5> bw{Sign::Minus, {1, 2, 3, 4, 5}};
		WHEN("Shifting by a negative amount")
		{
			THEN("Invalid argument is thrown")
			{
				REQUIRE_THROWS_AS(bw.left_shift(-1), std::invalid_argument);
			}
		}
		WHEN("Shifting by more than the number of bytes")
		{
			bw.left_shift(bw.num_bytes + 2);
			THEN("All bytes are 0")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 0);
				REQUIRE(bw.byte(2) == 0);
				REQUIRE(bw.byte(3) == 0);
				REQUIRE(bw.byte(4) == 0);
				REQUIRE(bw.byte(5) == 0);
			}
		}
		WHEN("Shifting by less than the number of bytes")
		{
			bw.left_shift(bw.num_bytes - 3);
			THEN("Bytes are shifted, and right-filled with 0")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 3);
				REQUIRE(bw.byte(2) == 4);
				REQUIRE(bw.byte(3) == 5);
				REQUIRE(bw.byte(4) == 0);
				REQUIRE(bw.byte(5) == 0);
			}
		}
		WHEN("Shifting all bytes")
		{
			bw.left_shift(bw.num_bytes);
			THEN("All bytes are 0")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 0);
				REQUIRE(bw.byte(2) == 0);
				REQUIRE(bw.byte(3) == 0);
				REQUIRE(bw.byte(4) == 0);
				REQUIRE(bw.byte(5) == 0);
			}
		}
		WHEN("Shifting by 0")
		{
			bw.left_shift(0);
			THEN("Word is unnaffected")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 1);
				REQUIRE(bw.byte(2) == 2);
				REQUIRE(bw.byte(3) == 3);
				REQUIRE(bw.byte(4) == 4);
				REQUIRE(bw.byte(5) == 5);
			}
		}
		WHEN("Copy-shifting")
		{
			Basic_word<5> copy{bw.left_shifted(3)};
			THEN("The new word is shifted correctly, the old is unnaffected")
			{
				REQUIRE(bw.sign() == Sign::Minus);
				REQUIRE(bw.byte(1) == 1);
				REQUIRE(bw.byte(2) == 2);
				REQUIRE(bw.byte(3) == 3);
				REQUIRE(bw.byte(4) == 4);
				REQUIRE(bw.byte(5) == 5);

				REQUIRE(copy.sign() == Sign::Minus);
				REQUIRE(copy.byte(1) == 4);
				REQUIRE(copy.byte(2) == 5);
				REQUIRE(copy.byte(3) == 0);
				REQUIRE(copy.byte(4) == 0);
				REQUIRE(copy.byte(5) == 0);
			}
		}
	}
}

SCENARIO("Copying a range")
{
	GIVEN("Two basic words")
	{
		Basic_word<5> first{Sign::Plus, {1, 2, 3, 4, 5}};
		Basic_word<5> second{Sign::Minus, {6, 7, 8, 9, 0}};
		WHEN("First index in range is negative")
		{
			THEN("Invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(first.copy_range(second, -1, 0),
								  std::invalid_argument);
			}
		}
		WHEN("First index is greater than last index")
		{
			THEN("Invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(first.copy_range(second, 1, 0),
								  std::invalid_argument);
			}
		}
		WHEN("Last index is greater than the number of bytes")
		{
			THEN("Invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(first.copy_range(second, 0, 6),
								  std::invalid_argument);
			}
		}
		WHEN("Copying entire range")
		{
			first.copy_range(second, 0, 5);
			THEN("All bytes from second are copied into first, including sign")
			{
				REQUIRE(first.sign() == second.sign());
				REQUIRE(first.byte(1) == second.byte(1));
				REQUIRE(first.byte(2) == second.byte(2));
				REQUIRE(first.byte(3) == second.byte(3));
				REQUIRE(first.byte(4) == second.byte(4));
				REQUIRE(first.byte(5) == second.byte(5));
			}
		}
		WHEN("Copying range that doesn't include the sign")
		{
			first.copy_range(second, 1, 4);
			THEN("Only applicable bytes are copied, not the sign")
			{
				REQUIRE(first.sign() == Sign::Plus);
				REQUIRE(first.byte(1) == second.byte(1));
				REQUIRE(first.byte(2) == second.byte(2));
				REQUIRE(first.byte(3) == second.byte(3));
				REQUIRE(first.byte(4) == second.byte(4));
				REQUIRE(first.byte(5) == 5);
			}
		}
		WHEN("Copying a range of a single byte")
		{
			first.copy_range(second, 3, 3);
			THEN("Only the byte is copied")
			{
				REQUIRE(first.sign() == Sign::Plus);
				REQUIRE(first.byte(1) == 1);
				REQUIRE(first.byte(2) == 2);
				REQUIRE(first.byte(3) == 8);
				REQUIRE(first.byte(4) == 4);
				REQUIRE(first.byte(5) == 5);
			}
		}
		WHEN("Copying only the sign")
		{
			first.copy_range(second, 0, 0);
			THEN("Only the sign is copied")
			{
				REQUIRE(first.sign() == Sign::Minus);
				REQUIRE(first.byte(1) == 1);
				REQUIRE(first.byte(2) == 2);
				REQUIRE(first.byte(3) == 3);
				REQUIRE(first.byte(4) == 4);
				REQUIRE(first.byte(5) == 5);
			}
		}
	}
}
