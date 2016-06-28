#include "catch.hpp"
#include "../Machine.h"

using namespace mix;

SCENARIO("Accessing registers")
{
	GIVEN("A mix machine")
	{
		Machine machine{};
		WHEN("Accessing an index register that doesn't exist")
		{
			THEN("An invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(machine.index_register(0),
								  std::invalid_argument);
				REQUIRE_THROWS_AS(machine.index_register(
									Machine::NUM_INDEX_REGISTERS + 1),
								  std::invalid_argument);
			}
		}
		WHEN("Accessing a valid index register")
		{
			Machine::Word w{machine.index_register(1)};
			Machine::Word w2{machine.index_register(
								Machine::NUM_INDEX_REGISTERS - 1)};
			THEN("The contents of the register are returned")
			{
				REQUIRE(w.sign() == Sign::Plus);
				REQUIRE(w.byte(1) == 0);
				REQUIRE(w.byte(2) == 0);
				REQUIRE(w.byte(3) == 0);
				REQUIRE(w.byte(4) == 0);
				REQUIRE(w.byte(5) == 0);

				REQUIRE(w2.sign() == Sign::Plus);
				REQUIRE(w2.byte(1) == 0);
				REQUIRE(w2.byte(2) == 0);
				REQUIRE(w2.byte(3) == 0);
				REQUIRE(w2.byte(4) == 0);
				REQUIRE(w2.byte(5) == 0);
			}
		}
	}
}

SCENARIO("Accessing memory")
{
	GIVEN("A mix machine")
	{
		Machine machine{};
		WHEN("Accessing memory which is out of bounds")
		{
			THEN("An invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(machine.memory_cell(-1),
								  std::invalid_argument);
				REQUIRE_THROWS_AS(machine.memory_cell(Machine::MEM_SIZE),
								  std::invalid_argument);
			}
		}
		WHEN("Accessing valid memory cells")
		{
			Machine::Word w{machine.memory_cell(0)};
			Machine::Word w2{machine.memory_cell(Machine::MEM_SIZE - 1)};
			THEN("The contents of the memory cell are returned")
			{
				REQUIRE(w.sign() == Sign::Plus);
				REQUIRE(w.byte(1) == 0);
				REQUIRE(w.byte(2) == 0);
				REQUIRE(w.byte(3) == 0);
				REQUIRE(w.byte(4) == 0);
				REQUIRE(w.byte(5) == 0);

				REQUIRE(w2.sign() == Sign::Plus);
				REQUIRE(w2.byte(1) == 0);
				REQUIRE(w2.byte(2) == 0);
				REQUIRE(w2.byte(3) == 0);
				REQUIRE(w2.byte(4) == 0);
				REQUIRE(w2.byte(5) == 0);
			}
		}
	}
}

SCENARIO("Program counter")
{
	GIVEN("A mix machine")
	{
		Machine machine{};
		WHEN("The first instruction is executed")
		{
			machine.execute_next_instruction();
			THEN("The program counter increments to next instruction")
			{
				REQUIRE(machine.program_counter() == 1);
			}
		}
	}
}
