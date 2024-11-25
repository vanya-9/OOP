#include "boardcontroller.h"
#include "logic.h"
BoardController::BoardController(Board* board,
                                 GraphicBoard* graphic_board,
                                 QObject* parent)
    : QObject(parent), board_(board), graphic_board_(graphic_board) {
    connect(graphic_board_, &GraphicBoard::cellClicked, this,
            &BoardController::handleCellClick);
}

void BoardController::handleCellClick(int x, int y) {
    Color turncolor = turn_to_walk % 2 == 0  ? WHITE : BLACK;
    Piece* clickedPiece = board_->GetPiece(x, y);
    if (x >= 0 && x <= 7 && y >= 0 && y <= 7 ) {
        if (clickedPiece != nullptr && board_->GetPiece(x, y)->GetColor() == turncolor) {
            if (selected_piece_ != nullptr &&
                clickedPiece->GetColor() != selected_piece_->GetColor()) {
                {
                    movePieceTo(selected_piece_, {y, x});
                    selected_piece_ = nullptr;
                }
            } else if (selected_piece_ == clickedPiece) {
                graphic_board_->clearHighlights();
                selected_piece_ = nullptr;
            } else {
                graphic_board_->clearHighlights();
                {
                    selected_piece_ = clickedPiece;
                    highlightMoves(selected_piece_);
                }
            }
        } else if (selected_piece_ != nullptr) {
            movePieceTo(selected_piece_, {y, x});
            selected_piece_ = nullptr;
        }
    }
}

void BoardController::highlightMoves(Piece* piece) {
    auto possible_moves = piece->validator(board_);
    graphic_board_->highlightPossibleMoves(possible_moves);
}

void BoardController::movePieceTo(Piece* piece,
                                  const Coordinates& target_coords) {
    board_->SetPiece(piece, target_coords);
    graphic_board_->clearHighlights();
    graphic_board_->drawPieces(true);

}
