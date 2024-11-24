#include "ASTArrayOfExpr.h"
#include "ASTVisitor.h"

void ASTArrayOfExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getLeft()->accept(visitor);
    getRight()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTArrayOfExpr::print(std::ostream &out) const {
  out << "[" << *getLeft() << " of " << *getRight() << "]";
  return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTArrayOfExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.push_back(LEFT);
  children.push_back(RIGHT);
  return children;
}

