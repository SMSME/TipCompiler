#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for decrement.
 */
class ASTDecrementStmt : public ASTStmt {
  std::shared_ptr<ASTExpr> LEFT;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTDecrementStmt(std::shared_ptr<ASTExpr> LEFT)
      : LEFT(LEFT) {}
  ASTExpr *getLeft() const { return LEFT.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
