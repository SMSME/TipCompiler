#include "ASTLengthExpr.h"
#include "ASTVisitor.h"

void ASTLengthExpr::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getLength()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTLengthExpr::print(std::ostream &out) const {
    out << "#" << *getLength();
    return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTLengthExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;

    children.push_back(LENGTH);

    return children;
}

llvm::Value *ASTLengthExpr::codegen() {
    return nullptr;
}
