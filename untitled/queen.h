#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
const int QUEEN = 5;
class Queen : public Piece
{
    std::vector<std::pair<int, int>> directions = {
    {-1, 0},
    {+1, 0},
    {0, -1},
    {0, +1},
    {-1, +1},
    {+1, -1},
    {+1, +1},
    {-1, -1}
    };
    
public:
    Queen(Color color, Coordinates coordinates);

    virtual std::vector<Coordinates> validator(Board* board, bool filtr = true) override;
};

#endif // QUEEN_H
