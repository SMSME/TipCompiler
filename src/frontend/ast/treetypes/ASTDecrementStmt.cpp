// #include "ASTIncrementStmt.h"
// #include "ASTVisitor.h"

// void ASTForStmt::accept(ASTVisitor *visitor) {
//   if (visitor->visit(this)) {
//     getLeft()->accept(visitor);
//   }
//   visitor->endVisit(this);
// }

// std::ostream &ASTIncrementStmt::print(std::ostream &out) const {
//   out << *getLeft() << getOp();
//   return out;
// }

// std::vector<std::shared_ptr<ASTNode>> ASTIncrementStmt::getChildren() {
//   std::vector<std::shared_ptr<ASTNode>> children;

//   children.push_back(LEFT);
  
//   return children;
// }

// llvm::Value *ASTForStmt::codegen() {
//     return nullptr;
// }