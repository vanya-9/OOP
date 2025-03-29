#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H
#include <map>
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

#include <functional>
#include <map>
#include <memory>

template <
    typename AbstractProduct,
    typename IdentifierType,
    typename ProductCreator = std::function<std::shared_ptr<AbstractProduct>(Color, Coordinates)>
    >
class Factory {
public:
    bool Register(const IdentifierType& id, ProductCreator creator) {
        return creators_.emplace(id, creator).second;
    }

    bool Unregister(const IdentifierType& id) {
        return creators_.erase(id) == 1;
    }

    std::shared_ptr<AbstractProduct> CreateObject(const IdentifierType& id, Color color, Coordinates coordinates) const {
        auto it = creators_.find(id);
        if (it != creators_.end()) {
            return (it->second)(color, coordinates);
        }
        return nullptr;
    }

private:
    std::map<IdentifierType, ProductCreator> creators_;
};

#endif  // PIECEFACTORY_H
