#include "catch.hpp"
#include "../Half_word.h"
#include "../Word.h"

using namespace machine;

SCENARIO("Invalid byte indexing")
{
  GIVEN("A Half_word")
  {
    Half_word hw{};
    WHEN("Byte index is less than 0")
    {
      int index{-1};
      THEN("Invalid argument is thrown")
      {
        REQUIRE_THROWS_AS(hw[index], std::invalid_argument);
      }
    }
    WHEN("Byte index is greater than num_bytes")
    {
      int index{Half_word::num_bytes + 1};
      THEN("Invalid argument is thrown")
      {
        REQUIRE_THROWS_AS(hw[index], std::invalid_argument);
      }
    }
  }

  GIVEN("A Word")
  {
    Word w{};
    WHEN("Byte index is less than 0")
    {
      int index{-1};
      THEN("Invalid argument is thrown")
      {
        REQUIRE_THROWS_AS(w[index], std::invalid_argument);
      }
    }
    WHEN("Byte index is greater than num_bytes")
    {
      int index{Word::num_bytes + 1};
      THEN("Invalid argument is thrown")
      {
        REQUIRE_THROWS_AS(w[index], std::invalid_argument);
      }
    }
  }
}


SCENARIO("Setting the sign to an illegal value")
{
  GIVEN("A Half_word")
  {
    Half_word hw{};
    WHEN("Setting sign to invalid value")
    {
      THEN("Invalid argument is thrown")
      {
        REQUIRE_THROWS_AS(hw.sign(static_cast<Sign>(-1)),
                          std::invalid_argument);
      }
    }
  }

  GIVEN("A Word")
  {
    Word w{};
    WHEN("Setting sign to invalid value")
    {
      THEN("Invalid argument is thrown")
      {
        REQUIRE_THROWS_AS(w.sign(static_cast<Sign>(-1)),
                          std::invalid_argument);
      }
    }
  }
}


SCENARIO("Accessing parts of a Word")
{
  GIVEN("A Word set to +0")
  {
    Word w{};
    WHEN("Accessing the address part")
    {
      unsigned int address{w.address()};
      THEN("The address is 0")
      {
        REQUIRE(address == 0);
      }
    }
  }

  GIVEN("A Word set to [+|1|0|0|0|0]")
  {
    Word w{};
    w[0] = 1;
    WHEN("Accessing the address part")
    {
      unsigned int address{w.address()};
      THEN("The address is 64")
      {
        REQUIRE(address == 64);
      }
    }
  }

  GIVEN("A word set to [+|3f|3f|0|0|0]")
  {
    Word w{};
    w[0] = 0x3f;
    w[1] = 0x3f;
    WHEN("Accessing the address part")
    {
      unsigned int address{w.address()};
      THEN("The address is 4095")
      {
        REQUIRE(address == 4095);
      }
    }
  }

  GIVEN("A word set to [+|ff|ff|0|0|0]")
  {
    Word w{};
    w[0] = 0xff;
    w[1] = 0xff;
    WHEN("Accessing the address part")
    {
      unsigned int address{w.address()};
      THEN("Address is max of 4095, due to truncating to 6-bit bytes")
      {
        REQUIRE(address == 4095);
      }
    }
  }
}
