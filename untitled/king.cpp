#include "king.h"
#include "board.h"
#include <QDebug>
King::King(Color color, Coordinates coordinates)
    : Piece(color, coordinates, "King") {
    is_king = true;
}

std::vector<Coordinates> King::validator(Board* board) {
    std::vector<Coordinates> possible_moves;
    Color enemy_color = (GetColor() == WHITE) ? BLACK : WHITE;

    Coordinates forward_up = {GetCoordinates().y - 1, GetCoordinates().x};


    if (forward_up.y >= 0 && (board->GetPiece(forward_up.x, forward_up.y) == nullptr ||
         (board->GetPiece(forward_up.x, forward_up.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_up.x, forward_up.y)->is_king)) &&
        !IsAttack(forward_up, board)) {
        possible_moves.push_back(forward_up);
    }

    Coordinates forward_up_left = {GetCoordinates().y - 1, GetCoordinates().x - 1};
    if (forward_up_left.y >= 0 && forward_up_left.x >= 0 &&
        (board->GetPiece(forward_up_left.x, forward_up_left.y) == nullptr ||
        (board->GetPiece(forward_up_left.x, forward_up_left.y)->GetColor() == enemy_color &&
        !board->GetPiece(forward_up_left.x, forward_up_left.y)->is_king)) &&
        !IsAttack(forward_up_left, board)) {
        possible_moves.push_back(forward_up_left);
    }

    Coordinates forward_up_right = {GetCoordinates().y - 1, GetCoordinates().x + 1};
    if (forward_up_right.y >= 0 && forward_up_right.x <= 7 &&
        (board->GetPiece(forward_up_right.x, forward_up_right.y) == nullptr ||
         (board->GetPiece(forward_up_right.x, forward_up_right.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_up_right.x, forward_up_right.y)->is_king)) &&
        !IsAttack(forward_up_right, board)) {
        possible_moves.push_back(forward_up_right);
    }

    Coordinates forward_right = {GetCoordinates().y, GetCoordinates().x + 1};


    if (forward_right.y >= 0 && forward_right.x <= 7 &&
        (board->GetPiece(forward_right.x, forward_right.y) == nullptr ||
         (board->GetPiece(forward_right.x, forward_right.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_right.x, forward_right.y)->is_king)) &&
        !IsAttack(forward_right, board)) {
        possible_moves.push_back(forward_right);
    }

    Coordinates forward_left = {GetCoordinates().y, GetCoordinates().x - 1};


    if (forward_left.y >= 0 && forward_left.x >= 0 &&
        (board->GetPiece(forward_left.x, forward_left.y) == nullptr ||
         (board->GetPiece(forward_left.x, forward_left.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_left.x, forward_left.y)->is_king)) &&
        !IsAttack(forward_left, board)) {
        possible_moves.push_back(forward_left);
    }
    Coordinates forward_dawn = {GetCoordinates().y + 1, GetCoordinates().x};

    if (forward_dawn.y <= 7 && forward_dawn.x >= 0 &&
        (board->GetPiece(forward_dawn.x, forward_dawn.y) == nullptr ||
         (board->GetPiece(forward_dawn.x, forward_dawn.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_dawn.x, forward_dawn.y)->is_king)) &&
        !IsAttack(forward_dawn, board)) {
        possible_moves.push_back(forward_dawn);
    }

    Coordinates forward_dawn_left = {GetCoordinates().y + 1, GetCoordinates().x - 1};

    if (forward_dawn_left.y <= 7 && forward_dawn_left.x >= 0 &&
        (board->GetPiece(forward_dawn_left.x, forward_dawn_left.y) == nullptr ||
         (board->GetPiece(forward_dawn_left.x, forward_dawn_left.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_dawn_left.x, forward_dawn_left.y)->is_king)) &&
        !IsAttack(forward_dawn_left, board)) {
        possible_moves.push_back(forward_dawn_left);
    }

    Coordinates forward_dawn_right = {GetCoordinates().y + 1, GetCoordinates().x + 1};

    if (forward_dawn_right.y <= 7 && forward_dawn_right.x <= 7 &&
        (board->GetPiece(forward_dawn_right.x, forward_dawn_right.y) == nullptr ||
         (board->GetPiece(forward_dawn_right.x, forward_dawn_right.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_dawn_right.x, forward_dawn_right.y)->is_king)) &&
        !IsAttack(forward_dawn_right, board)) {
        possible_moves.push_back(forward_dawn_right);
    }
    rokirovka = false; //при других вызовах валидатора тут может обновиться значение рокировки,
    //однако если мы не срокируемся, оно всегда будет трушным, что может привести к  mistakes
    //например в валидатор не добавим возможность, а она будет(в случае ошибок),
    //поэтому надо обновлять на false
    Coordinates short_rokirovka_coordinates = {0, 6};
    short_rokirovka_coordinates.y = GetColor() == WHITE ? 0 : 7;
    Color friendly_color = GetColor() == WHITE ? WHITE : BLACK;
    if(this->first_move == true && !IsAttack(this->GetCoordinates(), board, true) &&
        (short_rokirovka_coordinates.y == 7  || short_rokirovka_coordinates.y == 0) &&
        short_rokirovka_coordinates.x - 1 >= 0 &&  GetColor() == friendly_color &&
        board->GetPiece(short_rokirovka_coordinates.x, short_rokirovka_coordinates.y) == nullptr &&
        board->GetPiece(short_rokirovka_coordinates.x - 1, short_rokirovka_coordinates.y) == nullptr &&
        board->GetPiece(short_rokirovka_coordinates.x + 1, short_rokirovka_coordinates.y) != nullptr &&
        board->GetPiece(short_rokirovka_coordinates.x + 1, short_rokirovka_coordinates.y)->GetName() == "Rook" &&
        board->GetPiece(short_rokirovka_coordinates.x + 1, short_rokirovka_coordinates.y)->GetColor() == friendly_color){
        rokirovka = true;



        Coordinates king_new_coords = { short_rokirovka_coordinates.y, short_rokirovka_coordinates.x};
        possible_moves.push_back(king_new_coords);
    }
    Coordinates long_rokirovka_coordinates = {7, 2};
    long_rokirovka_coordinates.y = GetColor() == WHITE ? 0 : 7;
    if(this->first_move == true && !IsAttack(this->GetCoordinates(), board, true) &&
        (long_rokirovka_coordinates.y == 7  || long_rokirovka_coordinates.y == 0) &&
        long_rokirovka_coordinates.x - 2 >= 0 && long_rokirovka_coordinates.x + 3 <= 7 &&long_rokirovka_coordinates.y <= 7 &&
        GetColor() == friendly_color &&
        board->GetPiece(long_rokirovka_coordinates.x, long_rokirovka_coordinates.y) == nullptr &&
        board->GetPiece(long_rokirovka_coordinates.x + 1, long_rokirovka_coordinates.y) == nullptr &&
        board->GetPiece(long_rokirovka_coordinates.x - 1, long_rokirovka_coordinates.y) == nullptr &&
        board->GetPiece(long_rokirovka_coordinates.x - 2, long_rokirovka_coordinates.y) != nullptr &&
        board->GetPiece(long_rokirovka_coordinates.x - 2, long_rokirovka_coordinates.y)->GetName() == "Rook" &&
        board->GetPiece(long_rokirovka_coordinates.x - 2, long_rokirovka_coordinates.y)->GetColor() == friendly_color){
        rokirovka = true;
        Coordinates king_new_coords = { long_rokirovka_coordinates.y, long_rokirovka_coordinates.x};
        possible_moves.push_back(king_new_coords);
    }
    return possible_moves;
}


