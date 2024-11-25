#include "graphicboard.h"
#include <QGraphicsRectItem>
#include "logic.h"
#include <QMouseEvent>
#include <qmessagebox.h>
#include <QVBoxLayout>
#include <QPushButton>

GraphicBoard::GraphicBoard(QWidget *parent)
    : QGraphicsView(parent), scene_(new QGraphicsScene(this)), board_(nullptr)
{

    setupScene();
    setScene(scene_);

}

void GraphicBoard::setupScene()
{
    int boardSize = 8 * cell_size;
    scene_->setSceneRect(0, 0, boardSize, boardSize);

    drawBoard();
}

void GraphicBoard::drawBoard()
{
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QColor color = ((row + col) % 2 == 0) ? QColor(Qt::white) : QColor(Qt::gray);
            QGraphicsRectItem *cell = scene_->addRect(col * cell_size, row * cell_size, cell_size, cell_size, QPen(Qt::NoPen), QBrush(color));
            cell->setZValue(0);
        }
    }
    drawPieces();
}


void GraphicBoard::drawTypePiece(std::map<std::pair<int, int>, QGraphicsPixmapItem*> &piece_items, QString path, int row, int col)
{
    auto cell = std::make_pair(row, col);
    if (piece_items.find(cell) == piece_items.end()) {
        QPixmap pixmap_pawn(path);
        QPixmap scaled_pixmap_pawn = pixmap_pawn.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *pawn_item = scene_->addPixmap(scaled_pixmap_pawn);

        int x_pos = col * cell_size + (cell_size - scaled_pixmap_pawn.width()) / 2;
        int y_pos = row * cell_size + (cell_size - scaled_pixmap_pawn.height()) / 2;
        pawn_item->setPos(x_pos, y_pos);
        pawn_item->setZValue(1);
        piece_items[cell] = pawn_item;
    }
}


void GraphicBoard::drawPieces(bool update) {
    if (board_ == nullptr) return;


    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece* piece = board_->GetPiece(col, row);

            //проверка на повторную отрисовку фигур
            auto cell = std::make_pair(row, col);
            if (piece != nullptr) {
                if(update == true){
                    delete piece_items_[cell];
                    piece_items_.erase(cell);
                }

                if (dynamic_cast<Pawn*>(piece) && piece->GetColor() == WHITE) {
                    drawTypePiece(piece_items_,":/Image/w_pawn.svg", row, col);
                }

                if (dynamic_cast<Pawn*>(piece) && piece->GetColor() == BLACK) {
                    drawTypePiece(piece_items_,":/Image/b_pawn.svg", row, col);
                }

                if (dynamic_cast<Rook*>(piece) && piece->GetColor() == WHITE) {
                    drawTypePiece(piece_items_,":/Image/w_rook.svg", row, col);
                }
                if (dynamic_cast<Rook*>(piece) && piece->GetColor() == BLACK) {
                    drawTypePiece(piece_items_,":/Image/b_rook.svg", row, col);
                }
                if (dynamic_cast<Knight*>(piece) && piece->GetColor() == WHITE) {
                    drawTypePiece(piece_items_,":/Image/w_knight.svg", row, col);
                }
                if (dynamic_cast<Knight*>(piece) && piece->GetColor() == BLACK) {
                    drawTypePiece(piece_items_,":/Image/b_knight.svg", row, col);
                }
                if (dynamic_cast<Bishop*>(piece) && piece->GetColor() == WHITE) {
                    drawTypePiece(piece_items_,":/Image/w_bishop.svg", row, col);
                }
                if (dynamic_cast<Bishop*>(piece) && piece->GetColor() == BLACK) {
                    drawTypePiece(piece_items_,":/Image/b_bishop.svg", row, col);
                }
                if (dynamic_cast<Queen*>(piece) && piece->GetColor() == WHITE) {
                    drawTypePiece(piece_items_,":/Image/w_queen.svg", row, col);
                }
                if (dynamic_cast<Queen*>(piece) && piece->GetColor() == BLACK) {
                    drawTypePiece(piece_items_,":/Image/b_queen.svg", row, col);
                }
                if (dynamic_cast<King*>(piece) && piece->GetColor() == WHITE) {
                    drawTypePiece(piece_items_,":/Image/w_king.svg", row, col);
                }
                if (dynamic_cast<King*>(piece) && piece->GetColor() == BLACK) {
                    drawTypePiece(piece_items_,":/Image/b_king.svg", row, col);
                }

            } else {
                // Если ячейка пуста и содержит изображение, удаляем его
                if (piece_items_.find(cell) != piece_items_.end()) {
                    scene_->removeItem(piece_items_[cell]);
                    delete piece_items_[cell];
                    piece_items_.erase(cell);
                }
            }
        }
    }
}

