#ifndef MIX_MACHINE_MACHINE_H
#define MIX_MACHINE_MACHINE_H

#include "Basic_word.h"
#include "Sign.h"
#include <iostream>
#include <string>
#include <vector>

namespace mix
{
	// Mix machine.
	class Machine
	{
	public:
		// A word has 5 bytes and a sign.
		using Word = Basic_word<5>;

		// A half-word has 2 bytes and a sign.
		using Half_word = Basic_word<2>;

		// A bit is either on or off.
		enum class Bit : Byte { On, Off };

		// Comparison values
		enum class Comparison_value : Byte { Equal, Greater, Less };

		// Constants.
		static const unsigned int MEM_SIZE;
		static const unsigned int NUM_INDEX_REGISTERS;

		// Constructors and destructor.
		Machine();
		Machine(const Machine&) = delete;
		Machine(Machine&&) = delete;


		/* Functions. */

		// Running the machine.
		void load_program(std::istream&);
		void run(std::vector<std::string>&);
		void execute_next_instruction();
		void dump_memory(std::ostream*) const;

		// Accessors.
		int program_counter() const;
		Bit overflow_bit() const;
		Comparison_value comparison_indicator() const;
		Half_word jump_register() const;
		Word accumulator() const;
		Word extension_register() const;
		Half_word index_register(int) const;
		Word memory_cell(int) const;

		// Mutators.
		void store_in_memory(int, Word&);


	private:
		int pc;
		Bit overflow;
		Comparison_value compare;
		Half_word jump;
		Word accum;
		Word exten;

		std::vector<Half_word> index;
		std::vector<Word> memory;

		void check_arguments(const std::vector<std::string>&) const;
	};
}
#endif

