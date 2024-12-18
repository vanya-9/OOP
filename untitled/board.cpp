#include "board.h"
#include <QDebug>
/*namespace*/
std::shared_ptr<Piece> CreatePawn(Color color, Coordinates coordinates) {
    return std::make_shared<Pawn>(color, coordinates);
}

std::shared_ptr<Piece> CreateRook(Color color, Coordinates coordinates) {
    return std::make_shared<Rook>(color, coordinates);
}

std::shared_ptr<Piece> CreateKnight(Color color, Coordinates coordinates) {
    return std::make_shared<Knight>(color, coordinates);
}

std::shared_ptr<Piece> CreateBishop(Color color, Coordinates coordinates) {
    return std::make_shared<Bishop>(color, coordinates);
}

std::shared_ptr<Piece> CreateQueen(Color color, Coordinates coordinates) {
    return std::make_shared<Queen>(color, coordinates);
}

std::shared_ptr<Piece> CreateKing(Color color, Coordinates coordinates) {
    return std::make_shared<King>(color, coordinates);
}




Board::Board() {
    for (int i = 0; i < board_size; ++i) {
        for (int j = 0; j < board_size; ++j) {
            content_[i][j] = nullptr;
        }
    }
    SetDefault();
}

void Board::SetPawns(){
    for (int i = 0; i < board_size; ++i) {
        Coordinates coords_w = {1, i};
        content_[1][i] = factory_.CreateObject(PAWN, WHITE, coords_w);
        Coordinates coords_b = {6, i};
        content_[6][i] = factory_.CreateObject(PAWN, BLACK, coords_b);
    }
}

void Board::SetRook(){
    Coordinates coords_w_rook = {0, 0};
    content_[0][0] = factory_.CreateObject(ROOK, WHITE, coords_w_rook);
    coords_w_rook = {0, 7};
    content_[0][7] = factory_.CreateObject(ROOK, WHITE, coords_w_rook);

    Coordinates coords_b_rook = {7, 0};
    content_[7][0] = factory_.CreateObject(ROOK, BLACK, coords_b_rook);
    coords_b_rook = {7, 7};
    content_[7][7] = factory_.CreateObject(ROOK, BLACK, coords_b_rook);
}

void Board::SetKnight(){
    Coordinates coords_w_knight = {0, 1};
    content_[0][1] = factory_.CreateObject(KNIGHT, WHITE, coords_w_knight);
    coords_w_knight = {0, 6};
    content_[0][6] = factory_.CreateObject(KNIGHT, WHITE, coords_w_knight);

    Coordinates coords_b_knight = {7, 1};
    content_[7][1] = factory_.CreateObject(KNIGHT, BLACK, coords_b_knight);
    coords_b_knight = {7, 6};
    content_[7][6] = factory_.CreateObject(KNIGHT, BLACK, coords_b_knight);
}

void Board::SetBishop(){
    Coordinates coords_w_bishop = {0, 2};
    content_[0][2] = factory_.CreateObject(BISHOP, WHITE, coords_w_bishop);
    coords_w_bishop = {0, 5};
    content_[0][5] = factory_.CreateObject(BISHOP, WHITE, coords_w_bishop);
    Coordinates coords_b_bishop = {7, 2};
    content_[7][2] = factory_.CreateObject(BISHOP, BLACK, coords_b_bishop);
    coords_b_bishop = {7, 5};
    content_[7][5] = factory_.CreateObject(BISHOP, BLACK, coords_b_bishop);
}

void Board::SetKing(){
    Coordinates coords_w_king = {0,4};
    content_[0][4] = factory_.CreateObject(KING, WHITE, coords_w_king);

    Coordinates coords_b_king = {7,4};
    content_[7][4] = factory_.CreateObject(KING, BLACK, coords_b_king);
}

void Board::SetQueen(){
    Coordinates coords_w_queen= {0, 3};
    content_[0][3] = factory_.CreateObject(QUEEN, WHITE, coords_w_queen);

    Coordinates coords_b_queen = {7, 3};
    content_[7][3] = factory_.CreateObject(QUEEN, BLACK, coords_b_queen);
}

void Board::SetDefault() {
    factory_.Register(PAWN, CreatePawn);
    factory_.Register(ROOK, CreateRook);
    factory_.Register(KNIGHT, CreateKnight);
    factory_.Register(BISHOP, CreateBishop);
    factory_.Register(QUEEN, CreateQueen);
    factory_.Register(KING, CreateKing);

    SetPawns();
    SetRook();
    SetKnight();
    SetBishop();
    SetQueen();
    SetKing();
}


std::shared_ptr<Piece> Board::GetPiece(int x, int y){
    return content_[y][x];
}

bool Board::IsShortCastling(Coordinates new_coordinates){
    if(castling == true && ((new_coordinates.y == 7 && new_coordinates.x == 6)
    || (new_coordinates.y == 0 && new_coordinates.x == 6))){
        return true;
    }
    return false;
}

