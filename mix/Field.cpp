#include "Field.h"
#include "Word.h"

namespace MIX
{
	// Field specification's left part scaling factor.
	const unsigned int left_scale{8};
	// Default left value.
	const unsigned int default_left{0};
	// Default right value.
	const unsigned int default_right{Word::num_bytes};
	// Maximum valid value.
	const unsigned int max{Word::num_bytes};
	// Minimum valid value.
	const unsigned int min{0};

	/*
	* Return a field representing the address part of an instruction.
	*/
	const Field Field::address()
	{
		return Field{0, Instruction::address_lsb};
	}

	/*
	* Construct the default field specification of (0:5).
	*/
	Field::Field() : left{default_left}, right{default_right}
	{
	}

	/*
	* Construct a field with the given left and right values.
	*/
	Field::Field(unsigned int l, unsigned int r) : left{l}, right{r}
	{
		validate();
	}

	/*
	* Ensure the field is valid.
	*/
	void Field::validate()
	{
		if(left < min || right < left)
			throw std::invalid_state{"Left is invalid"};
		if(right < min || max < right)
			throw std::invalid_state{"Right is invalid"};
	}

	/*
	* Copy the given field.
	*/
	Field::Field(const Field& f) : left{f.left}, right{f.right}
	{
	}

	/*
	* Convert the given number into a field specification.
	*/
	Field to_field(const unsigned int ui)
	{
		unsigned int left{ui / left_scale};
		unsigned int right{ui % left_scale};
		return Field{left, right};
	}

	/*
	* Convert the given field specification into an unsigned int.
	*/
	Byte to_byte(const Field& fs)
	{
		return static_cast<Byte>(fs.left * left_scale + fs.right);
	}
}
