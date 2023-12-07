#include <QApplication>
#include "sudokuboard.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon/sudoku.png"));
    SudokuBoard sudokuBoard;
    sudokuBoard.show();

    return a.exec();
}
