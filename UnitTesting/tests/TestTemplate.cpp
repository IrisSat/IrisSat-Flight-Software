//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// File Description:
//  Template test file for CppUTest.
//
// History
// 2019-04-18 by Tamkin Rahman
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "CppUTest/TestHarness.h"

extern "C"
{
    // Place headers for C files here.
    // #include "sample.h"
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// TESTS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
TEST_GROUP(FooTestGroup)
{
   void setup()
   {
      // Init stuff
   }

   void teardown()
   {
      // Uninit stuff
   }
};

TEST(FooTestGroup, Foo)
{
   // Test FOO
}

TEST(FooTestGroup, MoreFoo)
{
   // Test more FOO
}

TEST_GROUP(BarTestGroup)
{
   void setup()
   {
      // Init Bar
   }
};

TEST(BarTestGroup, Bar)
{
   // Test Bar
}
