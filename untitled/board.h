#ifndef BOARD_H
#define BOARD_H
#include <QObject>
#include "logic.h"
#include "piece.h"
#include "piecefactory.h"

class Board : public QObject {
  Q_OBJECT
  std::shared_ptr<Piece> content_[board_size][board_size];
  Factory<Piece, int, std::function<std::shared_ptr<Piece>(Color, Coordinates)>> factory_;

 public:
  Board();

  void OnPawnTransform(std::shared_ptr<Piece> pawn, Coordinates new_coordinates);

  void ContentTmpChange(Coordinates coordinates, bool state, std::shared_ptr<Piece> piece = nullptr);

  void SetDefault();

  std::shared_ptr<Piece> GetPiece(int y, int x);

  void SetPiece(std::shared_ptr<Piece> piece, Coordinates new_coordinates);
  bool CellIsAttack(Board* board, Coordinates piece_coordinates, Color enemy_color);
  void FiltrMoves(std::vector<Coordinates> possible_moves,
                  std::vector<Coordinates>& filtr_moves,
                  std::shared_ptr<Piece> piece,
                  Color enemy_color);
  void SetPawns();
  void SetRook();
  void SetKnight();
  void SetBishop();
  void SetQueen();
  void SetKing();

  bool IsShortCastling(Coordinates new_coordinates);
  bool IsLongCastling(Coordinates new_coordinates);

  void MakeShortCastling(std::shared_ptr<Piece> piece, Coordinates new_coordinates);
  void MakeLongCastling(std::shared_ptr<Piece> piece, Coordinates new_coordinates);

  std::shared_ptr<King> GetEnemyKing(std::shared_ptr<Piece> piece, Board* board);
  std::shared_ptr<King> GetFriendKing(std::shared_ptr<Piece> piece, Board* board);

 signals:
  void ChooseFigure(std::shared_ptr<Piece> Pawn);
  void UpdateFigure();

 public slots:
  void onTransformationChosen(int chosen_figure, std::shared_ptr<Piece> pawn);
};

#endif
