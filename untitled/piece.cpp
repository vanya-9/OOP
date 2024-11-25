#include "piece.h"

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
