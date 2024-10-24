#pragma once

#include "ASTExpr.h"

/*! \brief Class for a an array of expression.
 */
class ASTArrayOfExpr : public ASTExpr {
  std::shared_ptr<ASTExpr> LEFT, RIGHT;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTArrayOfExpr(std::shared_ptr<ASTExpr> LEFT, std::shared_ptr<ASTExpr> RIGHT)
      : LEFT(LEFT), RIGHT(RIGHT) {}
  ASTExpr *getLeft() const { return LEFT.get(); }
  ASTExpr *getRight() const { return RIGHT.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
