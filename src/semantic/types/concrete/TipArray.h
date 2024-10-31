// #pragma once

// #include "TipCons.h"
// #include "TipType.h"
// #include <ostream>
// #include <string>
// #include <vector>

// /*!
//  * \class TipRecord
//  *
//  * \brief A proper type representing an array
//  */
// class TipArray : public TipCons {
// public:
//   TipArray() = delete;
//   TipArray(std::vector<std::shared_ptr<TipType>> inits);

//   std::vector<std::shared_ptr<TipType>> &getInits();
//   bool operator==(const TipType &other) const override;
//   bool operator!=(const TipType &other) const override;

//   void accept(TipTypeVisitor *visitor) override;

// protected:
//   std::ostream &print(std::ostream &out) const override;
// };