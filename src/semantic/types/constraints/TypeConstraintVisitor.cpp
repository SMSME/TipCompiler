#include "TypeConstraintVisitor.h"
#include "TipAbsentField.h"
#include "TipAlpha.h"
#include "TipFunction.h"
#include "TipInt.h"
#include "TipRecord.h"
#include "TipRef.h"
#include "TipVar.h"
#include "TipBoolean.h"
#include "TipArray.h"

TypeConstraintVisitor::TypeConstraintVisitor(
    SymbolTable *st, std::shared_ptr<ConstraintHandler> handler)
    : symbolTable(st), constraintHandler(std::move(handler)){};

/*! \fn astToVar
 *  \brief Convert an AST node to a type variable.
 *
 * Utility function that creates type variables and uses declaration nodes
 * as a canonical representative for program variables.  There are two case
 * that need to be checked: if the variable is local to a function or if
 * it is a function value.
 */
std::shared_ptr<TipType> TypeConstraintVisitor::astToVar(ASTNode *n) {
  if (auto ve = dynamic_cast<ASTVariableExpr *>(n)) {
    ASTDeclNode *canonical;
    if ((canonical = symbolTable->getLocal(ve->getName(), scope.top()))) {
      return std::make_shared<TipVar>(canonical);
    } else if ((canonical = symbolTable->getFunction(ve->getName()))) {
      return std::make_shared<TipVar>(canonical);
    }
  } // LCOV_EXCL_LINE

  return std::make_shared<TipVar>(n);
}

bool TypeConstraintVisitor::visit(ASTFunction *element) {
  scope.push(element->getDecl());
  return true;
}

/*! \brief Type constraints for function definition.
 *
 * Type rules for "main(X1, ..., Xn) { ... return E; }":
 *   [[X1]] = [[Xn]] = [[E]] = int
 * To express this we will equate all type variables to int.
 *
 * Type rules for "X(X1, ..., Xn) { ... return E; }":
 *   [[X]] = ([[X1]], ..., [[Xn]]) -> [[E]]
 */
void TypeConstraintVisitor::endVisit(ASTFunction *element) {
  if (element->getName() == "main") {
    std::vector<std::shared_ptr<TipType>> formals;
    for (auto &f : element->getFormals()) {
      formals.push_back(astToVar(f));
      // all formals are int
      constraintHandler->handle(astToVar(f), std::make_shared<TipInt>());
    }

    // Return is the last statement and must be int
    auto ret = dynamic_cast<ASTReturnStmt *>(element->getStmts().back());
    constraintHandler->handle(astToVar(ret->getArg()),
                              std::make_shared<TipInt>());

    constraintHandler->handle(
        astToVar(element->getDecl()),
        std::make_shared<TipFunction>(formals, astToVar(ret->getArg())));
  } else {
    std::vector<std::shared_ptr<TipType>> formals;
    for (auto &f : element->getFormals()) {
      formals.push_back(astToVar(f));
    }

    // Return is the last statement
    auto ret = dynamic_cast<ASTReturnStmt *>(element->getStmts().back());

    constraintHandler->handle(
        astToVar(element->getDecl()),
        std::make_shared<TipFunction>(formals, astToVar(ret->getArg())));
  }
}

/*! \brief Type constraints for numeric literal.
 *
 * Type rules for "I":
 *   [[I]] = int
 */
void TypeConstraintVisitor::endVisit(ASTNumberExpr *element) {
  constraintHandler->handle(astToVar(element), std::make_shared<TipInt>());
}

/*! \brief Type constraints for binary operator.
 *
 * Type rules for "E1 op E2":
 *   [[E1 op E2]] = int
 * and if "op" is not equality or disequality
 *   [[E1]] = [[E2]] = int
 * otherwise
 *   [[E1]] = [[E2]]
 */
void TypeConstraintVisitor::endVisit(ASTBinaryExpr *element) {
  auto op = element->getOp();
  auto intType = std::make_shared<TipInt>();
  auto boolType = std::make_shared<TipBoolean>();

  if (op == ">=" || op == ">" || op == "<=" || op == "<"){
    // operands should be ints
    constraintHandler->handle(astToVar(element->getLeft()), intType);
    constraintHandler->handle(astToVar(element->getRight()), intType);
    constraintHandler->handle(astToVar(element), boolType);
  }

  else if (op == "and" || op == "or"){
    // operands should be boolean
    constraintHandler->handle(astToVar(element->getLeft()), boolType);
    constraintHandler->handle(astToVar(element->getRight()), boolType);
    constraintHandler->handle(astToVar(element), boolType);
  }

  else if (op != "==" && op != "!=") {
    // operands are integer
    constraintHandler->handle(astToVar(element->getLeft()), intType);
    constraintHandler->handle(astToVar(element->getRight()), intType);
    constraintHandler->handle(astToVar(element), intType);
  } 

  else {
    // operands have the same type
    constraintHandler->handle(astToVar(element->getLeft()),
                              astToVar(element->getRight()));
    constraintHandler->handle(astToVar(element), boolType);
  }
}

