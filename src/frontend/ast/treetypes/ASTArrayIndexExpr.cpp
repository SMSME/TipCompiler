#include "ASTArrayIndexExpr.h"
#include "ASTVisitor.h"

void ASTArrayIndexExpr::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getName()->accept(visitor);
        getIndex()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTArrayIndexExpr::print(std::ostream &out) const {
    out << *getName() << "[";
    out << *getIndex() << "]";
    return out;
}
// LCOV_EXCL_START
std::vector<std::shared_ptr<ASTNode>> ASTArrayIndexExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;

    children.push_back(NAME);
    children.push_back(INDEX);

    return children;
}

// llvm::Value *ASTArrayIndexExpr::codegen() {
//     return nullptr;
// }
// LCOV_EXCL_END
