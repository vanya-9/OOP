#include "bishop.h"
#include "board.h"
Bishop::Bishop(Color color, Coordinates coordinates)
    : Piece(color, coordinates, "Bishop") {}

std::vector<Coordinates> Bishop::validator(Board* board) {
  std::vector<Coordinates> possible_moves;
  Coordinates forward = {GetCoordinates().y, GetCoordinates().x};
  Coordinates forward_push;
  Color enemy_color = GetColor() == WHITE ? BLACK : WHITE;
  for (int k = 1; k <= 7; k++) {
    if (forward.x - k >= 0 && forward.y + k <= 7) {
      if (board->GetPiece(forward.x - k, forward.y + k) == nullptr) {
        forward_push = {forward.y + k, forward.x - k};
        possible_moves.push_back(forward_push);
      } else if (board->GetPiece(forward.x - k, forward.y + k) != nullptr) {
        if (board->GetPiece(forward.x - k, forward.y + k)->GetColor() ==
            enemy_color) {
          forward_push = {forward.y + k, forward.x - k};
          possible_moves.push_back(forward_push);
        }break;
      }

    }
  }

  for (int k = 1; k <= 7; k++) {
      if (forward.x + k <= 7 && forward.y - k >= 0) {
          if (board->GetPiece(forward.x + k, forward.y - k) == nullptr) {
              forward_push = {forward.y - k, forward.x + k};
              possible_moves.push_back(forward_push);
          } else if (board->GetPiece(forward.x + k, forward.y - k) != nullptr) {
              if (board->GetPiece(forward.x + k, forward.y - k)->GetColor() ==
                  enemy_color) {
                  forward_push = {forward.y - k, forward.x + k};
                  possible_moves.push_back(forward_push);

              }break;
          }

      }
  }

  for (int k = 1; k <= 7; k++) {
      if (forward.x + k <= 7 && forward.y + k <= 7) {
          if (board->GetPiece(forward.x + k, forward.y + k) == nullptr) {
              forward_push = {forward.y + k, forward.x + k};
              possible_moves.push_back(forward_push);
          } else if (board->GetPiece(forward.x + k, forward.y + k) != nullptr) {
              if (board->GetPiece(forward.x + k, forward.y + k)->GetColor() ==
                  enemy_color) {
                  forward_push = {forward.y + k, forward.x + k};
                  possible_moves.push_back(forward_push);
              }break;
          }

      }
  }
  for (int k = 1; k <= 7; k++) {
      if (forward.x - k >= 0 && forward.y - k >= 0) {
          if (board->GetPiece(forward.x - k, forward.y - k) == nullptr) {
              forward_push = {forward.y - k, forward.x - k};
              possible_moves.push_back(forward_push);
          } else if (board->GetPiece(forward.x - k, forward.y - k) != nullptr) {
              if (board->GetPiece(forward.x - k, forward.y - k)->GetColor() ==
                  enemy_color) {
                  forward_push = {forward.y - k, forward.x - k};
                  possible_moves.push_back(forward_push);
              }break;
          }

      }
  }




  return possible_moves;
}
