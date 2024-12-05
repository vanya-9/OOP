#include "knight.h"
#include "board.h"

Knight::Knight(Color color, Coordinates coordinates) : Piece(color, coordinates, "Knight") {};

std::vector<Coordinates> Knight::validator(Board* board, bool filtr){
    std::vector<Coordinates> possible_moves;
    Color enemy_color = GetColor() == WHITE ? BLACK : WHITE;
    Coordinates down_right_forward = {GetCoordinates().y + 2, GetCoordinates().x + 1};
        if(down_right_forward.x <= 7 &&down_right_forward.y <= 7 &&
        ((board->GetPiece(down_right_forward.x,down_right_forward.y) == nullptr) ||(
        board->GetPiece(down_right_forward.x,down_right_forward.y) != nullptr &&
        board->GetPiece(down_right_forward.x,down_right_forward.y)->GetColor() == enemy_color))){
        possible_moves.push_back(down_right_forward);
    }
    Coordinates down_left_forward = {GetCoordinates().y + 2, GetCoordinates().x - 1};
    if(down_left_forward.x >= 0 &&down_left_forward.y <= 7 &&
        ((board->GetPiece(down_left_forward.x,down_left_forward.y) == nullptr) ||(
             board->GetPiece(down_left_forward.x,down_left_forward.y) != nullptr &&
             board->GetPiece(down_left_forward.x,down_left_forward.y)->GetColor() == enemy_color))){
        possible_moves.push_back(down_left_forward);
    }
    Coordinates up_right_forward = {GetCoordinates().y - 2, GetCoordinates().x + 1};
    if(up_right_forward.x <=7 && up_right_forward.y >= 0 &&
        ((board->GetPiece(up_right_forward.x,up_right_forward.y) == nullptr) ||(
             board->GetPiece(up_right_forward.x,up_right_forward.y) != nullptr &&
             board->GetPiece(up_right_forward.x,up_right_forward.y)->GetColor() == enemy_color))){
        possible_moves.push_back(up_right_forward);
    }

    Coordinates up_left_forward = {GetCoordinates().y - 2, GetCoordinates().x - 1};
    if(up_left_forward.x >= 0 && up_left_forward.y >= 0 &&
        ((board->GetPiece(up_left_forward.x,up_left_forward.y) == nullptr) ||(
             board->GetPiece(up_left_forward.x,up_left_forward.y) != nullptr &&
             board->GetPiece(up_left_forward.x,up_left_forward.y)->GetColor() == enemy_color))){
        possible_moves.push_back(up_left_forward);
    }
    Coordinates left_up_forward = {GetCoordinates().y - 1, GetCoordinates().x - 2};
    if(left_up_forward.x >= 0 && left_up_forward.y >= 0 &&
        ((board->GetPiece(left_up_forward.x,left_up_forward.y) == nullptr) ||(
             board->GetPiece(left_up_forward.x,left_up_forward.y) != nullptr &&
             board->GetPiece(left_up_forward.x,left_up_forward.y)->GetColor() == enemy_color))){
        possible_moves.push_back(left_up_forward);
    }
    Coordinates left_down_forward = {GetCoordinates().y + 1, GetCoordinates().x - 2};
    if(left_down_forward.x >= 0 &&left_down_forward.y <= 7 &&
        ((board->GetPiece(left_down_forward.x,left_down_forward.y) == nullptr) ||(
             board->GetPiece(left_down_forward.x,left_down_forward.y) != nullptr &&
             board->GetPiece(left_down_forward.x,left_down_forward.y)->GetColor() == enemy_color))){
        possible_moves.push_back(left_down_forward);
    }
    Coordinates right_up_forward = {GetCoordinates().y - 1, GetCoordinates().x + 2};
    if(right_up_forward.x <= 7 &&right_up_forward.y >= 0 &&
        ((board->GetPiece(right_up_forward.x,right_up_forward.y) == nullptr) ||(
             board->GetPiece(right_up_forward.x,right_up_forward.y) != nullptr &&
             board->GetPiece(right_up_forward.x,right_up_forward.y)->GetColor() == enemy_color))){
        possible_moves.push_back(right_up_forward);
    }
    Coordinates right_down_forward = {GetCoordinates().y + 1, GetCoordinates().x + 2};
    if(right_down_forward.x <= 7 &&right_down_forward.y <= 7 &&
        ((board->GetPiece(right_down_forward.x,right_down_forward.y) == nullptr) ||(
             board->GetPiece(right_down_forward.x,right_down_forward.y) != nullptr &&
             board->GetPiece(right_down_forward.x,right_down_forward.y)->GetColor() == enemy_color))){
        possible_moves.push_back(right_down_forward);
    }

    std::vector<Coordinates> filtr_moves;
    if(filtr){
        board->FiltrMovies(possible_moves,filtr_moves, this, enemy_color);
        return filtr_moves;

    }
    return possible_moves;
}
