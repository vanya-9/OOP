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
  enum class GameResult {
    Continue,
    Checkmate,
    Draw
  };

  GameResult CheckResult();

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

  std::shared_ptr<King> GetNeededKing(Board* board, Color color);

  bool CanPlayerGo(Color color);



 signals:
  void ChooseFigure(std::shared_ptr<Piece> Pawn);
  void UpdateFigure();
  void GameEnded(GameResult result);

 public slots:
  void onTransformationChosen(int chosen_figure, std::shared_ptr<Piece> pawn);
};

#endif
