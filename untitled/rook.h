#ifndef ROOK_H
#define ROOK_H
#include "piece.h"
const int ROOK = 2;
class Rook : public Piece {
  std::vector<std::pair<int, int>> directions =
    {
    {-1, 0},
    {+1, 0},
    {0, -1},
    {0, +1}
    };

 public:
  Rook(Color color, Coordinates coordinates);

  virtual std::vector<Coordinates> validator(Board* board, bool filtr = true) override;
};

#endif  // ROOK_H
