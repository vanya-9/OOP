#ifndef ROOK_H
#define ROOK_H
#include "piece.h"
const int ROOK = 2;
class Rook : public Piece
{
public:
    Rook(Color color, Coordinates coordinates);

    virtual std::vector<Coordinates> validator(Board* board, bool filtr = true) override;
};

#endif // ROOK_H
