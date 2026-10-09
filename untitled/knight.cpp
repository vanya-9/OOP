#include "knight.h"
#include "board.h"

Knight::Knight(Color color, Coordinates coordinates) : Piece(color, coordinates, "Knight") {};

std::vector<Coordinates> Knight::validator(Board* board, bool filtr) {
    std::vector<Coordinates> possible_moves;
    Color enemy_color = (GetColor() == WHITE) ? BLACK : WHITE;
    Coordinates current_pos = GetCoordinates();

    for (const auto& move : knight_moves) {
        int new_x = current_pos.x + move.second;
        int new_y = current_pos.y + move.first;
        Coordinates new_pos = {new_y, new_x};

        if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
            std::shared_ptr<Piece> piece = board->GetPiece(new_x, new_y);

            if (piece == nullptr || piece->GetColor() == enemy_color) {
                possible_moves.push_back(new_pos);
            }
        }
    }


    if (filtr) {
        std::vector<Coordinates> filtr_moves;
        board->FiltrMoves(possible_moves, filtr_moves, shared_from_this(), enemy_color);
        return filtr_moves;
    }

    return possible_moves;
}
