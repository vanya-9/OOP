#include "king.h"
#include "board.h"
#include <QDebug>

std::vector<Coordinates> King::getKingRawMoves() {
    auto moves = std::vector<Coordinates>();
    Coordinates coordinates_king;

    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            if (dx == 0 && dy == 0) continue;
            coordinates_king = {GetCoordinates().y + dy, GetCoordinates().x + dx};
            moves.push_back(coordinates_king);

        }
    }
    return moves;
}

King::King(Color color, Coordinates coordinates)
    : Piece(color, coordinates, "King") {
    is_king = true;
}

std::vector<Coordinates> King::validator(Board* board, bool filtr) {
    std::vector<Coordinates> possible_moves;
    Color enemy_color = (GetColor() == WHITE) ? BLACK : WHITE;

    Coordinates forward_up = {GetCoordinates().y - 1, GetCoordinates().x};


    if (forward_up.y >= 0 && (board->GetPiece(forward_up.x, forward_up.y) == nullptr ||
                              (board->GetPiece(forward_up.x, forward_up.y)->GetColor() == enemy_color &&
                               !board->GetPiece(forward_up.x, forward_up.y)->is_king)) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), forward_up, board)) {
        possible_moves.push_back(forward_up);
    }

    Coordinates forward_up_left = {GetCoordinates().y - 1, GetCoordinates().x - 1};
    if (forward_up_left.y >= 0 && forward_up_left.x >= 0 &&
        (board->GetPiece(forward_up_left.x, forward_up_left.y) == nullptr ||
         (board->GetPiece(forward_up_left.x, forward_up_left.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_up_left.x, forward_up_left.y)->is_king)) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), forward_up_left, board)) {
        possible_moves.push_back(forward_up_left);
    }

    Coordinates forward_up_right = {GetCoordinates().y - 1, GetCoordinates().x + 1};
    if (forward_up_right.y >= 0 && forward_up_right.x <= 7 &&
        (board->GetPiece(forward_up_right.x, forward_up_right.y) == nullptr ||
         (board->GetPiece(forward_up_right.x, forward_up_right.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_up_right.x, forward_up_right.y)->is_king)) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), forward_up_right, board)) {
        possible_moves.push_back(forward_up_right);
    }

    Coordinates forward_right = {GetCoordinates().y, GetCoordinates().x + 1};


    if (forward_right.y >= 0 && forward_right.x <= 7 &&
        (board->GetPiece(forward_right.x, forward_right.y) == nullptr ||
         (board->GetPiece(forward_right.x, forward_right.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_right.x, forward_right.y)->is_king)) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), forward_right, board)) {
        possible_moves.push_back(forward_right);
    }

    Coordinates forward_left = {GetCoordinates().y, GetCoordinates().x - 1};


    if (forward_left.y >= 0 && forward_left.x >= 0 &&
        (board->GetPiece(forward_left.x, forward_left.y) == nullptr ||
         (board->GetPiece(forward_left.x, forward_left.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_left.x, forward_left.y)->is_king)) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), forward_left, board)) {
        possible_moves.push_back(forward_left);
    }
    Coordinates forward_dawn = {GetCoordinates().y + 1, GetCoordinates().x};

    if (forward_dawn.y <= 7 && forward_dawn.x >= 0 &&
        (board->GetPiece(forward_dawn.x, forward_dawn.y) == nullptr ||
         (board->GetPiece(forward_dawn.x, forward_dawn.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_dawn.x, forward_dawn.y)->is_king)) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), forward_dawn, board)) {
        possible_moves.push_back(forward_dawn);
    }

    Coordinates forward_dawn_left = {GetCoordinates().y + 1, GetCoordinates().x - 1};

    if (forward_dawn_left.y <= 7 && forward_dawn_left.x >= 0 &&
        (board->GetPiece(forward_dawn_left.x, forward_dawn_left.y) == nullptr ||
         (board->GetPiece(forward_dawn_left.x, forward_dawn_left.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_dawn_left.x, forward_dawn_left.y)->is_king)) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), forward_dawn_left, board)) {
        possible_moves.push_back(forward_dawn_left);
    }

    Coordinates forward_dawn_right = {GetCoordinates().y + 1, GetCoordinates().x + 1};

    if (forward_dawn_right.y <= 7 && forward_dawn_right.x <= 7 &&
        (board->GetPiece(forward_dawn_right.x, forward_dawn_right.y) == nullptr ||
         (board->GetPiece(forward_dawn_right.x, forward_dawn_right.y)->GetColor() == enemy_color &&
          !board->GetPiece(forward_dawn_right.x, forward_dawn_right.y)->is_king)) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), forward_dawn_right, board)) {
        possible_moves.push_back(forward_dawn_right);
    }
    rokirovka = false; //при других вызовах валидатора тут может обновиться значение рокировки,
    //однако если мы не срокируемся, оно всегда будет трушным, что может привести к  mistakes
    //например в валидатор не добавим возможность, а она будет(в случае ошибок),
    //поэтому надо обновлять на false
    Coordinates short_rokirovka_coordinates = {0, 6};
    short_rokirovka_coordinates.y = GetColor() == WHITE ? 0 : 7;
    Color friendly_color = GetColor() == WHITE ? WHITE : BLACK;
    if(this->first_move == true && !IsAttack(shared_from_this(), this->GetCoordinates(), this->GetCoordinates(), board) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), short_rokirovka_coordinates, board) &&
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
    if(this->first_move == true && !IsAttack(shared_from_this(), this->GetCoordinates(), this->GetCoordinates(), board) &&//двигаю короля на его координаты, смотря что он не под атакой
        !IsAttack(shared_from_this(), this->GetCoordinates(), long_rokirovka_coordinates, board) &&
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

// !king->IsAttack(this, current_coords, move, board)
bool King::IsAttack(std::shared_ptr<Piece> piece, Coordinates piece_coordinates, Coordinates coordinates_to, Board* board){
    Color enemy_color = piece->GetColor() == WHITE ? BLACK : WHITE;
    std::shared_ptr<Piece> enemy_king;
    if(enemy_color == BLACK) {qDebug() << "WHITECRASH";}
    std::shared_ptr<Piece> our_king;
    for(int x = 0; x < board_size; x++){
        for(int y = 0; y < board_size; y++){
            if (board->GetPiece(x,y) !=nullptr && board->GetPiece(x,y)->GetName() == "King" &&
                board->GetPiece(x,y)->GetColor() == enemy_color){
                enemy_king = board->GetPiece(x,y);
            }
            if (board->GetPiece(x,y) !=nullptr && board->GetPiece(x,y)->GetName() == "King" &&
                board->GetPiece(x,y)->GetColor() != enemy_color){
                our_king = board->GetPiece(x,y);
            }
        }
    }
    for(int dx = -1; dx <= 1; dx++){
        for(int dy = -1; dy <= 1; dy++){
            if (dx == 0 && dy == 0) continue;
            int nx = enemy_king->GetCoordinates().x + dx;
            int ny = enemy_king->GetCoordinates().y + dy;
            if(nx == coordinates_to.x && ny == coordinates_to.y){
                return true;
            }
        }
    }



    //     //обработка всех кроме короля
    //     //проверим, что будет если мы переставим некую фигуру на координаты, например короля на какуюто позу
    //     //если он будет не под атакой то все четко, это нужно потому что может быть такая ситуация
    //     // что в ряд стоят белый король и две черных фигуры пешка и ферзь
    //     //тогда мы можем захавать пешку, потому что валидатор ферзя не даст нам хода на фигуру того же цвета
    //     //но по факту мы так сделать не можем
    //     //короля тут не получится обработать из-за цикла поэтому он будет обрабатываться выше отдельно



    auto tmp_piece = board->GetPiece(coordinates_to.x, coordinates_to.y);
    //Coordinates tmp_coordinates = board->GetPiece(coordinates_to.x, coordinates_to.y)->GetCoordinates();
    board->ContentTmpChange(coordinates_to, true, piece);// переставил коня
/*    if(piece->GetName() != "King" && piece_coordinates.x != coordinates_to.x &&
        piece_coordinates.y != coordinates_to.y)*/{
        board->ContentTmpChange(piece_coordinates, false); // удаляю коня с текущих
    }
    for(int x = 0; x < board_size; x++){
        for(int y = 0; y < board_size; y++){
            if (board->GetPiece(x,y) !=nullptr && board->GetPiece(x,y)->GetColor() != enemy_color &&
                board->GetPiece(x,y)->GetName() == "King"
                ){
                our_king = board->GetPiece(x,y); //поиск нашего короля происходит тут
                //потому что его могли передвинуть кодом выше
            }
        }
    }

    std::vector<Coordinates> enemy_movies;
    for(int x = 0; x < board_size; x++){
        for(int y = 0; y < board_size; y++){
            if(board->GetPiece(x,y) !=nullptr && board->GetPiece(x,y)->GetName()!= "King"
                && board->GetPiece(x,y)->GetColor() == enemy_color){
                enemy_movies = board->GetPiece(x,y)->validator(board, false);
                for(auto& move : enemy_movies){
                    if(move.x == our_king->GetCoordinates().x &&
                        move.y == our_king->GetCoordinates().y){
                        board->ContentTmpChange(coordinates_to, true, tmp_piece);
                        board->ContentTmpChange(piece_coordinates, true, piece);
                        return true;
                    }
                }
            }
        }
    }
    board->ContentTmpChange(coordinates_to, true, tmp_piece);
    board->ContentTmpChange(piece_coordinates, true, piece);
    return false;
}

