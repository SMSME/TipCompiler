#include "ASTHelper.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("ASTAccessExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
  std::stringstream stream;
  stream << R"(
      foo() {
         return {f : 0}.f;
      }
    )";

  auto ast = ASTHelper::build_ast(stream);
  auto expr = ASTHelper::find_node<ASTAccessExpr>(ast);

  std::stringstream o1;
  o1 << expr->getField();
  REQUIRE(o1.str() == "f");

  std::stringstream o2;
  o2 << *expr->getRecord();
  REQUIRE(o2.str() == "{f:0}");
}

TEST_CASE("ASTAllocExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return alloc 2 + 3;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTAllocExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getInitializer();
    REQUIRE(o1.str() == "(2+3)");
}

TEST_CASE("ASTAssignStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(p) {
         *p = 2 + 7;
         return *p - 1;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTAssignStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getLHS();
    REQUIRE(o1.str() == "(*p)");

    std::stringstream o2;
    o2 << *stmt->getRHS();
    REQUIRE(o2.str() == "(2+7)");
}

TEST_CASE("ASTBinaryExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         x = x + foo();
         return x;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTBinaryExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getLeft();
    REQUIRE(o1.str() == "x");

    std::stringstream o2;
    o2 << *expr->getRight();
    REQUIRE(o2.str() == "foo()");

    std::stringstream o3;
    o3 << expr->getOp();
    REQUIRE(o3.str() == "+");
}

TEST_CASE("ASTBlockStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         if (1 > 0) {
             x = 0;
             x = 1;
         }
         return x+1;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTBlockStmt>(ast);

    auto stmts = stmt->getStmts();
    REQUIRE(stmts.size() == 2);
}

TEST_CASE("ASTDeclNodeTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto decl = ASTHelper::find_node<ASTDeclNode>(ast);

    REQUIRE(decl->getName() == "x");
}

TEST_CASE("ASTDeclStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var v1, v2, v3, v4;
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTDeclStmt>(ast);

    auto stmts = stmt->getVars();
    REQUIRE(stmts.size() == 4);
}

TEST_CASE("ASTDerefExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(p) {
         return **p;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTDeRefExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getPtr();
    REQUIRE(o1.str() == "(*p)");
}

TEST_CASE("ASTErrorStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         error 13 - 1;
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTErrorStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getArg();
    REQUIRE(o1.str() == "(13-1)");
}

TEST_CASE("ASTFieldExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return {f : 13};
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTFieldExpr>(ast);

    std::stringstream o1;
    o1 << expr->getField();
    REQUIRE(o1.str() == "f");

    std::stringstream o2;
    o2 << *expr->getInitializer();
    REQUIRE(o2.str() == "13");
}

TEST_CASE("ASTFunAppExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return bar(1,2,3);
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTFunAppExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getFunction();
    REQUIRE(o1.str() == "bar");

    auto arguments = expr->getActuals();
    REQUIRE(arguments.size() == 3);
}

TEST_CASE("ASTFunctionTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x, y) {
         var z;
         var r;
         z = x - 1;
         z = z * 2;
         return x + y;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto fun = ASTHelper::find_node<ASTFunction>(ast);

    std::stringstream o1;
    o1 << *fun->getDecl();
    REQUIRE(o1.str() == "foo");

    REQUIRE(fun->getName() == "foo");
    REQUIRE(!fun->isPoly());
    REQUIRE(fun->getFormals().size() == 2);
    REQUIRE(fun->getDeclarations().size() == 2);
    REQUIRE(fun->getStmts().size() == 3);
}

TEST_CASE("ASTIfStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(c) {
         var x;
         if (c > 0)
            x = 13;
         else
            x = 7;
         return x;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTIfStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getCondition();
    REQUIRE(o1.str() == "(c>0)");

    std::stringstream o2;
    o2 << *stmt->getThen();
    REQUIRE(o2.str() == "x = 13;");

    std::stringstream o3;
    o3 << *stmt->getElse();
    REQUIRE(o3.str() == "x = 7;");
}

TEST_CASE("ASTIfStmtTest: No else.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(c) {
         var x;
         x = 7;
         if (c > 0) x = 13;
         return x;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTIfStmt>(ast);

    REQUIRE(stmt->getElse() == nullptr);
}

