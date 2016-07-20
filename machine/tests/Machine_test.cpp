#include "catch.hpp"
#include "Helpers.h"
#include "../Machine.h"
#include "../Op_code.h"
#include "../Word.h"
#include <fstream>
#include <sstream>
#include <vector>

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
			Word w{machine.index_register(1)};
			Word w2{machine.index_register(
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
			Word w{machine.memory_cell(0)};
			Word w2{machine.memory_cell(Machine::MEM_SIZE - 1)};
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
		Word w{Sign::Minus, {1, 2, 3, 4, 5}};
		WHEN("Memory address 0 is loaded with the word")
		{
			machine.store_in_memory(0, w);
			THEN("The word is copied to memory cell")
			{
				Word mem{machine.memory_cell(0)};
				REQUIRE(mem.sign() == Sign::Minus);
				require_bytes_are(mem, {1, 2, 3, 4, 5});
			}
		}
	}
}

SCENARIO("Dumping memory", "[A]")
{
	GIVEN("A mix machine")
	{
		Machine machine{};
		const int last_mem_address{static_cast<int>(Machine::MEM_SIZE) - 1};
		Word first{Sign::Minus, {1, 2, 3, 4, 5}};
		Word last{Sign::Minus, {6, 7, 8, 9, 0}};
		machine.store_in_memory(0, first);
		machine.store_in_memory(last_mem_address, last);
		WHEN("Memory is dumped to a stream")
		{
			std::stringstream ss{};
			machine.dump_memory(&ss);
			THEN("All memory cells are dumped")
			{
				std::vector<Word> mem{};
				Word curr{};
				while (ss) {
					ss >> curr;
					if (!curr.is_valid()) break;
					mem.push_back(curr);
				}
				REQUIRE(mem.size() == Machine::MEM_SIZE);
				REQUIRE(mem[0] == first);
				REQUIRE(mem[last_mem_address] == last);
				for (int i = 1; i < Machine::MEM_SIZE - 1; ++i) {
					REQUIRE(mem[i].sign() == Sign::Plus);
					require_bytes_are(mem[i], {0, 0, 0, 0, 0});
				}
			}
		}
	}
}

SCENARIO("Loading a program")
{
	GIVEN("A mix machine")
	{
		Machine machine{};
		WHEN("A program is loaded into machine memory")
		{
			std::stringstream ss{};
			Word first{Sign::Plus, {1, 2, 3, 4, 5}};
			Word second{Sign::Minus, {6, 7, 8, 9, 0}};
			ss << first << second;
			machine.load_program(&ss);
			THEN("Entire program is stored in memory, in correct order")
			{
				Word w{machine.memory_cell(0)};
				REQUIRE(w.sign() == Sign::Plus);
				require_bytes_are(w, {1, 2, 3, 4, 5});
				w = machine.memory_cell(1);
				REQUIRE(w.sign() == Sign::Minus);
				require_bytes_are(w, {6, 7, 8, 9, 0});
			}
		}
		WHEN("A program file cannot be opened")
		{
			std::ifstream program{"file_that_doesnt_exist"};
			THEN("An invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(machine.load_program(&program),
								  std::invalid_argument);
			}
		}
		WHEN("An empty program is loaded")
		{
			std::stringstream ss{};
			THEN("An invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(machine.load_program(&ss),
								  std::invalid_argument);
			}
		}
		WHEN("An invalid program is loaded")
		{
			std::stringstream ss{};
			for (int i = 0; i < 10; ++i)
				ss << static_cast<Byte>(i);
			THEN("An exception is thrown")
			{
				REQUIRE_THROWS_AS(machine.load_program(&ss),
								  Invalid_basic_word);
			}
		}
	}
}

