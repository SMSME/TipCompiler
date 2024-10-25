#pragma once

#include "ASTExpr.h"

/*! \brief Class for not expressions
 */
class ASTNotExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> NOT;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTNotExpr(std::shared_ptr<ASTExpr> NOT)
        :  NOT(NOT) {}
    ASTExpr *getNot() const { return NOT.get(); }
    
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};
