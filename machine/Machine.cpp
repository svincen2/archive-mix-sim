#include "Machine.h"

#include <iostream>

namespace MIX
{
    /*
    * Construct a MIX machine.
    * All registers are cleared to +0.
    * All memory words are also cleared to +0.
    */
    Machine::Machine()
        : _overflow{Bit::On},
          _comparison_indicator{Comparison::Equal},
          _accumulator{},
          _extension{},
          _jump{},
          _index_registers(num_index_registers),
          _memory(memory_size),
          _operation_table{}
    {
        setup_operation_table();
    }

    /*
    * Adds pointers to all machine operations to operation table.
    */
    void Machine::setup_operation_table()
    {
        _operation_table.push_back(&Machine::lda);
    }

    /*
    * Execute the given instruction word.
    */
    void Machine::execute_instruction(const Word& instruction)
    {
        operation op = _operation_table[read_op_code(instruction)];
        (this->*op)(instruction);
    }

    /*
    *
    */
    const Word Machine::contents(unsigned int address,
                                 const Instruction::Field& field) const
    {
        const Word& mem = memory(address);
        return get_bytes(mem, field);
    }

    /*
    * Get the bytes in the given field from the given word, right shifted.
    */
    const Word Machine::get_bytes(const Word& word,
                                  const Instruction::Field& field) const
    {
        Word destination_word{};
        int destination_byte = Word::num_bytes;
        for(int i = field.right; i >= field.left && i > 0; --i)
        {
            destination_word.byte(destination_byte--) = word.byte(i);
        }
        if(field.left == 0)
            destination_word.sign(word.sign());
        return destination_word;
    }

    /*
    * Return the index register at the given index.
    * Index is 1 based because register names are [I1, I6].
    * Register names are defined by Knuth, Volume 1, Chapter 3.1
    */
    const Half_word& Machine::index_register(int index) const
    {
        if(index < 1 || num_index_registers < index)
            throw std::invalid_argument{"Index register index out of bounds"};
        return _index_registers[index - 1];
    }

    /*
    * Return the index register at the given index.
    * Allows the index register to be modified.
    * Index is 1 based because register names are [I1, I6].
    * Register names are defined by Knuth, Volum 1, Chapter 3.1
    */
    Half_word& Machine::index_register(int index)
    {
        if(index < 1 || num_index_registers < index)
            throw std::invalid_argument{"Index register invalid"};
        return _index_registers[index - 1];
    }


    /*
    * Return the memory word at the given index.
    */
    const Word& Machine::memory(int address) const
    {
        if(address < 0 || memory_size <= address)
            throw std::invalid_argument{"Memory index out of bounds"};
        return _memory[address];
    }

    /*
    * Return a reference to the memory word at the given address.
    * Allows the reference to be modified.
    */
    Word& Machine::memory(int address)
    {
        if(address < 0 || memory_size <= address)
            throw std::invalid_argument{"Memory address out of bounds"};
        return _memory[address];
    }

    /*
    * Return the address specification of the given instruction word.
    * The address is offset by the contents of the index register
    * specified by the instruction's index specification on every instruction.
    * If the index specification is 0, there is no offset.
    */
    const int Machine::read_address(const Word& instruction) const
    {
        int a{address(instruction)};
        const unsigned int i{read_index(instruction)};
        if(i > 0)
            a += address(index_register(i));
        return a;
    }

    /*
    * Return the index specification of the given instruction word.
    */
    const unsigned int Machine::read_index(const Word& instruction) const
    {
        const unsigned int i{instruction.byte(Instruction::index)};
        if(i < 0 || num_index_registers < i)
            throw std::invalid_argument{"Index specification invalid"};
        return i;
    }

    /*
    * Return the field specification of the given instruction word.
    */
    const Instruction::Field Machine::read_field(const Word& instruction) const
    {
        return Instruction::to_field_spec(
            instruction.byte(Instruction::modification)
        );
    }

    /*
    * Read the operation code part of the given instruction word.
    */
    const unsigned int Machine::read_op_code(const Word& instruction) const
    {
        return instruction.byte(Instruction::op_code);
    }

    /*
    * Load the accumulator according to the given instruction.
    */
    void Machine::lda(const Word& instruction)
    {
        std::cout << "this: " << this << '\n';
    }
}

