#include "TipArray.h"
#include "TipTypeVisitor.h"
TipArray::TipArray() 
    : TipCons(std::vector<std::shared_ptr<TipType>>{}), arr_of(false), empty(true){}

TipArray::TipArray(std::vector<std::shared_ptr<TipType>> inits)
    : TipCons(inits) {arr_of = false, empty = false;}

TipArray::TipArray(std::shared_ptr<TipType> expr1, std::shared_ptr<TipType> expr2)
    : TipCons(combine(expr1, expr2)) {arr_of = true, empty = false;}

std::vector<std::shared_ptr<TipType>>
TipArray::combine(std::shared_ptr<TipType> expr1, std::shared_ptr<TipType> expr2) {
                    std::vector<std::shared_ptr<TipType>> combined;
    combined.push_back(std::move(expr1));
    combined.push_back(std::move(expr2));
    return combined;
}

bool TipArray::operator==(const TipType &other) const {
    // All elements in the comparing arrays should be the same type e.g. [1, 1, 1] == [1, 1, 1, 1, 1]
    auto otherTipArray = dynamic_cast<const TipArray *>(&other);
    if (!otherTipArray) {
        return false;
        }
    
        // Checks that the if either is empty than the other one is fine
    if (otherTipArray->empty){
        if (!empty){
            return false;
        }
    }

    if (empty){
        if (!otherTipArray->empty){
            return false;
        }
    }
    
    // both arrays are "of" arrays
    else if (arr_of && otherTipArray->arr_of){ 
        if (*(arguments.at(1)) != *(otherTipArray->arguments.at(1))) {
            return false;
        }
    }

    // initial array is "of" 
    else if (arr_of){
        if (*(arguments.at(1)) != *(otherTipArray->arguments.at(0))){
            return false;
        }
    }

    // other array is "of" 
    else if (otherTipArray->arr_of){
        if (*(arguments.at(0)) != *(otherTipArray->arguments.at(1))){
            return false;
            }
        // if 0 of and not empty
        if (arguments.size() == 0 && otherTipArray->arguments.at(0) != 0) {
            return false;
            }
        }

    // both arrays are default
    else{
        for (int i = 0; i < otherTipArray->arity(); i++) {
            if (*(arguments.at(0)) != *(otherTipArray->arguments.at(i))) {
                return false;
                }
            }
    }
    return true;
}

bool TipArray::operator!=(const TipType &other) const {
  return !(*this == other);
}


std::ostream &TipArray::print(std::ostream &out) const {
    if (arr_of) {
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
    for (auto a : arguments) {
      a->accept(visitor);
    }
  }
  visitor->endVisit(this);
}
