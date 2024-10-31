// #include "TipArray.h"
// #include "TipTypeVisitor.h"

// TipArray::TipArray(std::vector<std::shared_ptr<TipType>> inits)
//     : TipCons(inits) {}

// bool TipArray::operator==(const TipType &other) const {
//   auto otherTipArray = dynamic_cast<const TipArray *>(&other);
//   if (!otherTipArray) {
//     return false;
//   }

//   return true;
// }


// bool TipArray::operator!=(const TipType &other) const {
//   return !(*this == other);
// }


// std::ostream &TipArray::print(std::ostream &out) const {
//   out << "[";
//   bool first = true;
//   int i = 0;
//   for (auto &init : arguments) {
//     if (first) {
//       out << *init;
//       first = false;
//       continue;
//     }
//     out << "," << *init;
//   }
//   out << "]";
//   return out;
// }

// std::vector<std::shared_ptr<TipType>> &TipArray::getInits() {
//   return arguments;
// }


// void TipArray::accept(TipTypeVisitor *visitor) {
//   if (visitor->visit(this)) {
//     for (auto a : arguments) {
//       a->accept(visitor);
//     }
//   }
//   visitor->endVisit(this);
// }
