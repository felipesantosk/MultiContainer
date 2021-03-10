

#include "MultiContainer.h"

#include <tuple>

#include <catch2/catch.hpp>

struct Test1
{
   int32_t b;
   int32_t c;
};

bool operator<( const Test1& value1, const Test1& value2)
{
   return std::tie( value1.b, value1.c ) < std::tie( value2.b, value2.c );
}

TEST_CASE("MultiContainer - First Test")
{
   fsk::MultiContainer multiContainer;

   multiContainer.Insert<int32_t>(10);

   CHECK(multiContainer.Find(10).has_value());

   multiContainer.Insert<Test1>({10, 11});

   multiContainer.Find<Test1>({10, 12});
}