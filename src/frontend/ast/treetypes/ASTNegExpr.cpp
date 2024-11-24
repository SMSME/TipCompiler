#include "ASTNegExpr.h"
#include "ASTVisitor.h"

void ASTNegExpr::accept(ASTVisitor *visitor) {
    if (visitor->visit(this)) {
        getNegate()->accept(visitor);
    }
    visitor->endVisit(this);
}

std::ostream &ASTNegExpr::print(std::ostream &out) const {
    out << "-" << *getNegate();
    return out;
}

std::vector<std::shared_ptr<ASTNode>> ASTNegExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;

    children.push_back(NEGATE);

    return children;
}
