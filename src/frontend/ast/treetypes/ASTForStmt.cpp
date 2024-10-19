#include "ASTForStmt.h"
#include "ASTVisitor.h"

void ASTForStmt::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getItem()->accept(visitor);
    getIterate()->accept(visitor);
    getThen()->accept(visitor);
  }
  visitor->endVisit(this);
}

std::ostream &ASTForStmt::print(std::ostream &out) const {
  out << "for (" << *getItem() << ":" << *getIterate() << ") " << *getThen() ;
  return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTForStmt::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;

  children.push_back(ITEM);
  children.push_back(ITERATE);
  children.push_back(THEN);
  
  return children;
}

llvm::Value *ASTForStmt::codegen() {
    return nullptr;
}