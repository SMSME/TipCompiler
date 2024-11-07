#include "TipArray.h"
#include "TipVar.h"
#include "TipInt.h"
#include "TipRef.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

TEST_CASE("TipArray: test TipArray default - getters"
          "[TipArray]") {
  std::vector<std::shared_ptr<TipType>> inits{std::make_shared<TipInt>(),
                                               std::make_shared<TipInt>(),
                                               std::make_shared<TipInt>()};

  TipArray tipArr(inits);

  REQUIRE(inits.size() == tipArr.getInits().size());
}

TEST_CASE("TipArray: test TipArray, array of - getters"
        "[TipArray]") {
    std::shared_ptr<TipType> expr1;
    std::shared_ptr<TipType> expr2;

    TipArray tipArr(expr1, expr2);

    REQUIRE(2 == tipArr.getInits().size());
}

TEST_CASE("TipArray: test empty TipArray", "[TipArray]") {
    TipArray tipArr;
    REQUIRE(0 == tipArr.getInits().size());
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
