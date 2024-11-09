#include "TipArray.h"
#include "TipVar.h"
#include "TipInt.h"
#include "TipRef.h"
#include "TipBoolean.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

TEST_CASE("TipArray: Test TipArray default - arity"
          "[TipArray]") {
    auto expr1 = std::make_shared<TipInt>();
    auto expr2 = std::make_shared<TipBoolean>();

  TipArray tipArr(expr1, expr2, false);
  REQUIRE(2 == tipArr.arity());

  SECTION("Array of getter") {
        TipArray tipArrO(expr1, expr2, true);
        REQUIRE(2 == tipArrO.arity());
  }
}
  

TEST_CASE("TipArray: Test empty TipArray", "[TipArray]") {
    TipArray tipArr;
    REQUIRE(tipArr.getInits().empty());
}



TEST_CASE("TipArray: Test equality "
          "[TipArray]") {
    auto expr1 = std::make_shared<TipInt>();
    auto expr2 = std::make_shared<TipBoolean>();

    TipArray tipArr(expr1, expr2, false); // Base array - standard
    TipArray tipArrO(expr1, expr2, true); // Base "array of" O for comparison
    TipArray tipArr1; // Base empty array

    SECTION("Equal when types are the same") {
        REQUIRE(tipArr == tipArrO);
    }

    SECTION("Equal when both empty") {
        TipArray tipArr2;

        REQUIRE(tipArr1 == tipArr2);
    }

    SECTION("Equal when one empty - 1") {
        REQUIRE(tipArr == tipArr1);
    }

    SECTION("Equal when one empty - 2") {
        REQUIRE(tipArrO == tipArr1);
    }


    SECTION("Equal two array of"){
        auto expr3 = std::make_shared<TipInt>();
        auto expr4 = std::make_shared<TipBoolean>();

        TipArray tipArrO1(expr3, expr4, true);

        REQUIRE(tipArrO == tipArrO1);
    }

    SECTION("Not equal when other value is not an array 1") {
        TipVar expr;
        REQUIRE(tipArr != expr);
    }

    SECTION("Not equal when other value is not an array 2") {
        TipVar expr1;
        REQUIRE(tipArrO != expr1);
    }

    SECTION("Not equal with different types - default") {
        auto expr5 = std::make_shared<TipInt>();
        TipArray tipArr1(expr1, expr5, false);

        REQUIRE(tipArr1 != tipArr);
    }

    SECTION("Not equal with different types - array of ") {
        auto expr6 = std::make_shared<TipInt>();
        TipArray tipArr2(expr1, expr6, true);

        REQUIRE(tipArrO != tipArr2);
    }
}

TEST_CASE("TipArray: Test output stream"
    "[TipArray]") {
    auto expr1 = std::make_shared<TipInt>();
    auto expr2 = std::make_shared<TipBoolean>();
    TipArray tipArrayA(expr1, expr2, false);

    TipArray tipArrayC(expr1, expr2, true);

    auto expectedValue = "[int,bool]";
    std::stringstream stream;
    stream << tipArrayA;
    std::string actualValue = stream.str();

    REQUIRE(expectedValue == actualValue);

    SECTION("Array of output") {
        auto expectedValue2 = "[int of bool]";
        std::stringstream stream2;
        stream2 << tipArrayC;
        std::string actualValue2 = stream2.str();

        REQUIRE(expectedValue2 == actualValue2);

    }
}


