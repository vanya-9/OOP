#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "boardcontroller.h"
#include "graphicboard.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  Board* board = new Board();
  board->SetDefault();

  GraphicBoard* graphic_board = new GraphicBoard();
  ui->setupUi(this);
  connect(graphic_board, &GraphicBoard::transformationChosen, board,
          &Board::onTransformationChosen);

  graphic_board->SetBoard(*board);

  BoardController* controller = new BoardController(board, graphic_board, this);

  setCentralWidget(graphic_board);
}

MainWindow::~MainWindow() {
  delete ui;
}
