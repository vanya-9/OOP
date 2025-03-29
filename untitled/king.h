#ifndef KING_H
#define KING_H
#include "piece.h"
const int KING = 6;
class King : public Piece
{
    bool is_attack_ = true;

    std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, +1},
        {0, -1}, {0, +1},
        {+1, -1}, {+1, 0}, {+1, +1}
    };
public:
    King(Color color, Coordinates coordinates);
    virtual std::vector<Coordinates> validator(Board* board, bool filtr = true) override;
    bool IsAttack(std::shared_ptr<Piece> piece, Coordinates piece_coordinates, Coordinates coordinates_to, Board* board);
    void CastlingSwap(Board* board, std::vector<Coordinates>& possible_moves);
};

#endif // KING_H
