#include "TipArray.h"
#include "TipVar.h"
#include "TipInt.h"
#include "TipRef.h"

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
  
}

TEST_CASE("TipArray: Test TipArray, array of - getters"
        "[TipArray]") {
    std::shared_ptr<TipType> expr1;
    std::shared_ptr<TipType> expr2;

    TipArray tipArr(expr1, expr2);

    REQUIRE(2 == tipArr.getInits().size());
}

TEST_CASE("TipArray: Test empty TipArray", "[TipArray]") {
    TipArray tipArr;
    REQUIRE(0 == tipArr.getInits().size());

    SECTION("Empty array of"){
        auto expr1 = std::make_shared<TipInt>(0);
        auto expr2 = std::make_shared<TipInt>(7);

        TipArray tipArr(expr1, expr2);

        REQUIRE(tipArr.getInits().size() == 2);   
        REQUIRE(*(tipArr.getInits().at(0)) == *expr1);  
        REQUIRE(*(tipArr.getInits().at(1)) == *expr2);

        REQUIRE(tipArr.arr_of == true); 
        REQUIRE(tipArr.getInits().empty());

        }


}

TEST_CASE("TipArray: Test arity", "[TipArray]") {
    std::vector<std::shared_ptr<TipType>> inits{
        std::make_shared<TipInt>(), std::make_shared<TipInt>(),
        std::make_shared<TipInt>(), std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
    };

    TipArray tipArr(inits);
    REQUIRE(5 == tipArr.arity());
}

TEST_CASE("TipArray: Test arity - of", "[TipArray]") {
    std::shared_ptr<TipType> expr1;
    std::shared_ptr<TipType> expr2;

    TipArray tipArr(expr1, expr2);

    REQUIRE(2 == tipArr.arity());
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
    std::vector<std::shared_ptr<TipType>> initsB{
        std::make_shared<TipInt>(),
        std::make_shared<TipInt>(),
        };
        TipArray tipArrayB(initsB);

        REQUIRE(tipArrayA == tipArrayB);
    }

    SECTION("Equal when empty default") {
        TipArray tipArrayB;
        TipArray tipArrayC;

        REQUIRE(tipArrayC == tipArrayB);
    }


    }


// TEST_CASE("TipBoolean: test toString returns bool", "[tip_bool]") {
//   TipBoolean t;
//   std::stringstream stream;
//   stream << t;
//   REQUIRE("bool" == stream.str());
// }

// TEST_CASE("TipBoolean: test all TipBooleans are equal", "[tip_bool]") {
//   TipBoolean t1;
//   TipBoolean t2;
//   REQUIRE(t1 == t2);
// }
