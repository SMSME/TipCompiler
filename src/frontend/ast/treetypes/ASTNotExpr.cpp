#include "ASTNotExpr.h"
#include "ASTVisitor.h"

void ASTNotExpr::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getNot()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTNotExpr::print(std::ostream &out) const {
    out << "not " << *getNot();
    return out;
}
// LCOV_EXCL_START
std::vector<std::shared_ptr<ASTNode>> ASTNotExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;

    children.push_back(NOT);

    return children;
}

llvm::Value *ASTNotExpr::codegen() {
    return nullptr;
}
// LCOV_EXCL_END