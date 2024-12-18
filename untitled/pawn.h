#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
const int PAWN = 1;
class Pawn : public Piece
{
private:
    bool update_figure_ = false;

public:
    Pawn(Color color, Coordinates coordinates) : Piece(color, coordinates, "Pawn")
        {};

    virtual std::vector<Coordinates> validator(Board* board, bool filtr = true) override;

    void SetUpdate();

    bool GetUpdate();

    std::vector<Coordinates> AllValidator(Board* board);



};

#endif // PAWN_H
