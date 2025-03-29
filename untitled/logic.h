#ifndef LOGIC_H
#define LOGIC_H
#include "string"
const int board_size = 8;
extern int turn_to_walk;
const int cell_size = /*64*/ 100;
extern bool castling;
extern bool castling_black;
extern bool castling_white;

enum Color { WHITE, BLACK };

typedef struct {
  int y;
  int x;
} Coordinates;

class logic {
 public:
  logic();
};

#endif  // LOGIC_H
