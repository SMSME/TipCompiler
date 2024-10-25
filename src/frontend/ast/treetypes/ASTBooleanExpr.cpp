#include "ASTBooleanExpr.h"
#include "ASTVisitor.h"

void ASTBooleanExpr::accept(ASTVisitor *visitor) {
  visitor->visit(this);
  visitor->endVisit(this);
}

std::ostream &ASTBooleanExpr::print(std::ostream &out) const {
  out << getOp();
  return out;
} // LCOV_EXCL_LINE

// LCOV_EXCL_START
llvm::Value *ASTBooleanExpr::codegen() {
    return nullptr;
}
// LCOV_EXCL_END
