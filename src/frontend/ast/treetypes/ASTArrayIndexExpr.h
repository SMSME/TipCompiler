#pragma once

#include "ASTExpr.h"

/*! \brief Class for array index expressions
 */
class ASTArrayIndexExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> NAME, INDEX;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTArrayIndexExpr(std::shared_ptr<ASTExpr> NAME, std::shared_ptr<ASTExpr> INDEX)
        :  NAME(NAME), INDEX(INDEX) {}
    ASTExpr *getName() const { return NAME.get(); }
    ASTExpr *getIndex() const { return INDEX.get(); }
    
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};
