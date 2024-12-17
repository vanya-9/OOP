#include "rook.h"
#include "board.h"

Rook::Rook(Color color, Coordinates coordinates) : Piece(color, coordinates, "Rook") {};

std::vector<Coordinates> Rook::validator(Board* board, bool filtr){
    std::vector<Coordinates> possible_moves;
    Color enemy_color = GetColor() == WHITE ? BLACK : WHITE;
    Color not_enemy_color = GetColor() == WHITE ? WHITE : BLACK;

    {
        for(int y = GetCoordinates().y + 1; y <= 7; y++){
            if(board->GetPiece(GetCoordinates().x, y) == nullptr){
            Coordinates forward = {y,GetCoordinates().x};
            possible_moves.push_back(forward);
            }
            else if((board->GetPiece(GetCoordinates().x, y)) != nullptr &&
                    (board->GetPiece(GetCoordinates().x, y)->GetColor() == enemy_color ||
                    board->GetPiece(GetCoordinates().x, y)->GetColor() == not_enemy_color)){
                if(board->GetPiece(GetCoordinates().x, y)->GetColor() == enemy_color){
                Coordinates forward = {y,GetCoordinates().x};
                possible_moves.push_back(forward);
                }
                break;
            }
        }
        for(int y = GetCoordinates().y - 1; y >= 0; y--){
            if(board->GetPiece(GetCoordinates().x, y) == nullptr){
                Coordinates forward = {y,GetCoordinates().x};
                possible_moves.push_back(forward);
            }
            else if((board->GetPiece(GetCoordinates().x, y)) != nullptr &&
                     (board->GetPiece(GetCoordinates().x, y)->GetColor() == enemy_color ||
                      board->GetPiece(GetCoordinates().x, y)->GetColor() == not_enemy_color)){
                if(board->GetPiece(GetCoordinates().x, y)->GetColor() == enemy_color){
                    Coordinates forward = {y,GetCoordinates().x};
                    possible_moves.push_back(forward);
                }
                break;
            }
        }

        for(int x = GetCoordinates().x + 1; x <= 7; x++){
            if(board->GetPiece(x, GetCoordinates().y) == nullptr){
                Coordinates forward = {GetCoordinates().y,x};
                possible_moves.push_back(forward);
            }
            else if((board->GetPiece(x, GetCoordinates().y)) != nullptr &&
                     (board->GetPiece(x, GetCoordinates().y)->GetColor() == enemy_color ||
                      board->GetPiece(x, GetCoordinates().y)->GetColor() == not_enemy_color)){
                if(board->GetPiece(x, GetCoordinates().y)->GetColor() == enemy_color){
                    Coordinates forward = {GetCoordinates().y,x};
                    possible_moves.push_back(forward);
                }
                break;
            }
        }

        for(int x = GetCoordinates().x - 1; x >= 0; x--){
            if(board->GetPiece(x, GetCoordinates().y) == nullptr){
                Coordinates forward = {GetCoordinates().y,x};
                possible_moves.push_back(forward);
            }
            else if((board->GetPiece(x, GetCoordinates().y)) != nullptr &&
                     (board->GetPiece(x, GetCoordinates().y)->GetColor() == enemy_color ||
                      board->GetPiece(x, GetCoordinates().y)->GetColor() == not_enemy_color)){
                if(board->GetPiece(x, GetCoordinates().y)->GetColor() == enemy_color){
                    Coordinates forward = {GetCoordinates().y,x};
                    possible_moves.push_back(forward);
                }
                break;
            }
        }
    }
    std::vector<Coordinates> filtr_moves;
    if(filtr){
        board->FiltrMovies(possible_moves,filtr_moves, shared_from_this(), enemy_color);
        return filtr_moves;

    }
    return possible_moves;
}