bool Board::IsLongCastling(Coordinates new_coordinates){
    if(castling == true && ((new_coordinates.y == 7 && new_coordinates.x == 2) ||
    (new_coordinates.y == 0 && new_coordinates.x == 2))){
        return true;
    }
    return false;
}

void Board::MakeShortCastling(std::shared_ptr<Piece> piece, Coordinates new_coordinates){
    std::shared_ptr<Piece> rook;
    Coordinates king_new_coords;
    Coordinates rook_new_coords;

    king_new_coords = {new_coordinates.y, new_coordinates.x};
    rook = GetPiece(new_coordinates.x + 1, new_coordinates.y);
    rook_new_coords = {new_coordinates.y, new_coordinates.x - 1};
    content_[king_new_coords.y][king_new_coords.x] = piece;
    content_[piece->GetCoordinates().y][piece->GetCoordinates().x] = nullptr;
    piece->SetCoordinates(king_new_coords);
    content_[rook_new_coords.y][rook_new_coords.x] = rook;
    content_[new_coordinates.y][new_coordinates.x + 1] = nullptr;
    rook->SetCoordinates(rook_new_coords);
    turn_to_walk++;
    castling = false;
    piece->first_move = false;

}

void Board::MakeLongCastling(std::shared_ptr<Piece> piece, Coordinates new_coordinates){
    std::shared_ptr<Piece> rook;
    Coordinates king_new_coords;
    Coordinates rook_new_coords;

    king_new_coords = {new_coordinates.y, new_coordinates.x};
    rook = GetPiece(new_coordinates.x - 2, new_coordinates.y);
    rook_new_coords = {new_coordinates.y, new_coordinates.x + 1};
    content_[king_new_coords.y][king_new_coords.x] = piece;
    content_[piece->GetCoordinates().y][piece->GetCoordinates().x] = nullptr;
    piece->SetCoordinates(king_new_coords);
    content_[rook_new_coords.y][rook_new_coords.x] = rook;
    content_[new_coordinates.y][new_coordinates.x - 2] = nullptr;
    rook->SetCoordinates(rook_new_coords);

    turn_to_walk++;
    castling = false;
    piece->first_move = false;
}

void Board::SetPiece(std::shared_ptr<Piece> piece, Coordinates new_coordinates) {
    if (new_coordinates.y < 0 || new_coordinates.y >= board_size ||
        new_coordinates.x < 0 || new_coordinates.x >= board_size) {
        return;
    }
    if(IsShortCastling(new_coordinates)){
        MakeShortCastling(piece, new_coordinates);
        return;
    }

    if(IsLongCastling(new_coordinates)){
        MakeLongCastling(piece, new_coordinates);
        return;
    }
    // if(castling == true && (new_coordinates.y == 7 || new_coordinates.y == 0) && (new_coordinates.x == 6 || new_coordinates.x == 2)){
    //     std::shared_ptr<Piece> rook;
    //     Coordinates king_new_coords;
    //     Coordinates rook_new_coords;
    //     if(new_coordinates.x == 6){
    //         king_new_coords = {new_coordinates.y, new_coordinates.x};
    //         rook = GetPiece(new_coordinates.x + 1, new_coordinates.y);
    //         rook_new_coords = {new_coordinates.y, new_coordinates.x - 1};
    //         content_[king_new_coords.y][king_new_coords.x] = piece;
    //         content_[piece->GetCoordinates().y][piece->GetCoordinates().x] = nullptr;
    //         piece->SetCoordinates(king_new_coords);
    //         content_[rook_new_coords.y][rook_new_coords.x] = rook;
    //         content_[new_coordinates.y][new_coordinates.x + 1] = nullptr;
    //         rook->SetCoordinates(rook_new_coords);
    //     }
    //     else{
    //         king_new_coords = {new_coordinates.y, new_coordinates.x};
    //         rook = GetPiece(new_coordinates.x - 2, new_coordinates.y);
    //         rook_new_coords = {new_coordinates.y, new_coordinates.x + 1};
    //         content_[king_new_coords.y][king_new_coords.x] = piece;
    //         content_[piece->GetCoordinates().y][piece->GetCoordinates().x] = nullptr;
    //         piece->SetCoordinates(king_new_coords);
    //         content_[rook_new_coords.y][rook_new_coords.x] = rook;
    //         content_[new_coordinates.y][new_coordinates.x - 2] = nullptr;
    //         rook->SetCoordinates(rook_new_coords);
    //     }
    //     turn_to_walk++;
    //     castling = false;
    //     piece->first_move = false;
    //     return;
    // }
    auto possible_moves = piece->validator(this);
    for (const auto& coordinates : possible_moves) {
        if (coordinates.y == new_coordinates.y && coordinates.x == new_coordinates.x) {
            if (this->GetPiece(new_coordinates.y, new_coordinates.x) != nullptr) {
                //std::shared_ptr<Piece> shared_ptr(content_[new_coordinates.y][new_coordinates.x]);
                content_[new_coordinates.y][new_coordinates.x] = nullptr;
            }

            content_[piece->GetCoordinates().y][piece->GetCoordinates().x] = nullptr;
            piece->SetCoordinates(new_coordinates);
            content_[new_coordinates.y][new_coordinates.x] = piece;
            piece->first_move = false;
            turn_to_walk++;
            if ((piece->GetColor() == BLACK && new_coordinates.y == 0) ||
                (piece->GetColor() == WHITE && new_coordinates.y == 7)) {

                if (std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(piece)) {
                    pawn->SetUpdate();
                    emit ChooseFigure(piece);

                }
            }
    }
}
}


