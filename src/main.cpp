#include "impl1.h"

#include <fmt/printf.h>

#include <iostream>

int main()
{
  Impl1 hello;
  fmt::print("The lib say \"{}\"\n", hello.Greetings());
}
