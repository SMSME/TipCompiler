#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for.
 */
class ASTForStmt : public ASTStmt {
  std::shared_ptr<ASTExpr> ITEM, ITERATE;
  std::shared_ptr<ASTStmt> THEN;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTForStmt(std::shared_ptr<ASTExpr> ITEM, std::shared_ptr<ASTExpr> ITERATE,
            std::shared_ptr<ASTStmt> THEN)
      : ITEM(ITEM), ITERATE(ITERATE), THEN(THEN) {}
  ASTExpr *getItem() const { return ITEM.get(); }
  ASTExpr *getIterate() const { return ITERATE.get(); }
  ASTStmt *getThen() const { return THEN.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
