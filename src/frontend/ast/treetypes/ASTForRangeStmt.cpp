#include "ASTForRangeStmt.h"
#include "ASTVisitor.h"

void ASTForRangeStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getIterator()->accept(visitor);
    getA()->accept(visitor);
    getB()->accept(visitor);
    if (getAmt() != nullptr) {
      getAmt()->accept(visitor);
    }
    getThen()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTForRangeStmt::print(std::ostream &out) const {
  out << "for (" << *getIterator() << " : " << *getA() << " .. " << *getB();
  if (getAmt() != nullptr) {
    out << " by " << *getAmt();
  }
  out << ") ";
  out << *getThen();
  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTForRangeStmt::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;

  children.push_back(ITERATOR);
  children.push_back(A);
  children.push_back(B);
  if (getAmt() != nullptr) {
    children.push_back(AMT);
  }
  children.push_back(THEN);
  return children;
}

llvm::Value *ASTForRangeStmt::codegen() {
    return nullptr;
}