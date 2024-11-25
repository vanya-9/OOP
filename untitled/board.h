#ifndef BOARD_H
#define BOARD_H
#include "logic.h"
#include <QObject>
#include "piece.h"
#include "piecefactory.h"

class Board : public QObject
{
    Q_OBJECT
    Piece* content_[board_size][board_size];
    Factory<Piece, int, std::function<Piece*(Color, Coordinates)>> factory_;


public:
    Board();

    void ContentTmpChange(Coordinates coordinates, bool state, Piece* piece = nullptr);

    void SetDefault();

    Piece* GetPiece(int y, int x);

    void SetPiece(Piece* piece, Coordinates new_coordinates);

signals:
    void ChooseFigure(Piece* Pawn);
    void UpdateFigure();

public slots:
    void onTransformationChosen(int chosen_figure, Piece* pawn);
};

#endif // BOARD_H
