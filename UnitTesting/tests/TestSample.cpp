//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// File Description:
//  Sample test file for CppUTest.
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
TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
   FAIL("Fail me!");
}
