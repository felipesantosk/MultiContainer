

#include "MultiContainer.h"

#include <tuple>

#include <catch2/catch.hpp>

struct Test
{
   int32_t attr1;
   int32_t attr2;
};

bool operator<(const Test &value1, const Test &value2)
{
   return std::tie(value1.attr1, value1.attr2) < std::tie(value2.attr1, value2.attr2);
}

bool operator==(const Test &value1, const Test &value2)
{
   return std::tie(value1.attr1, value1.attr2) == std::tie(value2.attr1, value2.attr2);
}

SCENARIO("MultiContainer can be inserted and searched", "[MultiContainer]")
{
   fsk::MultiContainer multiContainer;

   GIVEN("A MultiContainer with multiple types")
   {
      multiContainer.Insert<int32_t>(10);
      multiContainer.Insert<int32_t>(14);
      multiContainer.Insert<int16_t>(10);
      multiContainer.Insert<Test>({10, 11});
      multiContainer.Insert<Test>({10, 13});

      WHEN("find by not existing type")
      {
         const auto value = multiContainer.Find<int8_t>(10);

         THEN("return a empty optional type")
         {
            CHECK_FALSE(value.has_value());
         }
      }

      WHEN("search by existing type")
      {
         WHEN("its a primitive type ")
         {
            WHEN("the value exists")
            {
               const auto value = multiContainer.Find<int32_t>(14);

               THEN("return a filled optional type")
               {
                  REQUIRE(value.has_value());
                  CHECK(*value == 14);
               }
            }

            WHEN("the value not exists")
            {
               const auto value = multiContainer.Find<int32_t>(32);

               THEN("return a empty optional type")
               {
                  CHECK_FALSE(value.has_value());
               }
            }
         }

         WHEN("its a object type")
         {
            WHEN("the value exists")
            {
               const auto value = multiContainer.Find<Test>({10, 11});

               THEN("return a filled optional type")
               {
                  REQUIRE(value.has_value());
                  CHECK(*value == Test{10, 11});
               }
            }

            WHEN("the value not exists")
            {
               const auto value = multiContainer.Find<Test>({10, 12});

               THEN("return a empty optional type")
               {
                  CHECK_FALSE(value.has_value());
               }
            }
         }
      }
   }
}
