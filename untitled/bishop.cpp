#include "bishop.h"
#include "board.h"
Bishop::Bishop(Color color, Coordinates coordinates)
    : Piece(color, coordinates, "Bishop") {}

std::vector<Coordinates> Bishop::validator(Board* board, bool filtr) {
    Color enemy_color = (GetColor() == WHITE) ? BLACK : WHITE;
    std::vector<Coordinates> possible_moves = ValidateLineMoves(board, directions);

    if (filtr) {
        std::vector<Coordinates> filtr_moves;
        board->FiltrMoves(possible_moves, filtr_moves, shared_from_this(), enemy_color);
        return filtr_moves;
    }

    return possible_moves;
}