void GraphicBoard::SetBoard(Board& board)
{
    board_ = &board;
    drawBoard();

    connect(board_, &Board::ChooseFigure, this, &GraphicBoard::ChooseTransform);
    connect(board_, &Board::UpdateFigure, this, &GraphicBoard::UpdateFigure);

}

void GraphicBoard::highlightPossibleMoves(const std::vector<Coordinates>& moves)
{
    for (const auto& move : moves) {
        if(move.y <= 7){
            QGraphicsRectItem* highlight = scene_->addRect(
                move.x * cell_size, move.y * cell_size, cell_size, cell_size,
                QPen(Qt::green), QBrush(QColor(0, 255, 0, 100))
                );
            highlight->setZValue(2);
            highlighted_cells_.push_back(highlight);
        }}
}

void GraphicBoard::clearHighlights()
{
    for (auto& cell : highlighted_cells_) {
        scene_->removeItem(cell);
    }
    highlighted_cells_.clear();
}





void GraphicBoard::mousePressEvent(QMouseEvent* event) {
    QPointF scene_position = mapToScene(event->pos());
    int x = static_cast<int>(scene_position.x()) / cell_size;
    int y = static_cast<int>(scene_position.y()) / cell_size;
    qDebug() << "signal y " << y << " x " << x;

    if (x >= 0 && x < board_size && y >= 0 && y < board_size) {
        emit cellClicked(x, y);
    }
}

void GraphicBoard::ChooseTransform(Piece* pawn){
    auto *promotion_dialog = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    QPushButton *queen_button = new QPushButton("Превратить в ферзя");
    QPushButton *rook_button = new QPushButton("Превратить в ладью");
    QPushButton *bishop_button = new QPushButton("Превратить в слона");
    QPushButton *knight_button = new QPushButton("Превратить в коня");

    layout->addWidget(queen_button);
    layout->addWidget(rook_button);
    layout->addWidget(bishop_button);
    layout->addWidget(knight_button);

    promotion_dialog->setLayout(layout);
    promotion_dialog->setWindowTitle("Трансформация пешки");
    promotion_dialog->setWindowFlags(promotion_dialog->windowFlags() & ~Qt::WindowCloseButtonHint);
    promotion_dialog->setWindowModality(Qt::ApplicationModal);
    promotion_dialog->show();

    int chose;

    connect(queen_button, &QPushButton::clicked, [this, pawn, promotion_dialog, &chose]() {
        emit transformationChosen(QUEEN, pawn);
        promotion_dialog->close();
    });
    connect(rook_button, &QPushButton::clicked, [this, pawn, promotion_dialog, &chose]() {
        emit transformationChosen(ROOK, pawn);
        promotion_dialog->close();

    });
    connect(bishop_button, &QPushButton::clicked, [this, pawn, promotion_dialog, &chose]() {
        emit transformationChosen(BISHOP, pawn);
        promotion_dialog->close();
    });
    connect(knight_button, &QPushButton::clicked, [this, pawn, promotion_dialog, &chose]() {
        emit transformationChosen(KNIGHT, pawn);
        promotion_dialog->close();
    });
}

void GraphicBoard::UpdateFigure(){
    drawPieces(true);
}
