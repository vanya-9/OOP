// graphicboard.h
#ifndef GRAPHICBOARD_H
#define GRAPHICBOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "board.h"
class GraphicBoard : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicBoard(QWidget *parent = nullptr);
    void SetBoard(Board& board);
    void setupScene();
    void drawBoard();
    void drawPieces(bool update = false);
    void highlightPossibleMoves(const std::vector<Coordinates>& moves);
    void drawTypePiece(std::map<std::pair<int, int>, QGraphicsPixmapItem*> &piece_items, QString path, int row, int col);

    void clearHighlights();

signals:
    void cellClicked(int x, int y);
    void transformationChosen(int chosen_figure, Piece*pawn);



private:
    QGraphicsScene *scene_;
    Board* board_;
    Piece* selected_piece_ = nullptr;     // Указатель на выбранную фигуру (для подсветки)
    std::vector<QGraphicsRectItem*> highlighted_cells_;
    std::map<std::pair<int, int>, QGraphicsPixmapItem*> piece_items_;
    void transformPawn(Piece* pawn, const int new_type);

protected:
    void mousePressEvent(QMouseEvent *event);

public slots:
    void ChooseTransform(Piece* pawn);
    void UpdateFigure();

};

#endif // GRAPHICBOARD_H
