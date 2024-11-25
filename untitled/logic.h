#ifndef LOGIC_H
#define LOGIC_H
#include "string"
const int board_size = 8;
extern int turn_to_walk;
const int cell_size = 64;
extern bool rokirovka;

enum Color { WHITE, BLACK };



typedef struct {
    int y;
    int x;
} Coordinates;

class logic
{
public:
    logic();
};

#endif // LOGIC_H
