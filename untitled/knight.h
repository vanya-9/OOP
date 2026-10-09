#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"
const int KNIGHT = 3;
class Knight : public Piece
{
    std::vector<std::pair<int, int>> knight_moves = {
    {+2, +1},
    {+2, -1},
    {-2, +1},
    {-2, -1},
    {+1, +2},
    {+1, -2},
    {-1, +2},
    {-1, -2}
    };

public:
    Knight(Color color, Coordinates coordinates);

    virtual std::vector<Coordinates> validator(Board* board, bool filtr = true) override;
};

#endif // KNIGHT_H
