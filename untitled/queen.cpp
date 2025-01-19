#include "queen.h"
#include "board.h"
Queen::Queen(Color color, Coordinates coordinates)
    : Piece(color, coordinates, "Queen") {}

std::vector<Coordinates> Queen::validator(Board* board, bool filtr) {
    std::vector<Coordinates> possible_moves;
    Color enemy_color = (GetColor() == WHITE) ? BLACK : WHITE;
    Coordinates current_pos = GetCoordinates();

    std::vector<std::pair<int, int>> directions = {
        {-1, 0},
        {+1, 0},
        {0, -1},
        {0, +1}
    };

    for (const auto& dir : directions) {
        int dx = dir.first;
        int dy = dir.second;

        for (int k = 1; k <= 7; ++k) {
            int new_x = current_pos.x + dx * k;
            int new_y = current_pos.y + dy * k;

            if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
                std::shared_ptr<Piece> piece = board->GetPiece(new_x, new_y);

                if (piece == nullptr) {
                    possible_moves.push_back({new_y, new_x});
                } else {
                    if (piece->GetColor() == enemy_color) {
                        possible_moves.push_back({new_y, new_x});
                    }
                    break;
                }
            } else {
                break;
            }
        }
    }

    std::vector<std::pair<int, int>> directions_two = {
        {-1, +1},
        {+1, -1},
        {+1, +1},
        {-1, -1}
    };

    for (const auto& dir : directions_two) {
        int dx = dir.first;
        int dy = dir.second;
        int x = current_pos.x;
        int y = current_pos.y;

        for (int k = 1; k <= 7; ++k) {
            int new_x = x + dx * k;
            int new_y = y + dy * k;

            if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
                std::shared_ptr<Piece> piece = board->GetPiece(new_x, new_y);

                if (piece == nullptr) {
                    possible_moves.push_back({new_y, new_x});
                } else {
                    if (piece->GetColor() == enemy_color) {
                        possible_moves.push_back({new_y, new_x});
                    }
                    break;
                }
            } else {
                break;
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
