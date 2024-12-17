#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <QObject>
#include "board.h"
#include "graphicboard.h"
#include <memory>

class BoardController : public QObject {
    Q_OBJECT

public:
    BoardController(Board* board, GraphicBoard* graphic_board, QObject* parent = nullptr);

public slots:
    void handleCellClick(int x, int y);

private:
    Board* board_;
    GraphicBoard* graphic_board_;
    std::shared_ptr<Piece> selected_piece_ = nullptr;

    void highlightMoves(std::shared_ptr<Piece> piece);
    void movePieceTo(std::shared_ptr<Piece> piece, const Coordinates& target_coords);
};

#endif // BOARDCONTROLLER_H
