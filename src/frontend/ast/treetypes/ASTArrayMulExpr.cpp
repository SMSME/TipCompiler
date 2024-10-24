#include "ASTArrayMulExpr.h"
#include "ASTVisitor.h"
#include "ASTinternal.h"

ASTArrayMulExpr::ASTArrayMulExpr(std::vector<std::shared_ptr<ASTExpr>> EXPRS) {
  for (auto &expr : EXPRS) {
    std::shared_ptr<ASTExpr> e = expr;
    this->EXPRS.push_back(e);
  }
}

std::vector<ASTExpr *> ASTArrayMulExpr::getExprs() const {
  return rawRefs(EXPRS);
}

void ASTArrayMulExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    for (auto e : getExprs()) {
      e->accept(visitor);
    }
  }
  visitor->endVisit(this);
}

std::ostream &ASTArrayMulExpr::print(std::ostream &out) const { ////
  out << "[";
  bool skip = true;
  for (auto &e : getExprs()) {
    if (skip) {
      skip = false;
      out << *e;
      continue;
    }
    out << "," << *e;
  }
  out << "]";
  return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTArrayMulExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  for (auto &expr : EXPRS) {
    children.push_back(expr);
  }
  return children;
}

llvm::Value *ASTArrayMulExpr::codegen() {
    return nullptr;
}

