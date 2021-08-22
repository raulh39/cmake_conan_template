#include "impl1.h"

#include <catch2/catch.hpp>

#include <iostream>

TEST_CASE("TBD_test_case_name")
{
  Impl1 hello;
  REQUIRE(hello.Greetings() == "Hello world!");
}