/*! \brief Type constraints for input statement.
 *
 * Type rules for "input":
 *  [[input]] = int
 */
void TypeConstraintVisitor::endVisit(ASTInputExpr *element) {
  constraintHandler->handle(astToVar(element), std::make_shared<TipInt>());
}

/*! \brief Type constraints for function application.
 *
 * Type Rules for "E(E1, ..., En)":
 *  [[E]] = ([[E1]], ..., [[En]]) -> [[E(E1, ..., En)]]
 */
void TypeConstraintVisitor::endVisit(ASTFunAppExpr *element) {
  std::vector<std::shared_ptr<TipType>> actuals;
  for (auto &a : element->getActuals()) {
    actuals.push_back(astToVar(a));
  }
  constraintHandler->handle(
      astToVar(element->getFunction()),
      std::make_shared<TipFunction>(actuals, astToVar(element)));
}

/*! \brief Type constraints for heap allocation.
 *
 * Type Rules for "alloc E":
 *   [[alloc E]] = &[[E]]
 */
void TypeConstraintVisitor::endVisit(ASTAllocExpr *element) {
  constraintHandler->handle(
      astToVar(element),
      std::make_shared<TipRef>(astToVar(element->getInitializer())));
}

/*! \brief Type constraints for address of.
 *
 * Type Rules for "&X":
 *   [[&X]] = &[[X]]
 */
void TypeConstraintVisitor::endVisit(ASTRefExpr *element) {
  constraintHandler->handle(
      astToVar(element), std::make_shared<TipRef>(astToVar(element->getVar())));
}

/*! \brief Type constraints for pointer dereference.
 *
 * Type Rules for "*E":
 *   [[E]] = &[[*E]]
 */
void TypeConstraintVisitor::endVisit(ASTDeRefExpr *element) {
  constraintHandler->handle(astToVar(element->getPtr()),
                            std::make_shared<TipRef>(astToVar(element)));
}

/*! \brief Type constraints for null literal.
 *
 * Type Rules for "null":
 *   [[null]] = & \alpha
 */
void TypeConstraintVisitor::endVisit(ASTNullExpr *element) {
  constraintHandler->handle(
      astToVar(element),
      std::make_shared<TipRef>(std::make_shared<TipAlpha>(element)));
}

/*! \brief Type rules for assignments.
 *
 * Type rules for "E1 = E":
 *   [[E1]] = [[E2]]
 *
 * Type rules for "*E1 = E2":
 *   [[E1]] = &[[E2]]
 *
 * Note that these are slightly more general than the rules in the SPA book.
 * The first allows for record expressions on the left hand side and the second
 * allows for more complex assignments, e.g., "**p = &x"
 */
void TypeConstraintVisitor::endVisit(ASTAssignStmt *element) {
  // If this is an assignment through a pointer, use the second rule above
  if (auto lptr = dynamic_cast<ASTDeRefExpr *>(element->getLHS())) {
    constraintHandler->handle(
        astToVar(lptr->getPtr()),
        std::make_shared<TipRef>(astToVar(element->getRHS())));
  } else {
    constraintHandler->handle(astToVar(element->getLHS()),
                              astToVar(element->getRHS()));
  }
}

/*! \brief Type constraints for while loop.
 *
 * Type rules for "while (E) S":
 *   [[E]] = bool
 */
void TypeConstraintVisitor::endVisit(ASTWhileStmt *element) {
  constraintHandler->handle(astToVar(element->getCondition()),
                            std::make_shared<TipBoolean>());
}

/*! \brief Type constraints for if statement.
 *
 * Type rules for "if (E) S1 else S2":
 *   [[E]] = int
 */
void TypeConstraintVisitor::endVisit(ASTIfStmt *element) {
  constraintHandler->handle(astToVar(element->getCondition()),
                            std::make_shared<TipBoolean>());
}

/*! \brief Type constraints for output statement.
 *
 * Type rules for "output E":
 *   [[E]] = int
 */
