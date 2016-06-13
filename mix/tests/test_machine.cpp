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
		Word instruction{1, 0};
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
		Word instruction{0x3f, 0x3f};
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
		Word instruction{0xff, 0xff};
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
		Half_word hw{0, 1};
		Word instruction{0, 1, 1};
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
		Word instruction{0, 0, Machine::num_index_registers + 1};
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
		Word instruction{0, 0, 0, 5};
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

SCENARIO("Loading registers")
{
	Machine mix{};
	GIVEN("A instruction to load the accumulator with default field")
	{
		mix.memory(0) = Word{Sign::Minus, {1, 2, 3, 4, 5}};
		Word instruction{0, 0, 0, to_byte(Field{}), Op_code::LDA};
		WHEN("Instruction is executed")
		{
			mix.execute_instruction(instruction);
			THEN("Contents of memory 0 are loaded into accumulator")
			{
				const Word& acc{mix.accumulator()};
				REQUIRE(acc.byte(1) == 1);
				REQUIRE(acc.byte(2) == 2);
				REQUIRE(acc.byte(3) == 3);
				REQUIRE(acc.byte(4) == 4);
				REQUIRE(acc.byte(5) == 5);
			}
		}
	}

	GIVEN("An instruction to load accumulator with field of (3:4)")
	{
		mix.memory(0) = Word{1, 2, 3, 4, 5};
		Word instruction{0, 0, 0, to_byte(Field{3, 4}), Op_code::LDA};
		WHEN("Instruction is executed")
		{
			mix.execute_instruction(instruction);
			THEN("Contents of memory 0 are loaded into accumulator")
			{
				const Word& acc{mix.accumulator()};
				REQUIRE(acc.byte(1) == 0);
				REQUIRE(acc.byte(2) == 0);
				REQUIRE(acc.byte(3) == 0);
				REQUIRE(acc.byte(4) == 3);
				REQUIRE(acc.byte(5) == 4);
			}
		}
	}

	GIVEN("An instruction to load index register with default field")
	{
		mix.memory(0) = Word{1, 2, 3, 4, 5};
		Word instruction{0, 0, 0, to_byte(Field{}), Op_code::LD1};
		WHEN("Instruction is executed")
		{
			mix.execute_instruction(instruction);
			THEN("Contents of memory 0 are loaded into index register")
			{
				const Half_word& i1{mix.index_register(1)};
				REQUIRE(i1.byte(1) == 4);
				REQUIRE(i1.byte(2) == 5);
			}
		}
	}

	GIVEN("An instruction to load index register with field of (1:3)")
	{
		mix.memory(0) = Word{1, 2, 3, 4, 5};
		Word instruction{0, 0, 0, to_byte(Field{1, 3}), Op_code::LD3};
		WHEN("Instruction is executed")
		{
			mix.execute_instruction(instruction);
			THEN("Contents of memory 0 are loaded into index reg 3")
			{
				const Half_word& i3{mix.index_register(3)};
				REQUIRE(i3.byte(1) == 2);
				REQUIRE(i3.byte(2) == 3);
			}
		}
	}

	GIVEN("A load negative instuction, with default field")
	{
		mix.memory(0) = Word{1, 2, 3, 4, 5};
		Word instruction{0, 0, 0, to_byte(Field{}), Op_code::LDAN};
		WHEN("Instruction is executed")
		{
			mix.execute_instruction(instruction);
			THEN("Contents of memory are loaded, with sign negated")
			{
				const Word& acc{mix.accumulator()};
				REQUIRE(acc.sign() == Sign::Minus);
				REQUIRE(acc.byte(1) == 1);
				REQUIRE(acc.byte(2) == 2);
				REQUIRE(acc.byte(3) == 3);
				REQUIRE(acc.byte(4) == 4);
				REQUIRE(acc.byte(5) == 5);
			}
		}
	}

	GIVEN("A load negative instruction, with field of (0:2)")
	{
		mix.memory(0) = Word{Sign::Minus, {1, 2, 3, 4, 5}};
		Word instruction{0, 0, 0, to_byte(Field{0, 2}), Op_code::LDXN};
		WHEN("Instruction is executed")
		{
			mix.execute_instruction(instruction);
			THEN("Contents of memory are loaded, with sign negated")
			{
				const Word& ex{mix.extension()};
				REQUIRE(ex.sign() == Sign::Plus);
				REQUIRE(ex.byte(1) == 0);
				REQUIRE(ex.byte(2) == 0);
				REQUIRE(ex.byte(3) == 0);
				REQUIRE(ex.byte(4) == 1);
				REQUIRE(ex.byte(5) == 2);
			}
		}
	}
}
