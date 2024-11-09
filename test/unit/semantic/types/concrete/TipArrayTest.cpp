#include "TipArray.h"
#include "TipVar.h"
#include "TipInt.h"
#include "TipRef.h"
#include "TipBoolean.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

TEST_CASE("TipArray: Test TipArray default - getters"
          "[TipArray]") {
  std::vector<std::shared_ptr<TipType>> inits{std::make_shared<TipInt>(),
                                               std::make_shared<TipInt>(),
                                               std::make_shared<TipInt>()};

  TipArray tipArr(inits, false);
  REQUIRE(inits.size() == tipArr.getInits().size());

  SECTION("Array of getter") {
        auto expr1 = std::make_shared<TipInt>();
        auto expr2 = std::make_shared<TipBoolean>();

        TipArray tipArrA(expr1, expr2, true);

        REQUIRE(2 == tipArrA.arity());
  }
}
  

TEST_CASE("TipArray: Test empty TipArray", "[TipArray]") {
    TipArray tipArr;
    REQUIRE(tipArr.getInits().empty());
}

TEST_CASE("TipArray: Test arity", "[TipArray]") {
    std::vector<std::shared_ptr<TipType>> inits{
        std::make_shared<TipInt>(), std::make_shared<TipInt>(),
        std::make_shared<TipInt>(), std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
    };

    TipArray tipArr(inits, false);
    REQUIRE(5 == tipArr.arity());

    SECTION("Arity for array of") {
        std::shared_ptr<TipType> expr1;
        std::shared_ptr<TipType> expr2;

        TipArray tipArrO(expr1, expr2, true);

        REQUIRE(2 == tipArrO.arity());}
}


TEST_CASE("TipArray: Test equality "
          "[TipArray]") {
    std::vector<std::shared_ptr<TipType>> initsA{
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>()
        };
    TipArray tipArrayA(initsA, false); // Base array A for comparison

    auto expr1 = std::make_shared<TipInt>();
    auto expr2 = std::make_shared<TipInt>();

    TipArray tipArrayO(expr1, expr2, true); // Base "array of" O for comparison

    SECTION("Equal when types are the same and same length") {
        std::vector<std::shared_ptr<TipType>> initsB{
            std::make_shared<TipInt>(),
            std::make_shared<TipInt>(),
            std::make_shared<TipInt>()
            };
        TipArray tipArrayB(initsB, false);

        REQUIRE(tipArrayA == tipArrayB);
    }

    SECTION("Equal when different length") {
        std::vector<std::shared_ptr<TipType>> initsC{
            std::make_shared<TipInt>(),
            std::make_shared<TipInt>(),
            };
        TipArray tipArrayC(initsC, false);

        REQUIRE(tipArrayA == tipArrayC);
    }

    SECTION("Equal when empty") {
        TipArray tipArrayD;
        TipArray tipArrayE;

        REQUIRE(tipArrayE == tipArrayD);
    }

    SECTION("Equal two array of"){
        auto expr4 = std::make_shared<TipInt>();
        auto expr5 = std::make_shared<TipInt>();

        TipArray tipArrayO1(expr4, expr5, true);

        REQUIRE(tipArrayO == tipArrayO1);
    }

    SECTION("Not equal when other value is not an array 1") {
        TipVar expr;
        REQUIRE(tipArrayA != expr);
    }

    SECTION("Not equal when other value is not an array 2") {
        TipVar expr;
        REQUIRE(tipArrayO != expr);
    }

    SECTION("Not equal when one empty") {
        TipArray tipArrayF;
        REQUIRE(tipArrayF != tipArrayA);
    }

    SECTION("Not equal with different types - default") {
        std::vector<std::shared_ptr<TipType>> initsG{
            std::make_shared<TipRef>(std::make_shared<TipInt>()),
            std::make_shared<TipRef>(std::make_shared<TipInt>()),
            std::make_shared<TipRef>(std::make_shared<TipInt>())
            };
        TipArray tipArrayG(initsG, false);

        REQUIRE(tipArrayG != tipArrayA);
    }

    SECTION("Not equal with different types - array of ") {
        auto expr6 = std::make_shared<TipInt>();
        auto expr7 = std::make_shared<TipBoolean>();
        TipArray tipArrayO2(expr6, expr7, true);

        REQUIRE(tipArrayO != tipArrayO2);
    }
}

TEST_CASE("TipArray: Test output stream"
    "[TipArray]") {
    std::vector<std::shared_ptr<TipType>> initsA{
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>()
        };
    TipArray tipArrayA(initsA, false);

    auto expr1 = std::make_shared<TipBoolean>();
    auto expr2 = std::make_shared<TipBoolean>();

    TipArray tipArrayC(expr1, expr2, true);

    auto expectedValue = "[int,int,int]";
    std::stringstream stream;
    stream << tipArrayA;
    std::string actualValue = stream.str();

    REQUIRE(expectedValue == actualValue);

    SECTION("Array of output") {
        auto expectedValue2 = "[bool of bool]";
        std::stringstream stream2;
        stream2 << tipArrayC;
        std::string actualValue2 = stream2.str();

        REQUIRE(expectedValue2 == actualValue2);

    }
}


