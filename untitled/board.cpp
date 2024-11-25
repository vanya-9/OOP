#include "board.h"
#include <QDebug>
namespace {
Piece* CreatePawn(Color color, Coordinates coordinates) {
    return new Pawn(color, coordinates);}

Piece* CreateRook(Color color, Coordinates coordinates) {
    return new Rook(color, coordinates);}

Piece* CreateKnight(Color color, Coordinates coordinates) {
    return new Knight(color, coordinates);}

Piece* CreateBishop(Color color, Coordinates coordinates) {
    return new Bishop(color, coordinates);}

Piece* CreateQueen(Color color, Coordinates coordinates) {
    return new Queen(color, coordinates);}


Piece* CreateKing(Color color, Coordinates coordinates) {
    return new King(color, coordinates);
}
}


Board::Board() {
    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            content_[i][j] = nullptr;
        }
    }
}

void Board::SetDefault() {
    factory_.Register(PAWN, CreatePawn);
    factory_.Register(ROOK, CreateRook);
    factory_.Register(KNIGHT, CreateKnight);
    factory_.Register(BISHOP, CreateBishop);
    factory_.Register(QUEEN, CreateQueen);
    factory_.Register(KING, CreateKing);

    for (int i = 0; i < board_size; ++i) {
        Coordinates coords_w = {1, i};
        content_[1][i] = factory_.CreateObject(PAWN, WHITE, coords_w);
        Coordinates coords_b = {6, i};
        content_[6][i] = factory_.CreateObject(PAWN, BLACK, coords_b);
    }
    Coordinates coords_w_rook = {0, 0};
    content_[0][0] = factory_.CreateObject(ROOK, WHITE, coords_w_rook);
    coords_w_rook = {0, 7};
    content_[0][7] = factory_.CreateObject(ROOK, WHITE, coords_w_rook);

    Coordinates coords_b_rook = {7, 0};
    content_[7][0] = factory_.CreateObject(ROOK, BLACK, coords_b_rook);
    coords_b_rook = {7, 7};
    content_[7][7] = factory_.CreateObject(ROOK, BLACK, coords_b_rook);

    Coordinates coords_w_knight = {0, 1};
    content_[0][1] = factory_.CreateObject(KNIGHT, WHITE, coords_w_knight);
    coords_w_knight = {0, 6};
    content_[0][6] = factory_.CreateObject(KNIGHT, WHITE, coords_w_knight);

    Coordinates coords_b_knight = {7, 1};
    content_[7][1] = factory_.CreateObject(KNIGHT, BLACK, coords_b_knight);
    coords_b_knight = {7, 6};
    content_[7][6] = factory_.CreateObject(KNIGHT, BLACK, coords_b_knight);

    Coordinates coords_w_bishop = {0, 2};
    content_[0][2] = factory_.CreateObject(BISHOP, WHITE, coords_w_bishop);
    coords_w_bishop = {0, 5};
    content_[0][5] = factory_.CreateObject(BISHOP, WHITE, coords_w_bishop);
    Coordinates coords_b_bishop = {7, 2};
    content_[7][2] = factory_.CreateObject(BISHOP, BLACK, coords_b_bishop);
    coords_b_bishop = {7, 5};
    content_[7][5] = factory_.CreateObject(BISHOP, BLACK, coords_b_bishop);

    Coordinates coords_w_queen= {0, 3};
    content_[0][3] = factory_.CreateObject(QUEEN, WHITE, coords_w_queen);

    Coordinates coords_b_queen = {7, 3};
    content_[7][3] = factory_.CreateObject(QUEEN, BLACK, coords_b_queen);

    Coordinates coords_w_king = {0,4};
    content_[0][4] = factory_.CreateObject(KING, WHITE, coords_w_king);

    Coordinates coords_b_king = {7,4};
    content_[7][4] = factory_.CreateObject(KING, BLACK, coords_b_king);



}


Piece* Board::GetPiece(int x, int y){
    return content_[y][x];
}