SCENARIO("Loading index register")
{
	GIVEN("A mix machine and a half word to load")
	{
		Machine machine{};
		Half_word hw{Sign::Minus, {1, 2}};
		WHEN("Index register 1 is loaded with [+ | 1 | 2]")
		{
			machine.load_index_register(1, hw);
			THEN("Index register 1 contains the loaded word")
			{
				const Half_word i1{machine.index_register(1)};
				REQUIRE(i1.sign() == Sign::Minus);
				require_bytes_are(i1, {1, 2});
			}
		}
		WHEN("Trying to load an index register that doesn't exist")
		{
			THEN("An invalid argument exception is thrown")
			{
				REQUIRE_THROWS_AS(machine.load_index_register(0, hw),
								  std::invalid_argument);

				int max{static_cast<int>(Machine::NUM_INDEX_REGISTERS)};
				REQUIRE_THROWS_AS(machine.load_index_register(max + 1, hw),
								  std::invalid_argument);
					
			}
		}
	}
}

SCENARIO("Reading the address from an instruction")
{
	GIVEN("A mix machine")
	{
		Machine machine{};
		WHEN("Reading address from an instruction")
		{
			Word inst{Sign::Plus, {0x1f, 0x10, 1, 0, 0}};
			Half_word i1{Sign::Plus, {0, 1}};
			machine.load_index_register(1, i1);
			int address{machine.read_address(inst)};
			THEN("The address is read, and offset by index reg spec")
			{
				REQUIRE(address == 2001);
			}
		}
	}
}

SCENARIO("Getting contents of memory with a field spec")
{
	GIVEN("A mix machine with some data in memory cell 0")
	{
		Machine machine{};
		Word some_data{Sign::Minus, {1, 2, 3, 4, 5}};
		machine.store_in_memory(0, some_data);
		WHEN("Getting field (0:5) of memory cell 0")
		{
			Field_spec fs{0, 5};
			Word contents{machine.memory_contents(0, fs)};
			THEN("The whole memory cell is returned")
			{
				REQUIRE(contents.sign() == Sign::Minus);
				require_bytes_are(contents, {1, 2, 3, 4, 5});
			}
		}
		WHEN("Getting field (0:2) of memory cell 0")
		{
			Field_spec fs{0, 2};
			Word contents{machine.memory_contents(0, fs)};
			THEN("The bytes [1, 2] are shifted to [4, 5]")
			{
				REQUIRE(contents.sign() == Sign::Minus);
				require_bytes_are(contents, {0, 0, 0, 1, 2});
			}
		}
	}
}

SCENARIO("Executing load instructions")
{
	GIVEN("A mix machine with some data in memory cell 0")
	{
		Machine machine{};
		Word some_data{Sign::Minus, {1, 2, 3, 4, 5}};
		machine.store_in_memory(0, some_data);
		WHEN("Executing a LDA instruction")
		{
			Word inst{Sign::Plus, {0, 0, 0, 5, Op_code::LDA}};
			machine.execute_load(inst);
			THEN("The accumulator is loaded")
			{
				Word accum{machine.accumulator()};
				REQUIRE(accum.sign() == Sign::Minus);
				require_bytes_are(accum, {1, 2, 3, 4, 5});
			}
		}
		WHEN("Executing a LDX instruction")
		{
			Word inst{Sign::Plus, {0, 0, 0, 3, Op_code::LDX}};
			machine.execute_load(inst);
			THEN("The extension register is loaded")
			{
				Word exten{machine.extension_register()};
				REQUIRE(exten.sign() == Sign::Minus);
				require_bytes_are(exten, {0, 0, 1, 2, 3});
			}
		}
		/*
		WHEN("Executing LD[1, 6] instructions")
		{
			Word inst{Sign::Plus, {0, 0, 0, 37, Op_code::LD1}};
			machine.execute_load(inst);
			THEN("Index register 1 is loaded")
			{
				Word index_one{machine.index_register(1)};
				REQUIRE(index_one.sign() == Sign::Plus);
				require_bytes_are(index_one, {3, 4});
			}
		}
		*/
	}
}

