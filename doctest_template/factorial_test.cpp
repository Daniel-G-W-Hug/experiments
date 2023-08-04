// do this only in one test file (to create a main function for tests):

//#define CATCH_CONFIG_MAIN
//#include "catch2/catch.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "factorial.hpp"

TEST_CASE("factorial value test") {

    //
	// REQUIRE(precondition1);
	// REQUIRE(precondition2);
	// 

	CHECK(factorial(0) == 1.);
	CHECK(factorial(1) == 1.);
	CHECK(factorial(2) == 2.);
	CHECK(factorial(3) == 6.);
	CHECK(factorial(4) == 24.);
	CHECK(factorial(10) == 3628800.);

	
	// SUBCASE("Section A") {
	//
	//   CHECK(...);
	//   CHECK(...);
    //}

}
