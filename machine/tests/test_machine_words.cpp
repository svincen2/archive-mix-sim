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

