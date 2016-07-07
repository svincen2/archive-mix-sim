#include "catch.hpp"
#include "Helpers.h"
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
				require_bytes_are(w, {0, 0, 0, 0, 0});

				REQUIRE(w2.sign() == Sign::Plus);
				require_bytes_are(w2, {0, 0, 0, 0, 0});
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
				require_bytes_are(w, {0, 0, 0, 0, 0});

				REQUIRE(w2.sign() == Sign::Plus);
				require_bytes_are(w2, {0, 0, 0, 0, 0});
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

SCENARIO("Loading memory")
{
	GIVEN("A mix machine and a word to load")
	{
		Machine machine{};
		Machine::Word w{Sign::Minus, {1, 2, 3, 4, 5}};
		WHEN("Memory address 0 is loaded with the word")
		{
			machine.store_in_memory(0, w);
			THEN("The word is copied to memory cell")
			{
				Machine::Word mem{machine.memory_cell(0)};
				REQUIRE(mem.sign() == Sign::Minus);
				require_bytes_are(mem, {1, 2, 3, 4, 5});
			}
		}
	}
}

SCENARIO("Dumping memory")
{
	GIVEN("A mix machine")
	{
		Machine machine{};
		const int last_mem_address{static_cast<int>(Machine::MEM_SIZE) - 1};
		Machine::Word first{Sign::Minus, {1, 2, 3, 4, 5}};
		Machine::Word last{Sign::Minus, {6, 7, 8, 9, 0}};
		machine.store_in_memory(0, first);
		machine.store_in_memory(last_mem_address, last);
		WHEN("Memory is dumped to a stream")
		{
			std::stringstream ss{};
			machine.dump_memory(&ss);
			THEN("All memory cells are dumped")
			{
				std::vector<Machine::Word> mem{};
				Machine::Word curr{};
				while (ss) {
					ss >> curr;
					if (!ss) break;
					mem.push_back(curr);
				}
				REQUIRE(mem.size() == Machine::MEM_SIZE);
				REQUIRE(mem[0] == first);
				REQUIRE(mem[last_mem_address] == last);
			}
		}
	}
}
