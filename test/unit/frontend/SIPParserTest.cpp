#include "ExceptionContainsWhat.h"
#include "FrontEnd.h"
#include "ParseError.h"
#include "ParserHelper.h"

#include <catch2/catch_test_macros.hpp>


/* 
BASE TESTS:

Precedence tests???

Boolean:
- true
- false

Expression tests:

- Negative expression
- ! expression
- Ternary expressions
- Mod expression (within multiplicative) x
- Relational expression 
    - GTE x
    - LTE x 
    - LT x
- Logical
    - ||
    - &&

Array Tests:
- Creating array expression
- Length of array
- Indexing into array

For Loop Tests:
- For loop statement
- Range statement

Increment and decrement statements

*/


TEST_CASE("SIP Parser: operators", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      operators() {
        var x;
        x = y % 2;
        x = 1 >= 0;
        x = 0 < 1;
        x = 0 <= 1;
        x = 1 > 0 and 0 < 1;
        x = 1 > 0 or 0 < 1;
        x = not (x > 1);
        x = -x;
        return z;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: increments/decrements", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      operators() {
        var x;
        x++;
        x--;
        return z;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: booleans", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      operators() {
        var x;
        x = false;
        x = true;
        return z;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}


TEST_CASE("SIP Parser: mod higher precedence than add", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(main() { return 1 + 2 % 3; })";
    std::string expected = "(expr (expr 1) + (expr (expr 2) % (expr 3)))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

// /************ Ternary Expression ************/
TEST_CASE("SIP Parser: ternary expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
    tern() { 
        var x, y, z;
        z = (x == 1) ? y : z;
        z = x ? y : z;
        z = x ? (y ? x : z) : z;
        z = x ? (y ? x : z) : (z ? x : y);
        z = (z ? y : x) ? (y ? x : z) : (z ? x : y);
        return 0; 
        }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: ternary expression right-associativity", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        main() {
            return a ? b : c ? d : e;
        }
    )";

    std::string expected = "(expr (expr a) ? (expr b) : (expr (expr c) ? (expr d) : (expr e)))";

    std::string tree = ParserHelper::parsetree(stream);

    REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Parser: illegal ternary expression ", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
    ill_tern() { 
        var x, y, z;
        z = 1;
        z = (x == 1) ? 1; 
        return 0; 
        }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal ternary expression only colon", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
    ill_tern_2() { 
        var x, y, z;
        z = 1;
        z = (x == 1) : 1; 
        return 0; 
        }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal ternary no second and third xpressions", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
    ill_tern() { 
        var x, y, z;
        z = 1;
        z = (x == 1) ? : ; 
        return 0; 
        }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal ternary no first expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
    ill_tern() { 
        var x, y, z;
        z = 1;
         ? 1 : 2 ; 
        return 0; 
        }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal ternary no second expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
    ill_tern() { 
        var x, y, z;
        z = 1;
         z = (x == 1 ? : 2 ; 
        return 0; 
        }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal ternary expression no third expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
    ill_tern() { 
        var x, y, z;
        z = 1;
        z = (x == 1) ? 1 : ; 
        return 0; 
        }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

// /************ Array Expression ************/
TEST_CASE("SIP Parser: array expressions", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        var x, z;
        x = [];
        x = [2];
        x = [1,2,3];
        x = [1 of 4];
        return z;
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array length expressions", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        var x, z;
        x = #[];
        x = #[2];
        x = #[1,2,3];
        x = #[1 of 4];
        return z;
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array index expressions", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        var x, y, z, s;
        x = [1, 3, 4];
        y = x[0];
        z = [1 of 3];
        s = z[0];
        return y;
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal array statement ", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        return [2++ ;];
      }
    )";
  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal array of statement ", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        return [2++ ; of 2];
      }
    )";
  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}



// /************ For Loops Expression ************/
TEST_CASE("SIP Parser: for loop", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      loop() {
        var x, y, z;
          x = 1; z = 5; y = 0;
          for (x : z) {
            y = y + 1;
          }
        return y;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: range for loop", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      loop() {
        var x, y, z;
          x = 1; z = 1; y = 5;
          for (x : z .. y by 2) {
            y = y + 1;
          }
        return y;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: range for loop no by", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      loop() {
        var x, y, z;
          x = 1; z = 1; y = 5;
          for (x : z .. y) {
            y = y + 1;
          }
        return y;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal for loop", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      loop() {
        var x, y, z;
          x = 1; z = 5; y = 0;
          for (x : z) {
            2;
          }
        return y;
      }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal range loop no .. ", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      loop() {
        var x, y, z;
          x = 1; z = 1; y = 5;
          for (x : z  y) {
            y = y + 1;
          }
        return y;
      }
    )";

  REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}
