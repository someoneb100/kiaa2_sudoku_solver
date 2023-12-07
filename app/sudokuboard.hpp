#pragma once

#include "board.hpp"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPushButton>
#include <QLabel>

class SudokuBoard : public QGraphicsView {
    Q_OBJECT
public:
    SudokuBoard();

    void keyPressEvent(QKeyEvent *event) override;

    static const int cellSize = 50;
    static const int gridSize = 9;

private slots:
    void solveButtonClicked();

private:
    QGraphicsScene *m_scene;
    Board m_board;
    QPushButton* m_button;
    QLabel* m_label;

    void initializeGrid();
    void initializeUI();
};