bool King::IsAttack(Coordinates coordinates, Board* board, bool validator_rokirovka) {
    Color enemy_color = (GetColor() == WHITE) ? BLACK : WHITE;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Пропускаем саму клетку
            int nx = coordinates.x + dx;
            int ny = coordinates.y + dy;
            if (nx >= 0 && nx < board_size && ny >= 0 && ny < board_size) {
                Piece* neighbor_piece = board->GetPiece(nx, ny);

                // Если соседняя фигура — это вражеский король, клетка под атакой
                if (neighbor_piece != nullptr && neighbor_piece->GetColor() == enemy_color && neighbor_piece->is_king) {
                    return true;
                }
            }
        }
    }
    // Проверка других фигур
    for (int x = 0; x < board_size; x++) {
        for (int y = 0; y < board_size; y++) {

            Piece* piece = board->GetPiece(x, y);
            if (piece != nullptr && piece->GetColor() == enemy_color && !piece->is_king) {
                std::vector<Coordinates> valid_moves;
                if(piece != nullptr && piece->GetName() == "Pawn"){
                    valid_moves = dynamic_cast<Pawn*>(piece)->AllValidator(board);
                }
                else{
                    if(!validator_rokirovka){
                        auto* tmp = board->GetPiece(coordinates.x, coordinates.y);
                        board->ContentTmpChange(coordinates, false);
                        valid_moves = piece->validator(board);
                        board->ContentTmpChange(coordinates, true, tmp);
                }
                else{
                        valid_moves = piece->validator(board);}}
                for (const auto& move : valid_moves) {
                    if (move.x == coordinates.x && move.y == coordinates.y) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
