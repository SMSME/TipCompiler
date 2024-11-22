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

  TipArray tipArr(expr1, false);
  REQUIRE(1 == tipArr.arity());

}
  

TEST_CASE("TipArray: Test empty TipArray", "[TipArray]") {
    auto expr1 = std::make_shared<TipInt>();
    TipArray tipArr(expr1, true); // Base empty array
    REQUIRE(tipArr.isEmpty);
}



TEST_CASE("TipArray: Test equality "
          "[TipArray]") {
    auto expr1 = std::make_shared<TipInt>();
    auto expr2 = std::make_shared<TipBoolean>();

    TipArray tipArr(expr1, false); // Int arr - standard
    TipArray tipArr9(expr1, false);
    TipArray tipArrO(expr2, false); // Boolean arr
    TipArray tipArr1(expr1, true); // Base empty array
    TipArray tipArr7(expr1, true); // Base empty array

    SECTION("Equal when types are the same") {
        REQUIRE(tipArr == tipArr9);
    }

    SECTION("Equal when both empty") {
        REQUIRE(tipArr1 == tipArr7);
    }

    SECTION("Equal when one empty - 1") {
        REQUIRE(tipArr == tipArr1);
    }

    SECTION("Equal when one empty - 2") {
        REQUIRE(tipArr1 == tipArr);
    }


    // SECTION("Equal two array of"){
    //     auto expr3 = std::make_shared<TipInt>();
    //     auto expr4 = std::make_shared<TipBoolean>();
    //
    //     TipArray tipArrO1(expr3, expr4, true);
    //
    //     REQUIRE(tipArrO == tipArrO1);
    // }

    SECTION("Not equal when other value is not an array 1") {
        TipVar expr;
        REQUIRE(tipArr != expr);
    }

    SECTION("Not equal when other value is not an array 2") {
        TipVar expr4;
        REQUIRE(tipArrO != expr4);
    }

    SECTION("Not equal with different types - default") {

        REQUIRE(tipArr != tipArrO);
    }

}

TEST_CASE("TipArray: Test output stream"
    "[TipArray]") {
    auto expr1 = std::make_shared<TipInt>();
    auto expr2 = std::make_shared<TipBoolean>();
    TipArray tipArrayA(expr1, false);
    TipArray tipArrayB(expr2, false);

    TipArray tipArrayC(expr1,  true);


    auto expectedValue = "[int]";
    std::stringstream stream;
    stream << tipArrayA;
    std::string actualValue = stream.str();

    REQUIRE(expectedValue == actualValue);

    SECTION("Bool Array ") {
        auto expectedValue2 = "[bool]";
        std::stringstream stream2;
        stream2 << tipArrayB;
        std::string actualValue2 = stream2.str();

        REQUIRE(expectedValue2 == actualValue2);

    }


    SECTION("Array empty") {
        auto expectedValue2 = "[]";
        std::stringstream stream2;
        stream2 << tipArrayC;
        std::string actualValue2 = stream2.str();

        REQUIRE(expectedValue2 == actualValue2);

    }
}