TEST_CASE("ASTInputExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return input;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTInputExpr>(ast);

    REQUIRE(expr != nullptr);
}

TEST_CASE("ASTNullExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return null;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTNullExpr>(ast);

    REQUIRE(expr != nullptr);
}

TEST_CASE("ASTNumberExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return 13;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTNumberExpr>(ast);

    REQUIRE(expr->getValue() == 13);
}

TEST_CASE("ASTOutputStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         output 17;
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTOutputStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getArg();
    REQUIRE(o1.str() == "17");
}

TEST_CASE("ASTRecordExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return {f : 0, g : 1, h : 2};
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTRecordExpr>(ast);

    REQUIRE(expr->getFields().size() == 3);
}

TEST_CASE("ASTRefExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         var x;
         return &x;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTRefExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getVar();
    REQUIRE(o1.str() == "x");
}

TEST_CASE("ASTReturnStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return 123;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTReturnStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getArg();
    REQUIRE(o1.str() == "123");
}

TEST_CASE("ASTVariableExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         return x + 1;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTVariableExpr>(ast);

    REQUIRE(expr->getName() == "x");
}

TEST_CASE("ASTWhileStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var y;
         while (x > 0) {
            x = x - 1;
         }
         return {f : 0}.f;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto stmt = ASTHelper::find_node<ASTWhileStmt>(ast);

    std::stringstream o1;
    o1 << *stmt->getCondition();
    REQUIRE(o1.str() == "(x>0)");

    std::stringstream o2;
    o2 << *stmt->getBody();
    REQUIRE(o2.str() == "{ x = (x-1); }");
}

/*
   New Added Tests:
   Array expression X
   Array index X
   Length expression X 
   
   Negative expression X
   Not expression X
   
   True and False X
   Decrement and Increment X
   Ternary expression X
   
   For statement X
   For range statement X

   Relational expression (>=, <, <=, %, and, or) ?
*/

TEST_CASE("ASTBooleanExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo() {
         return true;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTBooleanExpr>(ast);

    REQUIRE(expr->getOp() == true);
}

TEST_CASE("ASTDecrementStmt: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var z;
         z = 12;
         z--;
         return 0;
      }
    )";

   auto ast = ASTHelper::build_ast(stream);
   auto stmt = ASTHelper::find_node<ASTDecrementStmt>(ast);

   std::stringstream left;
   left << *stmt->getLeft();
   REQUIRE(left.str() == "z");
}

TEST_CASE("ASTIncrementStmt: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var z;
         z = 12;
         z++;
         return 0;
      }
    )";

   auto ast = ASTHelper::build_ast(stream);
   auto stmt = ASTHelper::find_node<ASTIncrementStmt>(ast);

   std::stringstream left;
   left << *stmt->getLeft();
   REQUIRE(left.str() == "z");
}

TEST_CASE("ASTNotExpr: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var z;
         x = not z;
         return 0;
      }
    )";

   auto ast = ASTHelper::build_ast(stream);
   auto expr = ASTHelper::find_node<ASTNotExpr>(ast);

   std::stringstream n;
   n << *expr->getNot();
   REQUIRE(n.str() == "z");
}

TEST_CASE("ASTArrayMulExprMultiple: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var e1, e2, arr;
         arr = []
         return 0;
      }
    )";

   auto ast = ASTHelper::build_ast(stream);
   auto expr = ASTHelper::find_node<ASTArrayMulExpr>(ast);

   auto exprs = expr->getExprs();
   REQUIRE(exprs.size() == 0);
}

TEST_CASE("ASTArrayMulExprNone: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var e1, e2, e3, arr;
         arr = [e1, e2, e3]
         return 0;
      }
    )";

   auto ast = ASTHelper::build_ast(stream);
   auto expr = ASTHelper::find_node<ASTArrayMulExpr>(ast);

   auto exprs = expr->getExprs();
   REQUIRE(exprs.size() == 3);
}

TEST_CASE("ASTArrayOfExprDefault: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var e1, e2, arr;
         arr = [e1 of e2]
         return 0;
      }
    )";

   auto ast = ASTHelper::build_ast(stream);
   auto expr = ASTHelper::find_node<ASTArrayOfExpr>(ast);

   std::stringstream left;
   left << *expr->getLeft();
   REQUIRE(left.str() == "e1");

   std::stringstream right;
   right << *expr->getRight();
   REQUIRE(right.str() == "e2");
}


