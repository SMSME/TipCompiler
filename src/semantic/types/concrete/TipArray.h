#pragma once

#include "TipCons.h"
#include "TipType.h"
#include <ostream>
#include <string>
#include <vector>

/*!
 * \class TipArray
 *
 * \brief A proper type representing an array
 */
class TipArray : public TipCons {
public:
    bool isEmpty = false;

//     TipArray(std::vector<std::shared_ptr<TipType>> inits, bool arr_of_init);
    TipArray(std::shared_ptr<TipType> elementType, bool isEmptyInit);
    // TipArray();

    std::vector<std::shared_ptr<TipType>> &getInits();
    bool operator==(const TipType &other) const override;
    bool operator!=(const TipType &other) const override;

    void accept(TipTypeVisitor *visitor) override;

    protected:
    std::ostream &print(std::ostream &out) const override;

    private:
    std::vector<std::shared_ptr<TipType>>
    combine(std::shared_ptr<TipType> amt,
            std::shared_ptr<TipType> obj);
    };