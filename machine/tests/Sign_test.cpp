#include "catch.hpp"
#include "../Byte.h"
#include "../Sign.h"

using namespace mix;

SCENARIO("Reading and writing a sign")
{
	GIVEN("A sign value")
	{
		Sign s{Sign::Plus};
		WHEN("Writing a sign to output stream")
		{
			std::stringstream ss{};
			ss << s;
			THEN("The output stream contains the sign")
			{
				REQUIRE('+' == ss.str()[0]);
			}
		}
		WHEN("Reading a sign from an input stream")
		{
			std::stringstream ss{};
			ss << Sign::Plus;
			ss >> s;
			THEN("The sign is read correctly")
			{
				REQUIRE(s == Sign::Plus);
			}
		}
		WHEN("Reading an invalid sign")
		{
			std::stringstream ss{};
			ss << static_cast<Byte>(6);
			ss >> s;
			THEN("Sign is marked as invalid")
			{
				REQUIRE(s == Sign::Invalid);
			}
		}
	}
}