void TypeConstraintVisitor::endVisit(ASTOutputStmt *element) {
  constraintHandler->handle(astToVar(element->getArg()),
                            std::make_shared<TipInt>());
}

/*! \brief Type constraints for record expression.
 *
 * Type rule for "{ X1:E1, ..., Xn:En }":
 *   [[{ X1:E1, ..., Xn:En }]] = { f1:v1, ..., fn:vn }
 * where fi is the ith field in the program's global record
 * and vi = [[Ei]] if fi = Xi and \alpha otherwise
 */
void TypeConstraintVisitor::endVisit(ASTRecordExpr *element) {
  auto allFields = symbolTable->getFields();
  std::vector<std::shared_ptr<TipType>> fieldTypes;
  for (auto &f : allFields) {
    bool matched = false;
    for (auto &fe : element->getFields()) {
      if (f == fe->getField()) {
        fieldTypes.push_back(astToVar(fe->getInitializer()));
        matched = true;
        break;
      }
    }
    if (matched)
      continue;

    fieldTypes.push_back(std::make_shared<TipAbsentField>());
  }
  constraintHandler->handle(astToVar(element),
                            std::make_shared<TipRecord>(fieldTypes, allFields));
}

/*! \brief Type constraints for field access.
 *
 * Type rule for "E.X":
 *   [[E]] = { f1:v1, ..., fn:vn }
 * where fi is the ith field in the program's global record
 * and vi = [[E.X]] if fi = X and \alpha otherwise
 */
void TypeConstraintVisitor::endVisit(ASTAccessExpr *element) {
  auto allFields = symbolTable->getFields();
  std::vector<std::shared_ptr<TipType>> fieldTypes;
  for (auto &f : allFields) {
    if (f == element->getField()) {
      fieldTypes.push_back(astToVar(element));
    } else {
      fieldTypes.push_back(std::make_shared<TipAlpha>(element, f));
    }
  }
  constraintHandler->handle(astToVar(element->getRecord()),
                            std::make_shared<TipRecord>(fieldTypes, allFields));
}

/*! \brief Type constraints for error statement.
 *
 * Type rules for "error E":
 *   [[E]] = int
 */
void TypeConstraintVisitor::endVisit(ASTErrorStmt *element) {
  constraintHandler->handle(astToVar(element->getArg()),
                            std::make_shared<TipInt>());
}


//NEW//
/*
1. increment X X
2. decrement X X

3. modulo - X X
4. gte - X X 
5. gt - X  X
6. lte - X X 
9. and - X X
10. or - X X

7. negative X X
8. not X X

11. for range X
12. for loop X

13. length X
14. ternary X X

15. boolean X X
16. array index X
17. array default X X
18. array of X
*/




/*! \brief Type constraints for boolean.
 *
 * Type rules for "B":
 *   [[B]] = bool
 */
void TypeConstraintVisitor::endVisit(ASTBooleanExpr *element) {
  constraintHandler->handle(astToVar(element), std::make_shared<TipBoolean>());
}

/*! \brief Type constraints for array mul.
 *
 * Type Rules for "[e1, e2, ..., en]":
 *   ?
 */
void TypeConstraintVisitor::endVisit(ASTArrayMulExpr *element) {
  std::vector<std::shared_ptr<TipType>> arrItems;

  if (element->getExprs().empty()) {
    // Empty array gets an alpha type
    constraintHandler->handle(
      astToVar(element),
      std::make_shared<TipArray>(std::make_shared<TipAlpha>(element), false)
    );
    return;
  }

  // Get type of first element
  auto elementType = astToVar(element->getExprs().at(0));
  arrItems.push_back(elementType);

  // Ensure all elements have the same type as the first element
  for (size_t i = 1; i < element->getExprs().size(); i++) {
    constraintHandler->handle(elementType, astToVar(element->getExprs().at(i)));
    arrItems.push_back(astToVar(element->getExprs().at(i)));
  }

  // Constrain the entire expression to be an array of the element type
  constraintHandler->handle(
    astToVar(element),
    std::make_shared<TipArray>(elementType, false)
  );
}

/*! \brief Type constraints for array of.
 *
 * Type Rules for "[e1 of e2]":
 *   ?
 */
void TypeConstraintVisitor::endVisit(ASTArrayOfExpr *element) {
  // auto size = astToVar(element->getLeft());
  // constraintHandler->handle(
  //     size, std::make_shared<TipInt>());

  auto arrayType = std::make_shared<TipArray>(
        astToVar(element->getRight()), false
    );
  constraintHandler->handle(astToVar(element), arrayType);
}