TEST_CASE("ASTLengthExpr: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var z, expr1;
         z = [expr1];
         a = #z
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTLengthExpr>(ast);

   std::stringstream len;
   len << *expr->getLength();
   REQUIRE(len.str() == "z");
}

TEST_CASE("ASTArrayIndexExpr: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         var z;
         x = z[1];
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTArrayIndexExpr>(ast);

   std::stringstream name;
   name << *expr->getName();
   REQUIRE(name.str() == "z");

   std::stringstream index;
   index << *expr->getIndex();
   REQUIRE(index.str() == "1");
}


TEST_CASE("ASTTernaryExpr: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(c) {
         var x;
         x = (1 > 2) ? 3 : 4;
         return 0;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTTernaryExpr>(ast);

    std::stringstream o1;
    o1 << *expr->getCondition();
    REQUIRE(o1.str() == "(1>2)");

    std::stringstream o2;
    o2 << *expr->getTrue();
    REQUIRE(o2.str() == "3");

    std::stringstream o3;
    o3 << *expr->getFalse();
    REQUIRE(o3.str() == "4");
}

TEST_CASE("ASTNegExprTest: Test methods of AST subtype.",
          "[ASTNodes]") {
    std::stringstream stream;
    stream << R"(
      foo(x) {
         return -x;
      }
    )";

    auto ast = ASTHelper::build_ast(stream);
    auto expr = ASTHelper::find_node<ASTNegExpr>(ast);

   std::stringstream neg;
   neg << *expr->getNegate();
   REQUIRE(neg.str() == "x");
}

TEST_CASE("ASTForStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
      foo(x) {
         var item, collection, x;
         for (item : collection) item = x;
         return 0;
      }
   )";

   auto ast = ASTHelper::build_ast(stream);
   auto stmt = ASTHelper::find_node<ASTForStmt>(ast);

   std::stringstream item;
   item << *stmt->getItem();
   REQUIRE(item.str() == "item");

   std::stringstream iterate;
   iterate << *stmt->getIterate();
   REQUIRE(iterate.str() == "collection");

   std::stringstream then;
   then << *stmt->getThen();
   REQUIRE(then.str() == "item = x;");
}

TEST_CASE("ASTForRangeStmtTest: Test methods of AST subtype.",
          "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
      foo(x) {
         var e1, e2, e3, stmt;
         for (e1 : e2 .. e3) stmt = x;
         return 0;
      }
   )";

   auto ast = ASTHelper::build_ast(stream);
   auto stmt = ASTHelper::find_node<ASTForRangeStmt>(ast);

   std::stringstream iter;
   iter << *stmt->getIterator();
   REQUIRE(iter.str() == "e1");

   std::stringstream a;
   a << *stmt->getA();
   REQUIRE(a.str() == "e2");

   std::stringstream b;
   b << *stmt->getB();
   REQUIRE(b.str() == "e3");

   REQUIRE(stmt->getAmt() == nullptr);

   std::stringstream then;
   then << *stmt->getThen();
   REQUIRE(then.str() == "stmt = x;");
}

TEST_CASE("ASTForRangeStmtTestAmt: Test methods of AST subtype.",
          "[ASTNodes]") {
   std::stringstream stream;
   stream << R"(
      foo(x) {
         var e1, e2, e3, stmt;
         for (e1 : e2 .. e3 by 1) stmt = x;
         return 0;
      }
   )";

   auto ast = ASTHelper::build_ast(stream);
   auto stmt = ASTHelper::find_node<ASTForRangeStmt>(ast);

   std::stringstream iter;
   iter << *stmt->getIterator();
   REQUIRE(iter.str() == "e1");

   std::stringstream a;
   a << *stmt->getA();
   REQUIRE(a.str() == "e2");

   std::stringstream b;
   b << *stmt->getB();
   REQUIRE(b.str() == "e3");

   std::stringstream amt;
   amt << *stmt->getAmt();
   REQUIRE(amt.str() == "1");

   std::stringstream then;
   then << *stmt->getThen();
   REQUIRE(then.str() == "stmt = x;");
}