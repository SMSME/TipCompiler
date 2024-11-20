#include "TipArray.h"
#include "TipTypeVisitor.h"



TipArray::TipArray(std::shared_ptr<TipType> elementType, bool isEmptyInit)
    : TipCons({std::move(elementType)}), isEmpty(isEmptyInit) {}

// std::vector<std::shared_ptr<TipType>>
// TipArray::combine(std::shared_ptr<TipType> expr1, std::shared_ptr<TipType> expr2) {
//     std::vector<std::shared_ptr<TipType>> combined;
//     combined.push_back(expr1);
//     combined.push_back(expr2);
//     return combined;
// }

bool TipArray::operator==(const TipType &other) const {
    auto otherTipArray = dynamic_cast<const TipArray *>(&other);
    if (!otherTipArray) {
        return false;
    }

    // Either empty is true 
    if ( isEmpty || otherTipArray->isEmpty) {
        return true;
    }

    // Array contains one element which is its type, check that its the same  {
    if (*(arguments.at(0)) != *(otherTipArray->arguments.at(0))) {
        return false;
    }

    return true;
}


bool TipArray::operator!=(const TipType &other) const {
  return !(*this == other);
}


std::ostream &TipArray::print(std::ostream &out) const {
    if (!isEmpty) {
        out << "[";
        out << *(arguments.at(0));
        out << "]";
        return out;
    }
    else{
        out << "[]";
        return out;
        }
}

std::vector<std::shared_ptr<TipType>> &TipArray::getInits() {
  return arguments;
}

void TipArray::accept(TipTypeVisitor *visitor) {
  if (visitor->visit(this)) {
    for (auto &a : arguments) {
      a->accept(visitor);
    }
  }
  visitor->endVisit(this);
}
