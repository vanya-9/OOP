#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
const int BISHOP = 4;
class Bishop : public Piece
{
public:
    Bishop(Color color, Coordinates coordinates);

    virtual std::vector<Coordinates> validator(Board* board) override;
};

#endif // BISHOP_H
