#include "ASTIncrementStmt.h"
#include "ASTVisitor.h"

void ASTIncrementStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getLeft()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTIncrementStmt::print(std::ostream &out) const {
  out << *getLeft() << "++";
  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTIncrementStmt::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;

  children.push_back(LEFT);
  
  return children;
}

llvm::Value *ASTIncrementStmt::codegen() {
  return nullptr;
}