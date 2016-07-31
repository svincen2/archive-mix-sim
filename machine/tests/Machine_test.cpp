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
									Machine::num_index_registers + 1),
								  std::invalid_argument);
			}
		}
		WHEN("Accessing a valid index register")
		{
			machine.index_register(1, {Sign::Minus, {1, 2}});
			machine.index_register(2, {Sign::Minus, {3, 4}});
			THEN("The contents of the register are returned")
			{
				Half_word ir_one{machine.index_register(1)};
				REQUIRE(ir_one.sign() == Sign::Minus);
				require_bytes_are(ir_one, {1, 2});

				Half_word ir_two{machine.index_register(2)};
				REQUIRE(ir_two.sign() == Sign::Minus);
				require_bytes_are(ir_two, {3, 4});
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
				REQUIRE_THROWS_AS(machine.memory_cell(Machine::mem_size),
								  std::invalid_argument);
			}
		}
		WHEN("Accessing valid memory cells")
		{
			Word w{machine.memory_cell(0)};
			Word w2{machine.memory_cell(Machine::mem_size - 1)};
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
		Word inst{Sign::Plus, {0, 0, 0, 0, Op_code::LDA}};
		machine.memory_cell(0, inst);
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
			machine.memory_cell(0, w);
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
		const int last_mem_address{static_cast<int>(Machine::mem_size) - 1};
		Word first{Sign::Minus, {1, 2, 3, 4, 5}};
		Word last{Sign::Minus, {6, 7, 8, 9, 0}};
		machine.memory_cell(0, first);
		machine.memory_cell(last_mem_address, last);
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
				REQUIRE(mem.size() == Machine::mem_size);
				REQUIRE(mem[0] == first);
				REQUIRE(mem[last_mem_address] == last);
				for (int i = 1; i < Machine::mem_size - 1; ++i) {
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
			machine.index_register(1, hw);
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
				REQUIRE_THROWS_AS(machine.index_register(0, hw),
								  std::invalid_argument);

				int max{static_cast<int>(Machine::num_index_registers)};
				REQUIRE_THROWS_AS(machine.index_register(max + 1, hw),
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
			machine.index_register(1, i1);
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
		machine.memory_cell(0, some_data);
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
	GIVEN("A mix machine with some data in memory cell 1")
	{
		Machine machine{};
		Word some_data{Sign::Minus, {1, 2, 3, 4, 5}};
		machine.memory_cell(1, some_data);
		WHEN("Executing a LDA instruction")
		{
			Word inst{Sign::Plus, {0, 1, 0, 5, Op_code::LDA}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("The accumulator is loaded")
			{
				Word accum{machine.accumulator()};
				REQUIRE(accum.sign() == Sign::Minus);
				require_bytes_are(accum, {1, 2, 3, 4, 5});
			}
		}
		WHEN("Executing a LDX instruction")
		{
			Word inst{Sign::Plus, {0, 1, 0, 3, Op_code::LDX}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("The extension register is loaded")
			{
				Word exten{machine.extension_register()};
				REQUIRE(exten.sign() == Sign::Minus);
				require_bytes_are(exten, {0, 0, 1, 2, 3});
			}
		}
		WHEN("Executing LD1 instructions")
		{
			Word inst{Sign::Plus, {0, 1, 0, 28, Op_code::LD1}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("Index register 1 is loaded")
			{
				Half_word index_one{machine.index_register(1)};
				REQUIRE(index_one.sign() == Sign::Plus);
				require_bytes_are(index_one, {3, 4});
			}
		}
		WHEN("Executing LD6 instructions")
		{
			Word inst{Sign::Plus, {0, 1, 0, 5, Op_code::LD6}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("Index register 6 is loaded")
			{
				Half_word index_six{machine.index_register(6)};
				REQUIRE(index_six.sign() == Sign::Minus);
				require_bytes_are(index_six, {4, 5});
			}
		}
	}
}

SCENARIO("Executing load negative operations")
{
	GIVEN("A mix machine with some data in memory cell 1")
	{
		Machine machine{};
		machine.memory_cell(1, {Sign::Plus, {1, 2, 3, 4, 5}});
		WHEN("Executing a LDAN instruction with field that contains sign")
		{
			const Word inst{Sign::Plus, {0, 1, 0, 5, Op_code::LDAN}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("Accumulator is loaded, and sign is negated")
			{
				const Word accum{machine.accumulator()};
				REQUIRE(accum.sign() == Sign::Minus);
				require_bytes_are(accum, {1, 2, 3, 4, 5});
			}
		}
		WHEN("Executing a LDXN instruction with field with no sign")
		{
			const Word inst{Sign::Plus, {0, 1, 0, 13, Op_code::LDXN}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("Extension register is loaded, and sign is not negated")
			{
				const Word exten{machine.extension_register()};
				REQUIRE(exten.sign() == Sign::Plus);
				require_bytes_are(exten, {1, 2, 3, 4, 5});
			}
		}
	}
}

SCENARIO("Executing store instructions")
{
	GIVEN("A mix machine")
	{
		Machine machine{};
		WHEN("Executing a STA instruction")
		{
			machine.accumulator({Sign::Minus, {1, 2, 3, 4, 5}});
			const Word inst{Sign::Plus, {0, 1, 0, 5, Op_code::STA}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("The contents of the accumulator are stored into memory")
			{
				const Word mem{machine.memory_cell(1)};
				REQUIRE(mem.sign() == Sign::Minus);
				require_bytes_are(mem, {1, 2, 3, 4, 5});
			}
		}
		WHEN("Executing a ST1 instruction")
		{
			machine.memory_cell(1, {Sign::Plus, {1, 2, 3, 4, 5}});
			machine.index_register(1, {Sign::Minus, {1, 2}});
			const Word inst{Sign::Plus, {0, 1, 0, 3, Op_code::ST1}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("The contents of index register 1 are stored in memory")
			{
				const Word mem{machine.memory_cell(1)};
				REQUIRE(mem.sign() == Sign::Minus);
				require_bytes_are(mem, {0, 1, 2, 4, 5});
			}
		}
		WHEN("Executing a STJ instruction")
		{
			machine.memory_cell(1, {Sign::Plus, {1, 2, 3, 4, 5}});
			machine.jump_register({Sign::Plus, {6, 7}});
			const Word inst{Sign::Plus, {0, 1, 0, 2, Op_code::STJ}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("The contents of the jump register are stored in memory")
			{
				const Word mem{machine.memory_cell(1)};
				REQUIRE(mem.sign() == Sign::Plus);
				require_bytes_are(mem, {6, 7, 3, 4, 5});
			}
		}
		WHEN("Executing a STX instruction")
		{
			machine.memory_cell(1, {Sign::Minus, {1, 2, 3, 4, 5}});
			machine.extension_register({Sign::Plus, {6, 7, 8, 9, 0}});
			const Word inst{Sign::Plus, {0, 1, 0, 27, Op_code::STX}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("The contents of the extension register are stored in memory")
			{
				const Word mem{machine.memory_cell(1)};
				REQUIRE(mem.sign() == Sign::Minus);
				require_bytes_are(mem, {1, 2, 0, 4, 5});
			}
		}
		WHEN("Executing a STZ instruction")
		{
			machine.memory_cell(1, {Sign::Minus, {1, 2, 3, 4, 5}});
			const Word inst{Sign::Plus, {0, 1, 0, 4, Op_code::STZ}};
			machine.memory_cell(0, inst);
			machine.execute_next_instruction();
			THEN("The specified field of memory are cleared to 0")
			{
				const Word mem{machine.memory_cell(1)};
				REQUIRE(mem.sign() == Sign::Plus);
				require_bytes_are(mem, {0, 0, 0, 0, 5});
			}
		}
	}
}

SCENARIO("Addition")
{
	GIVEN("A mix machine with some data in memory cell 1 and accumulator")
	{
		Machine machine{};
		machine.memory_cell(1, {Sign::Plus, {1, 2, 3, 4, 5}});
		machine.accumulator({Sign::Plus, {0, 0, 0, 1, 0}});
		WHEN("Adding field (0:5) of memory cell 1")
		{
			const Word inst{Sign::Plus, {0, 1, 0, 5, Op_code::ADD}};
			const int accum_before{machine.accumulator().to_int()};
			machine.execute_next_instruction();
			THEN("The accumulator contains result of addition")
			{
				const Word accum{machine.accumulator()};
				const int mem{machine.memory_cell(1).to_int()};
				REQUIRE(accum.sign() == Sign::Plus);
				REQUIRE(accum.to_int() == (accum_before + mem));
			}
		}
	}
}
