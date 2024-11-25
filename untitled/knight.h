#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
const int KNIGHT = 3;
class Knight : public Piece
{
public:
    Knight(Color color, Coordinates coordinates);

    virtual std::vector<Coordinates> validator(Board* board) override;
};

#endif // KNIGHT_H
