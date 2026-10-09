#include "king.h"
#include "board.h"
#include <QDebug>

King::King(Color color, Coordinates coordinates)
    : Piece(color, coordinates, "King") {
    is_king = true;
}

void King::CastlingSwap(Board *board, std::vector<Coordinates>& possible_moves){
    Coordinates short_castling_coordinates = {0, 1};
    short_castling_coordinates.y = GetColor() == WHITE ? 0 : 7;
    Color friendly_color = GetColor() == WHITE ? WHITE : BLACK;
    if(this->first_move == true && !IsAttack(shared_from_this(), this->GetCoordinates(), this->GetCoordinates(), board) &&
        !IsAttack(shared_from_this(), this->GetCoordinates(), short_castling_coordinates, board) &&
        (short_castling_coordinates.y == 7  || short_castling_coordinates.y == 0) &&
        short_castling_coordinates.x - 1 >= 0 &&  GetColor() == friendly_color &&
        board->GetPiece(short_castling_coordinates.x, short_castling_coordinates.y) == nullptr &&
        board->GetPiece(short_castling_coordinates.x + 1, short_castling_coordinates.y) == nullptr &&
        board->GetPiece(short_castling_coordinates.x - 1, short_castling_coordinates.y) != nullptr &&
        board->GetPiece(short_castling_coordinates.x - 1, short_castling_coordinates.y)->GetName() == "Rook" &&
        board->GetPiece(short_castling_coordinates.x - 1, short_castling_coordinates.y)->GetColor() == friendly_color){
        castling_black = (GetColor() == WHITE) ? false : true;
        castling_white = (GetColor() == WHITE) ? true : false;


        Coordinates king_new_coords = { short_castling_coordinates.y, short_castling_coordinates.x};
        possible_moves.push_back(king_new_coords);
    }
    Coordinates long_castling_coordinates = {7, 5};
    long_castling_coordinates.y = GetColor() == WHITE ? 0 : 7;
    if(this->first_move == true && !IsAttack(shared_from_this(), this->GetCoordinates(), this->GetCoordinates(), board) &&//двигаю короля на его координаты, смотря что он не под атакой
        !IsAttack(shared_from_this(), this->GetCoordinates(), long_castling_coordinates, board) &&
        (long_castling_coordinates.y == 7  || long_castling_coordinates.y == 0) &&
        long_castling_coordinates.x + 2 <= 7  && long_castling_coordinates.y <= 7 &&
        GetColor() == friendly_color &&
        board->GetPiece(long_castling_coordinates.x, long_castling_coordinates.y) == nullptr &&
        board->GetPiece(long_castling_coordinates.x + 1, long_castling_coordinates.y) == nullptr &&
        board->GetPiece(long_castling_coordinates.x - 1, long_castling_coordinates.y) == nullptr &&
        board->GetPiece(long_castling_coordinates.x + 2, long_castling_coordinates.y) != nullptr &&
        board->GetPiece(long_castling_coordinates.x + 2, long_castling_coordinates.y)->GetName() == "Rook" &&
        board->GetPiece(long_castling_coordinates.x + 2, long_castling_coordinates.y)->GetColor() == friendly_color){
        castling_black = (GetColor() == WHITE) ? false : true;
        castling_white = (GetColor() == WHITE) ? true : false;
        Coordinates king_new_coords = { long_castling_coordinates.y, long_castling_coordinates.x};
        possible_moves.push_back(king_new_coords);
    }
}

std::vector<Coordinates> King::validator(Board* board, bool filtr) {
    std::vector<Coordinates> possible_moves;
    Coordinates current_pos = GetCoordinates();
    Color enemy_color = (GetColor() == WHITE) ? BLACK : WHITE;

    for (const auto& dir : directions) {
        int dx = dir.first;
        int dy = dir.second;
        int new_x = current_pos.x + dx;
        int new_y = current_pos.y + dy;
        Coordinates new_coordinates = {new_y, new_x};

        if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
            std::shared_ptr<Piece> piece = board->GetPiece(new_x, new_y);

            if ((piece == nullptr || (piece->GetColor() == enemy_color && !piece->is_king)) &&
                !IsAttack(shared_from_this(), current_pos, new_coordinates, board)) {
                possible_moves.push_back(new_coordinates);
            }
        }
    }
    castling_black = false;
    castling_white = false; //при других вызовах валидатора тут может обновиться значение рокировки,
    //однако если мы не срокируемся, оно всегда будет трушным, что может привести к  mistakes
    //например в валидатор не добавим возможность, а она будет(в случае ошибок),
    //поэтому надо обновлять на false
    CastlingSwap(board, possible_moves);
    return possible_moves;
}

bool King::IsAttack(std::shared_ptr<Piece> piece, Coordinates piece_coordinates, Coordinates coordinates_to, Board* board){
    Color enemy_color = piece->GetColor() == WHITE ? BLACK : WHITE;
    std::shared_ptr<Piece> enemy_king = board->GetNeededKing(board, enemy_color);
    std::shared_ptr<Piece> our_king = board->GetNeededKing(board, piece->GetColor());

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
    board->ContentTmpChange(coordinates_to, true, piece);
    board->ContentTmpChange(piece_coordinates, false);

    std::vector<Coordinates> enemy_movies;
    for(int x = 0; x < board_size; x++){
        for(int y = 0; y < board_size; y++){

            if(board->GetPiece(x,y) !=nullptr && board->GetPiece(x,y)->GetName()!= "King"
                && board->GetPiece(x,y)->GetColor() == enemy_color)
            {
                enemy_movies = board->GetPiece(x,y)->validator(board, false);
                for(auto& move : enemy_movies){
                    if(move.x == coordinates_to.x &&
                        move.y == coordinates_to.y){
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