void Board::onTransformationChosen(int chosen_figure, std::shared_ptr<Piece> pawn)
{

    Coordinates current_coords = pawn->GetCoordinates();
//std::make_shared<Queen>(color, coordinates);
    std::shared_ptr<Piece> newPiece = nullptr;
    switch (chosen_figure) {
        if (this->GetPiece(current_coords.y, current_coords.x) != nullptr) {
            // delete content_[current_coords.y][current_coords.x];
            content_[current_coords.y][current_coords.x] = nullptr;
        }
    case QUEEN:
        newPiece = std::make_shared<Queen>(pawn->GetColor(), current_coords);
        content_[current_coords.y][current_coords.x] = newPiece;
        break;
    case ROOK:
        newPiece = std::make_shared<Rook>(pawn->GetColor(), current_coords);
        content_[current_coords.y][current_coords.x] = newPiece;
        break;
    case BISHOP:
        newPiece = std::make_shared<Bishop>(pawn->GetColor(), current_coords);
        content_[current_coords.y][current_coords.x] = newPiece;
        break;
    case KNIGHT:
        newPiece = std::make_shared<Knight>(pawn->GetColor(), current_coords);
        content_[current_coords.y][current_coords.x] = newPiece;
        break;
    }

    SetPiece(newPiece, current_coords);
    // delete pawn;
    emit UpdateFigure();

}

void Board::ContentTmpChange(Coordinates coordinates, bool state, std::shared_ptr<Piece> piece){
    if (!state){
        content_[coordinates.y][coordinates.x] = nullptr;
    }
    else{
        content_[coordinates.y][coordinates.x] = piece;
        if(piece != nullptr){
            piece->SetCoordinates(coordinates);
        }
    }

}
 // ////////////////////////////////////////////////////////////////////////////////////
void Board::FiltrMovies(std::vector<Coordinates> possible_movies,
                        std::vector<Coordinates>& filtr_movies, std::shared_ptr<Piece> piece, Color enemy_color){
    auto copy_board = this;
    std::shared_ptr<King> our_king;
    std::shared_ptr<King> enemy_king;

    for (int x = 0; x < board_size; x++) {
        for (int y = 0; y < board_size; y++) {
            if (copy_board->GetPiece(x, y) != nullptr &&
                copy_board->GetPiece(x, y)->GetName() == "King" &&
                copy_board->GetPiece(x, y)->GetColor() != enemy_color) {
                our_king = std::dynamic_pointer_cast<King>(copy_board->GetPiece(x, y));
            }
            if (copy_board->GetPiece(x, y) != nullptr &&
                copy_board->GetPiece(x, y)->GetName() == "King" &&
                copy_board->GetPiece(x, y)->GetColor() == enemy_color) {
                enemy_king = std::dynamic_pointer_cast<King>(copy_board->GetPiece(x, y));
            }
        }
    }
    auto piece_start_coordinates = piece->GetCoordinates();
    auto our_king_coordinates = our_king->GetCoordinates();

    int number_movie = 0;
    while(number_movie < possible_movies.size()){
        auto coordinates_to = possible_movies[number_movie];
        auto tmp_piece = copy_board->GetPiece(coordinates_to.x, coordinates_to.y);
        copy_board->ContentTmpChange(coordinates_to, true, piece);
        copy_board->ContentTmpChange(piece_start_coordinates, false);
        if(!CellIsAttack(copy_board, our_king_coordinates, enemy_color)){
            if(!(coordinates_to.x == enemy_king->GetCoordinates().x &&
                coordinates_to.y == enemy_king->GetCoordinates().y)){
            filtr_movies.push_back(coordinates_to);
            }
        }
        copy_board->ContentTmpChange(coordinates_to, true, tmp_piece);
        copy_board->ContentTmpChange(piece_start_coordinates, true, piece);
        number_movie++;
    }
}

bool Board::CellIsAttack(Board* board, Coordinates piece_coordinates, Color enemy_color){
    for(int x = 0; x <board_size; x++){
        for(int y = 0; y < board_size; y++){
            if(board->GetPiece(x,y) != nullptr && board->GetPiece(x,y)->GetName()!= "King"
                &&board->GetPiece(x,y)->GetColor() == enemy_color){
                auto enemy_piece = board->GetPiece(x,y);
                auto enemy_movies = enemy_piece->validator(board, false);
                for(auto& move : enemy_movies){
                    if(piece_coordinates.x == move.x &&
                        piece_coordinates.y == move.y){
                        return true;
                    }
                }


            }

        }
    }
    return false;
}
