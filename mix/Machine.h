#ifndef MIX_MACHINE_H
#define MIX_MACHINE_H

#include "Bit.h"
#include "Half_word.h"
#include "Word.h"
#include "Field.h"
#include "Comparison.h"
#include "Instruction.h"
#include <vector>

namespace MIX
{
	class Machine
	{
	public:
		// Constants.
		static const unsigned int num_index_registers{6};
		static const unsigned int memory_size{4000};

		// Constructors.
		Machine();
		Machine(const Machine&) = delete;
		Machine(Machine&&) = delete;

		// Accessors.
		const Word& accumulator() const { return _accumulator; }
		const Word& extension() const { return _extension; }
		const Half_word& jump_register() const { return _jump; }
		const Half_word& index_register(int) const;
		const Word& memory(int) const;

		// Mutators.
		Word& accumulator() { return _accumulator; }
		Word& extension() { return _extension; }
		Half_word& jump_register() { return _jump; }
		Half_word& index_register(int);
		Word& memory(int);

		// Methods to read parts of instructions.
		const int read_address(const Word&) const;
		const unsigned int read_index(const Word&) const;
		const unsigned int read_modification(const Word&) const;
		const Field read_field(const Word&) const;
		const unsigned int read_op_code(const Word&) const;

		// Methods to execute instructions.
		void execute_instruction(const Word&);
		void load(unsigned int, const Word&);
		void load_neg(unsigned int, const Word&);
		const Word right_shift(const Word&, const Field&);

	private:
		Bit _overflow;								// Overflow bit (on/off).
		Comparison _comparison_indicator;			// Comparison flag.
		Word _accumulator;							// Accumulator register (A).
		Word _extension;							// Extension register (X).
		Half_word _jump;							// Jump register (J).
		std::vector<Half_word> _index_registers;	// Index registers.
		std::vector<Word> _memory;					// Machine memory.
	};
}
#endif
