#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
const int QUEEN = 5;
class Queen : public Piece
{
public:
    Queen(Color color, Coordinates coordinates);

    virtual std::vector<Coordinates> validator(Board* board) override;
};

#endif // QUEEN_H
