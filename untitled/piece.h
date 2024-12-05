#ifndef PIECE_H
#define PIECE_H
#include "logic.h"
//#include "string"
#include "vector"

class Board;

class Piece
{
    Color color_;
    Coordinates coordinates_;
    std::string piece_name_;
public:
    Piece(Color color, Coordinates coordinates, std::string piece_name) : color_(color),
        coordinates_(coordinates), piece_name_(piece_name)
        {};

    virtual ~Piece() {};

    Color GetColor();

    virtual std::vector<Coordinates> validator(Board* board, bool filtr = true) = 0;

    Coordinates GetCoordinates();

    void SetCoordinates(Coordinates newCoordinates);

    bool first_move = true;

    std::string GetName();

    bool is_king = false;

};

#endif // PIECE_H
