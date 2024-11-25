#ifndef BOARDCONTROLLER_H
#define BOARDCONTROLLER_H

#include <QObject>
#include "board.h"
#include "graphicboard.h"

class BoardController : public QObject {
    Q_OBJECT

public:
    BoardController(Board* board, GraphicBoard* graphic_board, QObject* parent = nullptr);

public slots:
    void handleCellClick(int x, int y);

private:
    Board* board_;
    GraphicBoard* graphic_board_;
    Piece* selected_piece_ = nullptr;

    void highlightMoves(Piece* piece);
    void movePieceTo(Piece* piece, const Coordinates& target_coords);
};

#endif // BOARDCONTROLLER_H
