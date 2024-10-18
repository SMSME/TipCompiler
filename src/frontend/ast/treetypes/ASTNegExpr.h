#pragma once

#include "ASTExpr.h"

/*! \brief Class for array index expressions
 */
class ASTNegExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> NEGATE;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTNegExpr(std::shared_ptr<ASTExpr> NEGATE)
        :  NEGATE(NEGATE) {}
    ASTExpr *getNegate() const { return NEGATE.get(); }
    
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};
