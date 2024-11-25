#ifndef KING_H
#define KING_H
#include "piece.h"
const int KING = 6;
class King : public Piece
{
    bool is_attack_ = true;
public:
    King(Color color, Coordinates coordinates);
    virtual std::vector<Coordinates> validator(Board* board) override;
    bool IsAttack(Coordinates coordinates, Board* board, bool validator_rokirovka = false);
};

#endif // KING_H
