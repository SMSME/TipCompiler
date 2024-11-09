#include "TipArray.h"
#include "TipTypeVisitor.h"

TipArray::TipArray(std::vector<std::shared_ptr<TipType>> inits, bool arr_of_init)
    : TipCons(inits), array_of(arr_of_init), is_empty(false) {}

TipArray::TipArray(std::shared_ptr<TipType> expr1, std::shared_ptr<TipType> expr2, bool arr_of_init)
    : TipCons(combine(expr1, expr2)), array_of(arr_of_init), is_empty(false) {}

TipArray::TipArray()
    : TipCons(std::vector<std::shared_ptr<TipType>>{}) {
    array_of = false; is_empty = true;
}

bool TipArray::operator==(const TipType &other) const {
    auto otherTipArray = dynamic_cast<const TipArray *>(&other);
    if (!otherTipArray) {
        return false;
    }

    // If either array is empty, they must both be empty to be equal
    if (arguments.empty() != otherTipArray->arguments.empty()) {
        return false;
    }

    if (arguments.empty() && otherTipArray->arguments.empty()) {
        return true;
    }

    if (array_of != otherTipArray->array_of) { // Check array types when one is an array of
        if (array_of){
            for (auto arg: otherTipArray->arguments) {
                if (*(arguments.at(1)) != *(arg)){
                    return false;
                }}}
        else {
            for (auto arg: arguments) {
                if (*(arg) != *(otherTipArray->arguments.at(1))){
                    return false;
                }}}
    }

    else if (array_of && otherTipArray->array_of) {
        if (*(arguments.at(1)) != *(otherTipArray->arguments.at(1))) {
            return false;
        }
    }

    else if (*(arguments.at(0)) != *(otherTipArray->arguments.at(0))) {
        return false;
    }

    return true;
}


std::vector<std::shared_ptr<TipType>>
TipArray::combine(std::shared_ptr<TipType> expr1, std::shared_ptr<TipType> expr2) {
    std::vector<std::shared_ptr<TipType>> combined;
    combined.push_back(std::move(expr1));
    combined.push_back(std::move(expr2));
    return combined;
}

bool TipArray::operator!=(const TipType &other) const {
  return !(*this == other);
}


std::ostream &TipArray::print(std::ostream &out) const {
    if (array_of) {
        out << "[";
        out << *(arguments.at(0)) << " of " << *(arguments.at(1));
        out << "]";
        return out;
    }
    else{
        out << "[";
        bool first = true;
        for (auto &init : arguments) {
            if (first) {
                out << *init;
                first = false;
                continue;
            }
        out << "," << *init;
        }
        out << "]";
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
