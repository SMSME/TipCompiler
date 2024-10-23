#pragma once

#include "ASTExpr.h"

/*! \brief Class for a boolean expression.
 */
class ASTBooleanExpr : public ASTExpr {
  bool OP;

public:
  ASTBooleanExpr(bool OP) : OP(OP) {}
  bool getOp() const { return OP; }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
