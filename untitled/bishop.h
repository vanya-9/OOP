#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
const int BISHOP = 4;
class Bishop : public Piece {

    std::vector<std::pair<int, int>> directions = {
        {-1, +1},
        {+1, -1},
        {+1, +1},
        {-1, -1}
    };

 public:
  Bishop(Color color, Coordinates coordinates);

  virtual std::vector<Coordinates> validator(Board* board, bool filtr = true) override;
};

#endif