void Board::SetPiece(Piece* piece, Coordinates new_coordinates) {
    if (new_coordinates.y < 0 || new_coordinates.y >= board_size ||
        new_coordinates.x < 0 || new_coordinates.x >= board_size) {
        return;
    }

    if(rokirovka == true && (new_coordinates.y == 7 || new_coordinates.y == 0) && (new_coordinates.x == 6 || new_coordinates.x == 2)){
        Piece* rook;
        Coordinates king_new_coords;
        Coordinates rook_new_coords ;
        if(new_coordinates.x == 6){
            king_new_coords = {new_coordinates.y, new_coordinates.x};
            rook = GetPiece(new_coordinates.x + 1, new_coordinates.y);
            rook_new_coords = {new_coordinates.y, new_coordinates.x - 1};
            content_[king_new_coords.y][king_new_coords.x] = piece;
            content_[piece->GetCoordinates().y][piece->GetCoordinates().x] = nullptr;
            piece->SetCoordinates(king_new_coords);
            content_[rook_new_coords.y][rook_new_coords.x] = rook;
            content_[new_coordinates.y][new_coordinates.x + 1] = nullptr;
            rook->SetCoordinates(rook_new_coords);
        }
        else{
            king_new_coords = {new_coordinates.y, new_coordinates.x};
            rook = GetPiece(new_coordinates.x - 2, new_coordinates.y);
            rook_new_coords = {new_coordinates.y, new_coordinates.x + 1};
            content_[king_new_coords.y][king_new_coords.x] = piece;
            content_[piece->GetCoordinates().y][piece->GetCoordinates().x] = nullptr;
            piece->SetCoordinates(king_new_coords);
            content_[rook_new_coords.y][rook_new_coords.x] = rook;
            content_[new_coordinates.y][new_coordinates.x - 2] = nullptr;
            rook->SetCoordinates(rook_new_coords);
        }
        turn_to_walk++;
        rokirovka = false;
        piece->first_move = false;
        return;
    }

    auto possible_moves = piece->validator(this);
    for (const auto& coordinates : possible_moves) {
        if (coordinates.y == new_coordinates.y && coordinates.x == new_coordinates.x) {
            if (this->GetPiece(new_coordinates.y, new_coordinates.x) != nullptr) {
                delete content_[new_coordinates.y][new_coordinates.x];
                content_[new_coordinates.y][new_coordinates.x] = nullptr;
            }

            content_[piece->GetCoordinates().y][piece->GetCoordinates().x] = nullptr;
            piece->SetCoordinates(new_coordinates);
            content_[new_coordinates.y][new_coordinates.x] = piece;
            piece->first_move = false;
            turn_to_walk++;
            if ((piece->GetColor() == BLACK && new_coordinates.y == 0) ||
                (piece->GetColor() == WHITE && new_coordinates.y == 7)) {

                if (dynamic_cast<Pawn*>(piece)) {
                    dynamic_cast<Pawn*>(piece)->SetUpdate();
                    emit ChooseFigure(piece);

                }
            }
    }
}
}


void Board::onTransformationChosen(int chosen_figure, Piece* pawn)
{

    Coordinates current_coords = pawn->GetCoordinates();

    Piece* newPiece = nullptr;
    switch (chosen_figure) {
        if (this->GetPiece(current_coords.y, current_coords.x) != nullptr) {
            delete content_[current_coords.y][current_coords.x];
            content_[current_coords.y][current_coords.x] = nullptr;
        }
    case QUEEN:
        newPiece = new Queen(pawn->GetColor(), current_coords);
        content_[current_coords.y][current_coords.x] = newPiece;
        break;
    case ROOK:
        newPiece = new Rook(pawn->GetColor(), current_coords);
        content_[current_coords.y][current_coords.x] = newPiece;
        break;
    case BISHOP:
        newPiece = new Bishop(pawn->GetColor(), current_coords);
        content_[current_coords.y][current_coords.x] = newPiece;
        break;
    case KNIGHT:
        newPiece = new Knight(pawn->GetColor(), current_coords);
        content_[current_coords.y][current_coords.x] = newPiece;
        break;
    }

    SetPiece(newPiece, current_coords);
    delete pawn;
    emit UpdateFigure();

}

void Board::ContentTmpChange(Coordinates coordinates, bool state, Piece* piece){
    if (!state){
        content_[coordinates.y][coordinates.x] = nullptr;
    }
    else{
        content_[coordinates.y][coordinates.x] = piece;
    }

}
