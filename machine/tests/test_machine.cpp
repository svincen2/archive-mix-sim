#include "catch.hpp"
#include "../Machine.h"
#include "../Word.h"

using namespace machine;

SCENARIO("Reading address specifications")
{
  Machine mix{};
  GIVEN("An Instruction of [+|1|0|0|0|0]")
  {
    Word instruction{};
    instruction[Instruction::address_msb] = 1;
    instruction[Instruction::address_lsb] = 0;
    WHEN("The address is read by the machine")
    {
      const int address{mix.read_address(instruction)};
      THEN("Address read is 0x40")
      {
        REQUIRE(address == 0x40);
      }
    }
  }

  GIVEN("An Instruction of [+|3f|3f|0|0|0]")
  {
    Word instruction{};
    instruction[Instruction::address_msb] = 0x3f;
    instruction[Instruction::address_lsb] = 0x3f;
    WHEN("The address is read by the machine")
    {
      const int address{mix.read_address(instruction)};
      THEN("Address read is 0xfff")
      {
        REQUIRE(address == 0xfff);
      }
    }
  }

  GIVEN("And Instruction of [+|ff|ff|0|0|0]")
  {
    Word instruction{};
    instruction[Instruction::address_msb] = 0xff;
    instruction[Instruction::address_lsb] = 0xff;
    WHEN("The address is read by the machine")
    {
      const int address{mix.read_address(instruction)};
      THEN("Address read is 0xfff")
      {
        REQUIRE(address == 0xfff);
      }
    }
  }
}

SCENARIO("Reading the field specification")
{
  Machine mix{};
  GIVEN("An Instruction of [+|0|0|0|5|0]")
  {
    Word instruction{};
    instruction[Instruction::modification] = 5;
    WHEN("Machine reads field specification")
    {
      const Instruction::Field f{mix.read_field(instruction)};
      THEN("Field specification is (0:5)")
      {
        REQUIRE(f.left == 0);
        REQUIRE(f.right == 5);
      }
    }
  }
}
