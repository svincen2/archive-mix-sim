#include "catch.hpp"
#include "../Machine.h"
#include "../Word.h"
#include "../Field.h"

using namespace MIX;

SCENARIO("Reading address specifications")
{
	Machine mix{};
	GIVEN("An Instruction of [+|1|0|0|0|0]")
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

	GIVEN("An Instruction of [+|3f|3f|0|0|0]")
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

	GIVEN("And Instruction of [+|ff|ff|0|0|0]")
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

SCENARIO("Reading the index specification")
{
	Machine mix{};
	GIVEN("An instruction with an index that is too big")
	{
		Word instruction{Sign::Plus, 0, 0, Machine::num_index_registers + 1};
		WHEN("Machine reads the index specification")
		{
			THEN("Invalid argument is thrown")
			{
				REQUIRE_THROWS_AS(mix.read_index(instruction),
								  std::invalid_argument);
			}
		}
	}
}

SCENARIO("Reading the field specification")
{
	Machine mix{};
	GIVEN("An Instruction of [+|0|0|0|5|0]")
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
