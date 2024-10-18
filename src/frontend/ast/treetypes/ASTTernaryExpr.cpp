#include "ASTTernaryExpr.h"
#include "ASTVisitor.h"

void ASTTernaryExpr::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getCondition()->accept(visitor);
        getTrue()->accept(visitor);
        getFalse()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTTernaryExpr::print(std::ostream &out) const {
    out << *getCondition() << "? ";
    out << *getTrue();
    out << ": " << *getFalse(); //all this might need to be one line?? most likely not
    return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTTernaryExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;

    children.push_back(COND);
    children.push_back(TRUE);
    children.push_back(FALSE);

    return children;
}

llvm::Value *ASTTernaryExpr::codegen() {
    return nullptr;
}
