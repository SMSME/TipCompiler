#pragma once

#include "ASTExpr.h"

/*! \brief Class for defining an array.
 */
class ASTArrayMulExpr : public ASTExpr {
  std::vector<std::shared_ptr<ASTExpr>> EXPRS;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTArrayMulExpr(std::vector<std::shared_ptr<ASTExpr>> EXPRS);
  std::vector<ASTExpr *> getExprs() const;
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
