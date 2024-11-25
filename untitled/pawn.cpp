#include "pawn.h"
#include "board.h"
#include <QDebug>
std::vector<Coordinates> Pawn::validator(Board* board) {
    std::vector<Coordinates> possible_moves;
    Coordinates forward {0, 0};
    Coordinates forward_two{0, 0};
    Coordinates rightAttack{0, 0};
    Coordinates leftAttack{0, 0};
    Coordinates coordinates_this = this->GetCoordinates();
    if(this->GetColor() == WHITE){
    int direction =  1;

    forward = {coordinates_this.y + 1*direction, coordinates_this.x};
    forward_two ={coordinates_this.y + 2*direction, coordinates_this.x};
    rightAttack = {coordinates_this.y + direction, coordinates_this.x + 1};
    leftAttack = {coordinates_this.y + direction, coordinates_this.x - 1};
    if (this->first_move && board->GetPiece(forward.x, forward.y) == nullptr &&
        board->GetPiece(forward_two.x, forward_two.y) == nullptr) {
        possible_moves.push_back(forward_two);

    }


    if (forward.y < board_size && board->GetPiece(forward.x, forward.y) == nullptr ) {
        possible_moves.push_back(forward);
    }

    if(rightAttack.x < board_size && rightAttack.y < board_size &&
    board->GetPiece(rightAttack.x, rightAttack.y) != nullptr &&
     board->GetPiece(rightAttack.x, rightAttack.y)->GetColor() != WHITE)
     {
         possible_moves.push_back(rightAttack);
         //qDebug() << "kruto";
     }

    if(leftAttack.x >= 0 && leftAttack.y <board_size &&
         board->GetPiece(leftAttack.x, leftAttack.y) != nullptr &&
         board->GetPiece(leftAttack.x, leftAttack.y)->GetColor() != WHITE){
         possible_moves.push_back(leftAttack);
     }

    }
    if(this->GetColor() == BLACK){
        int direction = -1;
        forward = {coordinates_this.y + direction, coordinates_this.x};
        forward_two = {coordinates_this.y + 2*direction, coordinates_this.x};
        rightAttack = {coordinates_this.y + direction, coordinates_this.x + 1};
        leftAttack = {coordinates_this.y + direction, coordinates_this.x - 1};

        if (this->first_move && board->GetPiece(forward.x, forward.y) == nullptr &&
            board->GetPiece(forward_two.x, forward_two.y) == nullptr) {
            possible_moves.push_back(forward_two);
        }

        if (forward.y >= 0 && board->GetPiece(forward.x, forward.y) == nullptr ) {
            possible_moves.push_back(forward);
        }

        if(rightAttack.x < board_size && rightAttack.y >= 0 &&
            board->GetPiece(rightAttack.x, rightAttack.y) != nullptr &&
            board->GetPiece(rightAttack.x, rightAttack.y)->GetColor() != BLACK)
        {
            possible_moves.push_back(rightAttack);
        }

        if(leftAttack.x >= 0 && leftAttack.y >=0 &&
            board->GetPiece(leftAttack.x, leftAttack.y) != nullptr &&
            board->GetPiece(leftAttack.x, leftAttack.y)->GetColor() != BLACK){
            possible_moves.push_back(leftAttack);
        }
    }
    return possible_moves;
}


void Pawn::SetUpdate(){
    update_figure_ = true;
}

bool Pawn::GetUpdate(){
    return update_figure_;
}

std::vector<Coordinates> Pawn::AllValidator(Board* board){
    std::vector<Coordinates> possible_moves;
    Coordinates rightAttack{0, 0};
    Coordinates leftAttack{0, 0};
    Coordinates coordinates_this = this->GetCoordinates();
    if(this->GetColor() == WHITE){
        int direction =  1;
        rightAttack = {coordinates_this.y + direction, coordinates_this.x + 1};
        leftAttack = {coordinates_this.y + direction, coordinates_this.x - 1};
        if(rightAttack.x < board_size && rightAttack.y < board_size)
        {
            possible_moves.push_back(rightAttack);
        }

        if(leftAttack.x >= 0 && leftAttack.y <board_size){
            possible_moves.push_back(leftAttack);
        }

    }
    if(this->GetColor() == BLACK){
        int direction = -1;
        rightAttack = {coordinates_this.y + direction, coordinates_this.x + 1};
        leftAttack = {coordinates_this.y + direction, coordinates_this.x - 1};

        if(rightAttack.x < board_size && rightAttack.y >= 0)
        {
            possible_moves.push_back(rightAttack);
        }

        if(leftAttack.x >= 0 && leftAttack.y >=0){
            possible_moves.push_back(leftAttack);
        }
    }
    return possible_moves;
}






