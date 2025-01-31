#include "CheckAssignable.h"
#include "PrettyPrinter.h"
#include "SemanticError.h"

#include <sstream>

#include "loguru.hpp"

namespace {

// Return true if expression has an l-value
bool isAssignable(ASTExpr *e) {
  if (dynamic_cast<ASTVariableExpr *>(e))
    return true;
  if (dynamic_cast<ASTAccessExpr *>(e)) {
    ASTAccessExpr *access = dynamic_cast<ASTAccessExpr *>(e);
    if (dynamic_cast<ASTVariableExpr *>(access->getRecord())) {
      return true;
    } else if (dynamic_cast<ASTDeRefExpr *>(access->getRecord())) {
      return true;
    } else {
      return false;
    }
  }
  if (dynamic_cast<ASTArrayIndexExpr *>(e))
    return true;
  return false;
}

} // namespace

void CheckAssignable::endVisit(ASTAssignStmt *element) {
  LOG_S(1) << "Checking assignability of " << *element;

  if (isAssignable(element->getLHS()))
    return;

  // Assigning through a pointer is also permitted
  if (dynamic_cast<ASTDeRefExpr *>(element->getLHS()))
    return;

  std::ostringstream oss;
  oss << "Assignment error on line " << element->getLine() << ": ";
  if (dynamic_cast<ASTAccessExpr *>(element->getLHS())) {
    ASTAccessExpr *access = dynamic_cast<ASTAccessExpr *>(element->getLHS());
    oss << *access->getRecord()
        << " is an expression, and not a variable corresponding to a record\n";
  } else {
    oss << *element->getLHS() << " not an l-value\n";
  }
  throw SemanticError(oss.str());
}

void CheckAssignable::endVisit(ASTRefExpr *element) {
  LOG_S(1) << "Checking assignability of " << *element;

  if (isAssignable(element->getVar()))
    return;

  std::ostringstream oss;
  oss << "Address of error on line " << element->getLine() << ": ";
  oss << *element->getVar() << " not an l-value\n";
  throw SemanticError(oss.str());
}

void CheckAssignable::check(ASTProgram *p) {
  LOG_S(1) << "Checking assignability";
  CheckAssignable visitor;
  p->accept(&visitor);
}

//NEW//
void CheckAssignable::endVisit(ASTArrayIndexExpr *element) {
  LOG_S(1) << "Checking assignability of " << *element;

  if (isAssignable(element->getName()))
    return;

  std::ostringstream oss;
  oss << "Address of error on line " << element->getLine() << ": ";
  oss << *element->getName() << " not an l-value\n";
  throw SemanticError(oss.str());
}

void CheckAssignable::endVisit(ASTIncrementStmt *element) {
  LOG_S(1) << "Checking assignability of " << *element;

  if (isAssignable(element->getLeft()))
    return;

  std::ostringstream oss;
  oss << "Address of error on line " << element->getLine() << ": ";
  oss << *element->getLeft() << " not an l-value\n";
  throw SemanticError(oss.str());
}

void CheckAssignable::endVisit(ASTDecrementStmt *element) {
  LOG_S(1) << "Checking assignability of " << *element;

  if (isAssignable(element->getLeft()))
    return;

  std::ostringstream oss;
  oss << "Address of error on line " << element->getLine() << ": ";
  oss << *element->getLeft() << " not an l-value\n";
  throw SemanticError(oss.str());
}

void CheckAssignable::endVisit(ASTForStmt *element) {
  LOG_S(1) << "Checking assignability of " << *element;

  if (isAssignable(element->getItem()))
    return;

  std::ostringstream oss;
  oss << "Address of error on line " << element->getLine() << ": ";
  oss << *element->getItem() << " not an l-value\n";
  throw SemanticError(oss.str());
}

void CheckAssignable::endVisit(ASTForRangeStmt *element) {
  LOG_S(1) << "Checking assignability of " << *element;

  if (isAssignable(element->getIterator()))
    return;

  std::ostringstream oss;
  oss << "Address of error on line " << element->getLine() << ": ";
  oss << *element->getIterator() << " not an l-value\n";
  throw SemanticError(oss.str());
}