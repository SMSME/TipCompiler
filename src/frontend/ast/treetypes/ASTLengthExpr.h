#pragma once

#include "ASTExpr.h"

/*! \brief Class for length expressions
 */
class ASTLengthExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> LENGTH;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTLengthExpr(std::shared_ptr<ASTExpr> LENGTH)
        :  LENGTH(LENGTH) {}
    ASTExpr *getLength() const { return LENGTH.get(); }
    
    void accept(ASTVisitor *visitor) override;
    llvm::Value *codegen() override;

protected:
    std::ostream &print(std::ostream &out) const override;
};
