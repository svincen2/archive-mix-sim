#include "Sign.h"

namespace mix
{
	/*
	* Write the given sign to the given output stream.
	* Parameters:
	*	os - Output stream to write to.
	*	sign - Sign to write.
	*/
	std::ostream& operator<<(std::ostream& os, const Sign& sign)
	{
		os << static_cast<Byte>(sign);
		return os;
	}

	/*
	* Read a sign from the given input stream into the given sign.
	* Parameters:
	*	is - Input stream to read from.
	*	sign - Sign to read into.
	*/
	std::istream& operator>>(std::istream& is, Sign& sign)
	{
		Byte temp;
		is >> temp;
		sign = static_cast<Sign>(temp);
		if (!valid(sign))
			throw Invalid_sign{};
		return is;
	}

	/*
	* Returns whether or not the sign is valid.
	*/
	bool valid(const Sign& sign)
	{
		return sign == Sign::Plus || sign == Sign::Minus;
	}
}

