#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for if-then-else.
 */
class ASTForRangeStmt : public ASTStmt {
  std::shared_ptr<ASTExpr> ITERATOR, A, B, AMT;
  std::shared_ptr<ASTStmt> THEN;

public:
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTForRangeStmt(std::shared_ptr<ASTExpr> ITERATOR, std::shared_ptr<ASTExpr> A, 
                    std::shared_ptr<ASTExpr> B, std::shared_ptr<ASTExpr> AMT, std::shared_ptr<ASTStmt> THEN)
      : ITERATOR(ITERATOR), A(A), B(B), AMT(AMT), THEN(THEN) {}
  ASTExpr *getIterator() const { return ITERATOR.get(); }
  ASTExpr *getA() const { return A.get(); }
  ASTExpr *getB() const { return B.get(); }
  ASTStmt *getThen() const { return THEN.get(); }

  /*! \fn getAmt
   * \return Amt expr if it exists and nullptr otherwise.
   */
  ASTExpr *getAmt() const { return AMT.get(); }
  void accept(ASTVisitor *visitor) override;
  llvm::Value *codegen() override;

protected:
  std::ostream &print(std::ostream &out) const override;
};
