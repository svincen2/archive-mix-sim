#include "catch.hpp"
#include "../Instruction.h"
#include "../Word.h"

using namespace mix;

SCENARIO("Getting parts of an instruction")
{
	GIVEN("An instruction")
	{
		Word inst{Sign::Plus, {1, 2, 3, 4, 5}};
		WHEN("Getting the address")
		{
			int address{get_address(inst)};
			THEN("The address is correct")
			{
				REQUIRE(address == 66);
			}
		}
		WHEN("Getting the index specification")
		{
			int index_spec{get_index_spec(inst)};
			THEN("The index spec is correct")
			{
				REQUIRE(index_spec == 3);
			}
		}
		WHEN("Getting the field spec")
		{
			Field_spec fs{get_field_spec(inst)};
			THEN("The field spec is correct")
			{
				REQUIRE(fs.left == 0);
				REQUIRE(fs.right == 4);
			}
		}
		WHEN("Getting the op code")
		{
			Op_code op{get_op_code(inst)};
			THEN("The op code is correct")
			{
				REQUIRE(op == 5);
			}
		}
	}
}
