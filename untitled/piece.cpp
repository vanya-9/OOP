#include "piece.h"
#include "board.h"

Color Piece::GetColor(){
    return this->color_;
}

Coordinates Piece::GetCoordinates(){
    return coordinates_;
}

void Piece::SetCoordinates(Coordinates newCoordinates) {
    coordinates_ = newCoordinates;
}

std::string Piece::GetName(){
    return piece_name_;
}

std::vector<Coordinates> Piece::ValidateLineMoves(Board* board,std::vector<std::pair<int, int>>& directions) {
    std::vector<Coordinates> possible_moves;
    Coordinates current_pos = GetCoordinates();
    Color enemy_color = GetColor() == WHITE ? BLACK : WHITE;

    for (const auto& dir : directions) {
        int dx = dir.first;
        int dy = dir.second;

        for (int k = 1; ; ++k) {
            int new_x = current_pos.x + dx * k;
            int new_y = current_pos.y + dy * k;

            if (new_x < 0 || new_x >= 8 || new_y < 0 || new_y >= 8) {
                break;
            }

            std::shared_ptr<Piece> piece = board->GetPiece(new_x, new_y);

            if (piece == nullptr) {
                possible_moves.push_back({new_y, new_x});
            } else {
                if (piece->GetColor() == enemy_color) {
                    possible_moves.push_back({new_y, new_x});
                }
                break;
            }
        }
    }

    return possible_moves;
}
