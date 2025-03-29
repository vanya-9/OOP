#include "pawn.h"
#include "board.h"
#include <QDebug>
std::vector<Coordinates> Pawn::validator(Board* board, bool filtr) {
    std::vector<Coordinates> possible_moves;
    Color enemy_color = (GetColor() == WHITE) ? BLACK : WHITE;
    Coordinates current_pos = GetCoordinates();

    int direction = (GetColor() == WHITE) ? 1 : -1;

    Coordinates forward = {current_pos.y + direction, current_pos.x};
    Coordinates forward_two = {current_pos.y + 2 * direction, current_pos.x};
    Coordinates right_attack = {current_pos.y + direction, current_pos.x + 1};
    Coordinates left_attack = {current_pos.y + direction, current_pos.x - 1};

    if (forward.y >= 0 && forward.y < 8 && board->GetPiece(forward.x, forward.y) == nullptr) {
        possible_moves.push_back(forward);

        if (first_move && forward_two.y >= 0 && forward_two.y < 8 &&
            board->GetPiece(forward_two.x, forward_two.y) == nullptr) {
            possible_moves.push_back(forward_two);
        }
    }

    if (right_attack.x >= 0 && right_attack.x < 8 && right_attack.y >= 0 && right_attack.y < 8) {
        std::shared_ptr<Piece> piece = board->GetPiece(right_attack.x, right_attack.y);
        if (piece != nullptr && piece->GetColor() == enemy_color) {
            possible_moves.push_back(right_attack);
        }
    }

    if (left_attack.x >= 0 && left_attack.x < 8 && left_attack.y >= 0 && left_attack.y < 8) {
        std::shared_ptr<Piece> piece = board->GetPiece(left_attack.x, left_attack.y);
        if (piece != nullptr && piece->GetColor() == enemy_color) {
            possible_moves.push_back(left_attack);
        }
    }

    if (filtr) {
        std::vector<Coordinates> filtr_moves;
        board->FiltrMoves(possible_moves, filtr_moves, shared_from_this(), enemy_color);
        return filtr_moves;
    }

    return possible_moves;
}


void Pawn::SetUpdate(){
    update_figure_ = true;
}

bool Pawn::GetUpdate(){
    return update_figure_;
}






