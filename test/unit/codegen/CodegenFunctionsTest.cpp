#include "AST.h"
#include "ASTNodeHelpers.h"
#include "InternalError.h"
#include "ParserHelper.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("CodegenFunction: ASTDeclNode throws InternalError on codegen",
          "[CodegenFunctions]") {
  ASTDeclNode node("foo");
  REQUIRE_THROWS_AS(node.codegen(), InternalError);
}

TEST_CASE("CodegenFunction: ASTAssignsStmt throws InternalError on LHS codegen "
          "nullptr",
          "[CodegenFunctions]") {
  ASTAssignStmt assignStmt(std::make_shared<nullcodegen::MockASTExpr>(),
                           std::make_shared<ASTInputExpr>());
  REQUIRE_THROWS_AS(assignStmt.codegen(), InternalError);
}

TEST_CASE("CodegenFunction: ASTAssignsStmt throws InternalError on RHS codegen "
          "nullptr",
          "[CodegenFunctions]") {
  ASTAssignStmt assignStmt(std::make_shared<ASTInputExpr>(),
                           std::make_shared<nullcodegen::MockASTExpr>());
  REQUIRE_THROWS_AS(assignStmt.codegen(), InternalError);
}

TEST_CASE(
    "CodegenFunction: ASTIfStmt throws InternalError on COND codegen nullptr",
    "[CodegenFunctions]") {
  ASTIfStmt ifStmt(
      std::make_shared<nullcodegen::MockASTExpr>(),
      std::make_shared<ASTReturnStmt>(std::make_shared<ASTNumberExpr>(42)),
      std::make_shared<ASTReturnStmt>(std::make_shared<ASTNumberExpr>(42)));
  REQUIRE_THROWS_AS(ifStmt.codegen(), InternalError);
}

TEST_CASE("CodegenFunction: ASTBinaryExpr throws InternalError on LHS codegen "
          "nullptr",
          "[CodegenFunctions]") {
  ASTBinaryExpr binaryExpr("+", std::make_shared<nullcodegen::MockASTExpr>(),
                           std::make_shared<ASTInputExpr>());
  REQUIRE_THROWS_AS(binaryExpr.codegen(), InternalError);
}

TEST_CASE("CodegenFunction: ASTBinaryExpr throws InternalError on RHS codegen "
          "nullptr",
          "[CodegenFunctions]") {
  ASTBinaryExpr binaryExpr("+", std::make_shared<ASTInputExpr>(),
                           std::make_shared<nullcodegen::MockASTExpr>());
  REQUIRE_THROWS_AS(binaryExpr.codegen(), InternalError);
}

TEST_CASE("CodegenFunction: ASTBinaryExpr throws InternalError on bad OP",
          "[CodegenFunctions]") {
  ASTBinaryExpr binaryExpr("ADDITION", std::make_shared<ASTInputExpr>(),
                           std::make_shared<ASTInputExpr>());
  REQUIRE_THROWS_AS(binaryExpr.codegen(), InternalError);
}

TEST_CASE("CodegenFunction: ASTOutputStmt throws InternalError on ARG codegen "
          "nullptr",
          "[CodegenFunctions]") {
  ASTOutputStmt outputStmt(std::make_shared<nullcodegen::MockASTExpr>());
  REQUIRE_THROWS_AS(outputStmt.codegen(), InternalError);
}

TEST_CASE(
    "CodegenFunction: ASTErrorStmt throws InternalError on ARG codegen nullptr",
    "[CodegenFunctions]") {
  ASTErrorStmt errorStmt(std::make_shared<nullcodegen::MockASTExpr>());
  REQUIRE_THROWS_AS(errorStmt.codegen(), InternalError);
}

TEST_CASE(
    "CodegenFunction: ASTVariableExpr throws InternalError on unknown NAME",
    "[CodegenFunctions]") {
  ASTVariableExpr variableExpr("foobar");
  REQUIRE_THROWS_AS(variableExpr.codegen(), InternalError);
}

TEST_CASE("CodegenFunction: ASTAllocExpr throws InternalError on INIT codegen "
          "nullptr",
          "[CodegenFunctions]") {
  ASTAllocExpr allocExpr(std::make_shared<nullcodegen::MockASTExpr>());
  REQUIRE_THROWS_AS(allocExpr.codegen(), InternalError);
}

TEST_CASE(
    "CodegenFunction: ASTRefExpr throws InternalError on VAR codegen nullptr",
    "[CodegenFunctions]") {
  ASTRefExpr refExpr(std::make_shared<nullcodegen::MockASTExpr>());
  REQUIRE_THROWS_AS(refExpr.codegen(), InternalError);
}

