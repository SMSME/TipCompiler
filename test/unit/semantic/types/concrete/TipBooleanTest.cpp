#include "TipBoolean.h"
#include "TipVar.h"

#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <string>

TEST_CASE("TipBoolean: test TipBoolean is a TipCons"
          "[tip_bool]") {
  TipBoolean t;
  REQUIRE_FALSE(nullptr == dynamic_cast<TipCons *>(&t));
}

TEST_CASE("TipBoolean: test TipBoolean is a TipType"
          "[tip_bool]") {
  TipBoolean t;
  REQUIRE_FALSE(nullptr == dynamic_cast<TipType *>(&t));
}

TEST_CASE("TipBoolean: test args is empty", "[tip_bool]") {
  TipBoolean t;
  REQUIRE(t.getArguments().empty());
}

TEST_CASE("TipBoolean: test toString returns bool", "[tip_bool]") {
  TipBoolean t;
  std::stringstream stream;
  stream << t;
  REQUIRE("bool" == stream.str());
}

TEST_CASE("TipBoolean: test all TipBooleans are equal", "[tip_bool]") {
  TipBoolean t1;
  TipBoolean t2;
  REQUIRE(t1 == t2);
}
