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

  TipArray tipArr(inits);
  REQUIRE(inits.size() == tipArr.getInits().size());

  SECTION("Array of getter") {
        auto expr1 = std::make_shared<TipBoolean>();
        auto expr2 = std::make_shared<TipBoolean>();

        TipArray tipArr(expr1, expr2);

        REQUIRE(2 == tipArr.arity());
  }
}
  

TEST_CASE("TipArray: Test empty TipArray", "[TipArray]") {
    TipArray tipArr;
    REQUIRE(0 == tipArr.getInits().size());
}

TEST_CASE("TipArray: Test arity", "[TipArray]") {
    std::vector<std::shared_ptr<TipType>> inits{
        std::make_shared<TipInt>(), std::make_shared<TipInt>(),
        std::make_shared<TipInt>(), std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
    };

    TipArray tipArr(inits);
    REQUIRE(5 == tipArr.arity());

    SECTION("Arity for array of") {
        std::shared_ptr<TipType> expr1;
        std::shared_ptr<TipType> expr2;

        TipArray tipArr(expr1, expr2);

        REQUIRE(2 == tipArr.arity());}
}


TEST_CASE("TipArray: Test equality "
          "[TipArray]") {
    std::vector<std::shared_ptr<TipType>> initsA{
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>()
        };
    TipArray tipArrayA(initsA);

    SECTION("Equal when types are the same and same length") {
    std::vector<std::shared_ptr<TipType>> initsB{
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>()
        };
        TipArray tipArrayB(initsB);

        REQUIRE(tipArrayA == tipArrayB);
    }

    SECTION("Equal when different length") {
    std::vector<std::shared_ptr<TipType>> initsC{
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
        };
        TipArray tipArrayC(initsC);

        REQUIRE(tipArrayA == tipArrayC);
    }

    SECTION("Equal when empty") {
        TipArray tipArrayC;
        TipArray tipArrayD;

        REQUIRE(tipArrayC == tipArrayD);
    }

    SECTION("Not equal when one empty") {
        TipArray tipArrayC;
        REQUIRE(tipArrayC != tipArrayA);
    }

    SECTION("Not equal with different types - default") {
        std::vector<std::shared_ptr<TipType>> initsC{
        std::make_shared<TipRef>(std::make_shared<TipInt>()),
        std::make_shared<TipRef>(std::make_shared<TipInt>()),
        std::make_shared<TipRef>(std::make_shared<TipInt>())
        };
        TipArray tipArrayC(initsC);

        REQUIRE(tipArrayC != tipArrayA);
    }

    SECTION("Not equal with different types - array of") {
        auto expr1 = std::make_shared<TipBoolean>();
        auto expr2 = std::make_shared<TipBoolean>();

        TipArray tipArrayC(expr1, expr2);

        REQUIRE(tipArrayC != tipArrayA);
    }

    }

    TEST_CASE("TipArray: Test output stream"
          "[TipArray]") {
    std::vector<std::shared_ptr<TipType>> initsA{
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>()
        };
    TipArray tipArrayA(initsA);

    auto expectedValue = "[int,int,int]";
    std::stringstream stream;
    stream << tipArrayA;
    std::string actualValue = stream.str();

    REQUIRE(expectedValue == actualValue);
}