TEST_CASE(
    "CodegenFunction: ASTDeRefExpr throws InternalError on VAR codegen nullptr",
    "[CodegenFunctions]") {
  ASTDeRefExpr deRefExpr(std::make_shared<nullcodegen::MockASTExpr>());
  REQUIRE_THROWS_AS(deRefExpr.codegen(), InternalError);
}

TEST_CASE(
    "CodegenFunction: ASTAccessExpr throws InternalError on nonexistent field",
    "[CodegenFunctions]") {
  ASTAccessExpr accessExpr(std::make_shared<nullcodegen::MockASTExpr>(),
                           "foobar");
  REQUIRE_THROWS_AS(accessExpr.codegen(), InternalError);
}

TEST_CASE("CodegenFunction: ASTFunAppExpr throws InternalError on FUN codegen "
          "nullptr",
          "[CodegenFunctions]") {
  std::vector<std::shared_ptr<ASTExpr>> actuals;
  ASTFunAppExpr funAppExpr(std::make_shared<nullcodegen::MockASTExpr>(),
                           actuals);
  REQUIRE_THROWS_AS(funAppExpr.codegen(), InternalError);
}



// NEW Tests//
/* BooleanExpr X
 * Increment X
 * Decrement X
 * Negative Expr X
 * Not Expr X
 * Ternary X
 * Array Expr
 * Array of Expr
 * Array Index
 * Array Len
 * For Each
 * For Range
 */
// TEST_CASE("CodegenFunction: ASTForRangeStmt basic codegen test", "[CodegenFunctions]") {
//   // Create the basic components
//   auto iterator = std::make_shared<ASTVariableExpr>("i");
//   auto start = std::make_shared<ASTNumberExpr>(0);
//   auto end = std::make_shared<ASTNumberExpr>(5);
//   auto step = std::make_shared<ASTNumberExpr>(1);
//   auto body = std::make_shared<ASTOutputStmt>(iterator);
//
//   // Create the for range statement
//   ASTForRangeStmt forStmt(iterator, start, end, step, body);
//   forStmt.codegen();
//   // This will let you set a breakpoint and step through codegen()
//   REQUIRE_NOTHROW(forStmt.codegen());
// }


// TEST_CASE("CodegenFunction: ASTBooleanExpr generates correct boolean constant",
//           "[CodegenFunctions]") {
//   llvm::LLVMContext llvmContext; // Needed to create LLVM constants
//
//   SECTION("Generates true constant") {
//     ASTBooleanExpr trueExpr(true); // Initialize with true
//     auto result = trueExpr.codegen(); // Generate LLVM code
//     REQUIRE(result != nullptr);
//   }
//
//   SECTION("Generates false constant") {
//     ASTBooleanExpr falseExpr(false); // Initialize with false
//     auto result = falseExpr.codegen(); // Generate LLVM code
//     REQUIRE(result != nullptr);
//   }
// }

// TEST_CASE("CodegenFunction: ASTIncrementStmt throws InternalError on codegen", 
//           "[CodegenFunctions]") {
//   ASTIncrementStmt incrementStmt(std::make_shared<nullcodegen::MockASTExpr>());
//   REQUIRE_THROWS_AS(incrementStmt.codegen(), InternalError);
// }

// TEST_CASE("CodegenFunction: ASTDecrementStmt throws InternalError on codegen", 
//           "[CodegenFunctions]") {
//   ASTDecrementStmt decrementStmt(std::make_shared<nullcodegen::MockASTExpr>());
//   REQUIRE_THROWS_AS(decrementStmt.codegen(), InternalError);
// }

// // TEST_CASE("CodegenFunction: ASTIncrementStmt increments a value", "[CodegenFunctions]") {
// //     auto initialValue = std::make_shared<ASTNumberExpr>(5);
// //     ASTIncrementStmt incrementStmt(initialValue);
// //     REQUIRE_NOTHROW(incrementStmt.codegen());
// // }

// // TEST_CASE("CodegenFunction: ASTDecrementStmt decrements a value", "[CodegenFunctions]") {
// //     auto initialValue = std::make_shared<ASTNumberExpr>(5);
// //     ASTDecrementStmt decrementStmt(initialValue);
// //     REQUIRE_NOTHROW(decrementStmt.codegen()); 
// // }

// TEST_CASE("CodegenFunction: ASTNegExpr negates a positive value", "[CodegenFunctions]") {
//     auto positiveExpr = std::make_shared<ASTNumberExpr>(5);
//     ASTNegExpr negExpr(positiveExpr);
//     REQUIRE_NOTHROW(negExpr.codegen());
// }

// TEST_CASE("CodegenFunction: ASTNegExpr negates zero", "[CodegenFunctions]") {
//     auto zeroExpr = std::make_shared<ASTNumberExpr>(0);
//     ASTNegExpr negExpr(zeroExpr);
//     REQUIRE_NOTHROW(negExpr.codegen());
// }