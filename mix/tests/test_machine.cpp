#include "catch.hpp"
#include "../Machine.h"
#include "../Word.h"
#include "../Field.h"

using namespace MIX;

SCENARIO("Reading address specifications")
{
  Machine mix{};
  GIVEN("An Instruction of .byte(+|1|0|0|0|0)")
  {
	Word instruction{Sign::Plus, 1, 0};
	WHEN("The address is read by the machine")
	{
	  const int address{mix.read_address(instruction)};
	  THEN("Address read is 0x40")
	  {
		REQUIRE(address == 0x40);
	  }
	}
  }

  GIVEN("An Instruction of .byte(+|3f|3f|0|0|0)")
  {
	Word instruction{Sign::Plus, 0x3f, 0x3f};
	WHEN("The address is read by the machine")
	{
	  const int address{mix.read_address(instruction)};
	  THEN("Address read is 0xfff")
	  {
		REQUIRE(address == 0xfff);
	  }
	}
  }

  GIVEN("And Instruction of .byte(+|ff|ff|0|0|0)")
  {
	Word instruction{Sign::Plus, 0xff, 0xff};
	WHEN("The address is read by the machine")
	{
	  const int address{mix.read_address(instruction)};
	  THEN("Address read is 0xfff")
	  {
		REQUIRE(address == 0xfff);
	  }
	}
  }

  GIVEN("An instruction with an index specification")
  {
	Half_word hw{Sign::Plus, 0, 1};
	Word instruction{Sign::Plus, 0, 1, 1};
	mix.index_register(1) = hw;
	WHEN("The address is read by the machine")
	{
	  const int address{mix.read_address(instruction)};
	  THEN("Address read is 2")
	  {
		REQUIRE(address == 2);
	  }
	}
  }
}

SCENARIO("Reading the field specification")
{
  Machine mix{};
  GIVEN("An Instruction of .byte(+|0|0|0|5|0)")
  {
	Word instruction{Sign::Plus, 0, 0, 0, 5};
	WHEN("Machine reads field specification")
	{
	  const Field f{mix.read_field(instruction)};
	  THEN("Field specification is (0:5)")
	  {
		REQUIRE(f.left == 0);
		REQUIRE(f.right == 5);
	  }
	}
  }
}

SCENARIO("Reading a field of a word")
{
	Machine mix{};
	GIVEN("A word and a field")
	{
		Word w{Sign::Minus, 1, 2, 3, 4, 5};
		Field f{0, 3};
		WHEN("Machine gets the bytes within the specified field")
		{
			const Word w2{mix.get_bytes(w, f)};
			THEN("All bytes are copied, and right shifted")
			{
				REQUIRE(w2.sign() == Sign::Minus);
				REQUIRE(w2.byte(1) == 0);
				REQUIRE(w2.byte(2) == 0);
				REQUIRE(w2.byte(3) == 1);
				REQUIRE(w2.byte(4) == 2);
				REQUIRE(w2.byte(5) == 3);
			}
		}
	}
}
