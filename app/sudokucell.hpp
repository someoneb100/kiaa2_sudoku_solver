#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "board.hpp"

class SudokuCell : public QGraphicsRectItem {
public:
    SudokuCell(qreal x, qreal y, qreal width, qreal height, size_t i, size_t j, Board& board);

    static const int font_size = 18;

    void setNumber(int number, Qt::GlobalColor color = Qt::black);
    void clearNumber();
    void updateCell();
    void errorCell();

protected:
    void focusInEvent(QFocusEvent*) override;
    void focusOutEvent(QFocusEvent*) override;

private:
    const size_t m_i;
    const size_t m_j;
    Board& m_board;
    void updateBoard(int number);

    QGraphicsTextItem *m_text;
};
