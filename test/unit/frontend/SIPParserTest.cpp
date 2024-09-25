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
        x = y + 1;
        x = y - 1;
        x = y * 1;
        x = y / 1;
        x = y % 2;
        x = -1;
        x = 1 > 0;
        x = 1 >= 0;
        x = 0 < 1;
        x = 0 <= 1;
        x = 1 == 0;
        x = 1 != 0;
        x = 1 > 0 && 0 < 1;
        x = 1 > 0 || 0 < 1;
        return z;
      }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

//RELATIONAL EXPRESSIONS
TEST_CASE("SIP Lexer: New legal comparison token - LT", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; if (x < 0) x = x + 1; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: New legal comparison token - GTE", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; if (x >= 0) x = x + 1; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: New legal comparison token - LTE", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; if (x <= 0) x = x + 1; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

// Altered test case MOD illegal comparison token now legal, require_false -> require_true
TEST_CASE("SIP Lexer: New legal operator token - MOD", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; if (x == 0) x = x % 2; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

// BOOLEAN TESTS //
TEST_CASE("SIP Lexer: New legal token - true", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      main() { return true; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: New legal token - false", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      main() { return false; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: New legal operator token - AND", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; if (x > 0 && x > -1) x = x % 2; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: New legal operator token - OR", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; if (x > 0 || x > -1) x = x % 2; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: New legal operator token - NOT", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; if (!(x < 0)) x = x % 2; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: New legal operator token - ++", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; x = 0; x++; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: New legal operator token - --", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; x = 0; x--; return x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Lexer: New legal operator token - -", "[SIP Lexer]") {
  std::stringstream stream;
  stream << R"(
      operators() { var x; x = 1+x; return -x; }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

// /************ Ternary Expression ************/
TEST_CASE("SIP Parser: ternary expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
    tern() { 
        var x, y, z;
        z = 1;
        z = (x == 1) ? 1 : 2; 
        return 0; 
        }
    )";

  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal ternary expression no colon", "[SIP Parser]") {
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
    ill_tern() { 
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
TEST_CASE("SIP Parser: empty array expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        return [];
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array expression one item", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        return [2];
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array expression multiple items", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        return [1, 2, 3];
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array of expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        return [1 of 4];
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: length of expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        return #[1 of 4];
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: length expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        return #[];
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: index expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        x = [1, 2, 3];
        return x[0];
      }
    )";
  REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: index of expression", "[SIP Parser]") {
  std::stringstream stream;
  stream << R"(
      arr() {
        x = [1 of 3];
        return x[0];
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






// //TODO: Replace with for loop
// TEST_CASE("SIP Parser: conditionals", "[SIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       short() {
//         var x, y, z;
//         if (x>0) {
//           for (y : z) {
//             y = y + 1;
//           }
//         } else {
//           z = z + 1;
//         }
//         return z;
//       }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

//TODO: Replace with for loop range
// TEST_CASE("TIP Parser: operators", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() {
//         var x;
//         x = y + 1;
//         x = y - 1;
//         x = y * 1;
//         x = y / 1;
//         x = -1;
//         x = 1 > 0;
//         x = 1 == 0;
//         x = 1 != 0;
//         return z;
//       }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: pointers", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() {
//         var x, y;
//         y = alloc 13;
//         x = &y;
//         *y = 42;
//         **x = 7;
//         x = null;
//         return *y;
//       }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: funs", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       foo(f, a) { return f(a); }
//       bar(x) { return x + 1; }
//       baz(y) { return foo(bar, y); }
//       main(z) { return baz(z); }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: decls", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       main() { var x; var y; var z; return 0; }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: parens", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       main() { return ((1 + 2) * 3) - ((((2 - 1)))); }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: io stmts", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       main() { var x; x = input; output x; error x; output x * x; error (x * x); return x; }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: records", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       r() { var x, y; x = {f1:0, f2:13}; y = x.f1; x.f2 = y + a; return x.f2; }
//       nr() { var x, y; x = {f1: {nf1:1, nf2:2}, f2:13}; y = x.f1.nf1; x.f1.nf2 = x.f2; return x.f1.nf1; }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: block stmts", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       main() { var x, y; { x = 0; { y = x + 1; } } return x + y; }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: identifiers and literals", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       main() { var __314, __; __314 = 00007; __ = 0000; return __; }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: dangling else", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() { var x; if (x==0) if (x==0) x = x + 1; else x = x-1; return x; }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: input", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() { var x; if (input) if (input) x = 1; else x = -1; return x; }
//       outin() { output input; return 0; }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: address of field access", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() { var x, y; y = &(x.f); return *y; }
//     )";

//   REQUIRE(ParserHelper::is_parsable(stream));
// }

// /* These tests checks for operator precedence.
//  * They access the parse tree and ensure that the higher precedence
//  * operator is nested more deeply than the lower precedence operator.
//  */
// TEST_CASE("TIP Parser: mul higher precedence than add", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(main() { return 1 + 2 * 3; })";
//   std::string expected = "(expr (expr 1) + (expr (expr 2) * (expr 3)))";
//   std::string tree = ParserHelper::parsetree(stream);
//   REQUIRE(tree.find(expected) != std::string::npos);
// }

// TEST_CASE("TIP Parser: access higher precedence than deref", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(main() { var p; return *p.f; })";
//   std::string expected = "(expr * (expr (expr p) . f))";
//   std::string tree = ParserHelper::parsetree(stream);
//   REQUIRE(tree.find(expected) != std::string::npos);
// }

// TEST_CASE("TIP Parser: fun app higher precedence than deref", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(main() { var p; return *p(); })";
//   std::string expected = "(expr * (expr (expr p) ( )))";
//   std::string tree = ParserHelper::parsetree(stream);
//   REQUIRE(tree.find(expected) != std::string::npos);
// }

// /************ The following are expected to fail parsing ************/

// TEST_CASE("TIP Parser: decl after stmt", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       main() { var x; x = 0; var z; return 0; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: missing semi-colon", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       short() { var x; if (x>0) x = x + 1 return 0; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: missing paren", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       short() { var x; if x>0 x = x + 1; return 0; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: unbalanced blocks", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       main() { var x, y; { x = 0; y = x + 1; } } return x + y; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: unbalanced binary expr", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() { var x; x = y + + 1; return -x; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: bad field delimiter", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() { var x; x = {a:0, b 0}; return x.a; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: bad field separator", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() { var x; x = {a:0 b:0}; return x.a; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: no expression statements", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() { var x, y; x = y = 1; return x; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Parser: keywords as ids", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       if() { var x; if (x <= 0) x = x + 1; return x; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }


// TEST_CASE("TIP Lexer: illegal identifier token", "[TIP Lexer]") {
//   std::stringstream stream;
//   stream << R"(
//       operators() { var $x; if ($x == 0) $x = $x + 2; return $x; }
//     )";

//   REQUIRE_FALSE(ParserHelper::is_parsable(stream));
// }

// TEST_CASE("TIP Lexer: Lexing exceptions are thrown", "[TIP Lexer]") {
//   std::stringstream stream;
//   stream << R"(
//       main() {
//         return ";
//       }
//     )";

//   REQUIRE_THROWS_MATCHES(FrontEnd::parse(stream), ParseError,
//                          ContainsWhat("token recognition error"));
// }

// TEST_CASE("TIP Parser: Parsing exceptions are thrown", "[TIP Parser]") {
//   std::stringstream stream;
//   stream << R"(
//       main() {
//         return 0
//       }
//     )";

//   REQUIRE_THROWS_MATCHES(FrontEnd::parse(stream), ParseError,
//                          ContainsWhat("missing ';'"));
// }