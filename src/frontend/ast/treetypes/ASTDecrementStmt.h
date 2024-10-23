// #pragma once

// #include "ASTExpr.h"

// /*! \brief Class for decrement.
//  */
// class ASTDecrementStmt : public ASTStmt {
//   std::shared_ptr<ASTExpr> LEFT;
//   std::string OP;

// public:
//   std::vector<std::shared_ptr<ASTNode>> getChildren() override;
//   ASTDecrementStmt(std::shared_ptr<ASTExpr> LEFT, const std::string &OP)
//       : LEFT(LEFT), OP(OP) {}
//   ASTExpr *getLeft() const { return LEFT.get(); }
//   std::string getOp() const { return OP; }
//   void accept(ASTVisitor *visitor) override;
//   llvm::Value *codegen() override;

// protected:
//   std::ostream &print(std::ostream &out) const override;
// };
