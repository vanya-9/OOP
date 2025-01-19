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
    if (x < 0 || x >= board_size || y < 0 || y >= board_size) {
        return;
    }

    Color turncolor = (turn_to_walk % 2 == 0) ? WHITE : BLACK;
    std::shared_ptr<Piece> clicked_piece = board_->GetPiece(x, y);

    if (clicked_piece == selected_piece_) {
        graphic_board_->clearHighlights();
        selected_piece_ = nullptr;
        return;
    }

    if (clicked_piece != nullptr && clicked_piece->GetColor() == turncolor) {
        graphic_board_->clearHighlights();
        selected_piece_ = clicked_piece;
        highlightMoves(selected_piece_);
        return;
    }

    if (selected_piece_ != nullptr) {
        movePieceTo(selected_piece_, {y, x});
        graphic_board_->clearHighlights();
        selected_piece_ = nullptr;
    }
}


void BoardController::highlightMoves(std::shared_ptr<Piece> piece) {
    auto possible_moves = piece->validator(board_);
    graphic_board_->highlightPossibleMoves(possible_moves);
}

void BoardController::movePieceTo(std::shared_ptr<Piece> piece,
                                  const Coordinates& target_coords) {
    board_->SetPiece(piece, target_coords);
    graphic_board_->clearHighlights();
    graphic_board_->drawPieces(true);

}
