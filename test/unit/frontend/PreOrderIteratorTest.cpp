#include "PreOrderIterator.h"
#include "ASTHelper.h"
#include "PrettyPrinter.h"
#include "SyntaxTree.h"

#include <catch2/catch_test_macros.hpp>

#include <Iterator.h>
#include <iostream>

TEST_CASE("PreOrderIterator: Test Traversal", "[PreOrderIterator]") {
  std::stringstream stream;
  stream << R"(
      short() {
        var x;
        return 5;
      }
    )";

  std::shared_ptr<ASTProgram> ast = std::move(ASTHelper::build_ast(stream));

  std::vector<std::string> expected_node_order = {
      "50c958e71584bef4c6a4334580c1669c4da35197a53365db8f53d54b1775f848",
      "short() {...}",
      "short",
      "var x;",
      "x",
      "return 5;",
      "5",
  };

  SyntaxTree syntaxTree(ast);
  int i = 0;
  for (auto iter = syntaxTree.begin(""); iter != syntaxTree.end(""); ++iter) {
    std::stringstream actual_node;
    actual_node << *iter->getRoot();
    REQUIRE(expected_node_order.at(i++) == actual_node.str());
  }
}

TEST_CASE("PreOrderIterator: Test dereference", "[PreOrderIterator]") {
  std::stringstream stream;
  stream << R"(
      short() {
        var x;
        return 5;
      }
    )";
  std::shared_ptr<ASTProgram> ast = std::move(ASTHelper::build_ast(stream));
  SyntaxTree syntaxTree(ast);
  auto iter = syntaxTree.begin("");
  REQUIRE(syntaxTree.getRoot() == (*iter).getRoot());
  REQUIRE(syntaxTree.getRoot() == iter->getRoot());
}

TEST_CASE("PreOrderIterator: Test Cloning", "[PreOrderIterator]") {
  std::stringstream stream;
  stream << R"(
      short() {
        var x;
        return 5;
      }
    )";

  std::shared_ptr<ASTProgram> ast = std::move(ASTHelper::build_ast(stream));
  SyntaxTree syntaxTree(ast);
  auto iter = new PreOrderIterator(syntaxTree, false);
  iter->get_tree().getRoot()->getChildren();
  auto cloned = iter->clone();

  REQUIRE(iter->get_tree().getRoot() == cloned->get_tree().getRoot());
}

TEST_CASE("PreOrderIterator: Exhausted increment returns gracefully",
          "[PreOrderIterator]") {
  std::stringstream stream;
  stream << R"(
      short() {
        var x;
        return 5;
      }
    )";

  std::shared_ptr<ASTProgram> ast = std::move(ASTHelper::build_ast(stream));
  SyntaxTree syntaxTree(ast);
  auto iter = syntaxTree.begin("");
  for (; iter != syntaxTree.end(""); ++iter)
    ;

  REQUIRE_NOTHROW(iter++);
}

TEST_CASE("PreOrderIterator: Sentinel end", "[PreOrderIterator]") {
  std::stringstream stream;
  stream << R"(
      short() {
        var x;
        return 5;
      }
    )";

  std::shared_ptr<ASTProgram> ast = std::move(ASTHelper::build_ast(stream));
  SyntaxTree syntaxTree(ast);
  auto begin = PreOrderIterator(syntaxTree, false);
  auto end = PreOrderIterator(syntaxTree, true);

  REQUIRE(begin != end);
}
// TEST_CASE("PreOrderIterator: Test Children", "[PreOrderIterator]") {
//   std::stringstream stream;
//   stream << R"(
//       short() {
//         var x;
//         x = [1, 2, 3];
//         return 5;
//       }
//     )";
//
//   std::shared_ptr<ASTProgram> ast = std::move(ASTHelper::build_ast(stream));
//
//   std::vector<std::string> expected_node_order = {
//     "50c958e71584bef4c6a4334580c1669c4da35197a53365db8f53d54b1775f848",
//     "short() {...}",
//     "short",
//     "var x;",
//     "x",
//     "return 5;",
//     "5",
// };
//
//   SyntaxTree syntaxTree(ast);
//   int i = 0;
//   for (auto iter = syntaxTree.begin(""); iter != syntaxTree.end(""); ++iter) {
//     std::stringstream actual_node;
//     actual_node << *iter->getRoot()->getChildren();
//     REQUIRE(expected_node_order.at(i++) == actual_node.str());
//   }
// }

