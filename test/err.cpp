#include <iostream>
int main ()
{
    try
{
  throw "a";
  throw "b";
  throw "c";
  throw "d";
  throw "e";
}
catch (const char *e) {
  std::cout << e;
}
}