/*! \brief Type constraints for increment statement.
 *
 * Type rules for "E++":
 *  [[E]] = int
 */
void TypeConstraintVisitor::endVisit(ASTIncrementStmt *element) {
  constraintHandler->handle(astToVar(element->getLeft()), std::make_shared<TipInt>());
}

/*! \brief Type constraints for decrement statement.
 *
 * Type rules for "E--":
 *  [[E]] = int
 */
void TypeConstraintVisitor::endVisit(ASTDecrementStmt *element) {
  constraintHandler->handle(astToVar(element->getLeft()), std::make_shared<TipInt>());
}

/*! \brief Type constraints for negative expression.
 *
 * Type rules for "-E":
 *  [[E]] = int
 *  E = -E
 */
void TypeConstraintVisitor::endVisit(ASTNegExpr *element) {
  constraintHandler->handle(astToVar(element->getNegate()), std::make_shared<TipInt>());
  constraintHandler->handle(astToVar(element), std::make_shared<TipInt>());
}

/*! \brief Type constraints for not expression.
 *
 * Type rules for "not E":
 *  [[E]] = boolean
 *  E = not E
 */
void TypeConstraintVisitor::endVisit(ASTNotExpr *element) {
  constraintHandler->handle(astToVar(element->getNot()), std::make_shared<TipBoolean>());
  constraintHandler->handle(astToVar(element), std::make_shared<TipBoolean>());
}

/*! \brief Type constraints for length expression.
 *
 * Type rules for "#E":
 *  [[E]] = array
 *  E1 = #E
 */
void TypeConstraintVisitor::endVisit(ASTLengthExpr *element) {
  // Alpha array type
  constraintHandler->handle(
      astToVar(element->getLength()),
      std::make_shared<TipArray>(std::make_shared<TipAlpha>(element), false)
  );

  // Ensure the length expression itself is an integer
  constraintHandler->handle(
      astToVar(element),
      std::make_shared<TipInt>()
  );
}


/*! \brief Type constraints for array index expression.
 *
 * Type rules for "E[1]":
 *  [[E]] = array
 *  E1 = E[1]
 */
void TypeConstraintVisitor::endVisit(ASTArrayIndexExpr *element) {
  auto elementType = std::make_shared<TipVar>(); // Type variable for the array element type


  constraintHandler->handle(astToVar(element->getName()), std::make_shared<TipArray>(astToVar(element), false));
  //std::make_shared<TipArray>(std::make_shared<TipInt>(), astToVar(element->getName()), true)
  constraintHandler->handle(astToVar(element->getIndex()), std::make_shared<TipInt>()); // Index is an int
  // constraintHandler->handle(astToVar(element), elementType); // Return the same for the array elements
}



/*! \brief Type constraints for ternary expression.
 *
 * Type rules for "E1 ? E2 : E3":
 *  [[E1]] = boolean
 *  [[E2]] = [[E3]]
 *  X = Y ? Z : W
 */
void TypeConstraintVisitor::endVisit(ASTTernaryExpr *element) {
  constraintHandler->handle(astToVar(element->getCondition()), std::make_shared<TipBoolean>());
  constraintHandler->handle(astToVar(element->getTrue()), astToVar(element->getFalse()));
  constraintHandler->handle(astToVar(element), astToVar(element->getFalse()));
}

/*! \brief Type constraints for a standard for loop expression.
 *
 * Type rules for "for (E1 : E2) S1"
 *  [[E1]] = [[E2]]
 *  for (val : arr) statement
 *
 */
void TypeConstraintVisitor::endVisit(ASTForStmt *element) {
    constraintHandler->handle(astToVar(element->getIterate()),
    std::make_shared<TipArray>(astToVar(element->getItem()), false));

}

/*! \brief Type constraints for a for range expression.
 * Type rules for "for "
 *  [[E1]] = int
 *  [E2]] = int
 *  [E3]] = int
 *  [E4]] = int
 *  for '(' E1 ':' E2  '..' E3 ('by' E4)? ')' S
 *
 */
void TypeConstraintVisitor::endVisit(ASTForRangeStmt *element) {
  constraintHandler->handle(astToVar(element->getIterator()), std::make_shared<TipInt>());
  constraintHandler->handle(astToVar(element->getA()), std::make_shared<TipInt>());
  constraintHandler->handle(astToVar(element->getB()), std::make_shared<TipInt>());
  if (element->getAmt() != nullptr) {
    constraintHandler->handle(astToVar(element->getAmt()), std::make_shared<TipInt>());
  }
}




