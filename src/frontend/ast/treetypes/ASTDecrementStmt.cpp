#include "ASTDecrementStmt.h"
#include "ASTVisitor.h"

void ASTDecrementStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getLeft()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTDecrementStmt::print(std::ostream &out) const {
  out << *getLeft() << "--";
  return out;
}
// LCOV_EXCL_START
std::vector<std::shared_ptr<ASTNode>> ASTDecrementStmt::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;

  children.push_back(LEFT);
  
  return children;
}

// llvm::Value *ASTDecrementStmt::codegen() {
//     return nullptr;
// }
// LCOV_EXCL_END