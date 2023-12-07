#include "sudokucell.hpp"

#include <QPen>
#include <QFont>

SudokuCell::SudokuCell(qreal x, qreal y, qreal width, qreal height, size_t i, size_t j, Board& board)
    : QGraphicsRectItem(x, y, width, height)
    , m_i(i), m_j(j), m_board(board)
{
    setPen(QPen(Qt::black));
    setFlag(QGraphicsItem::ItemIsFocusable);

    m_text = new QGraphicsTextItem(this);

    QFont font = m_text->font();
    font.setPointSize(font_size);
    m_text->setFont(font);
    m_text->setDefaultTextColor(Qt::black);
}

void SudokuCell::setNumber(int number)
{
    m_text->setPlainText(QString::number(number));
    m_text->setPos(rect().x() + rect().width() / 3 - 1, rect().y() + rect().height() / 5 - 1);
    updateBoard(number);
}

void SudokuCell::focusInEvent(QFocusEvent *)
{
    setPen(QPen(Qt::yellow));
}

void SudokuCell::focusOutEvent(QFocusEvent *)
{
    setPen(QPen(Qt::black));
}

void SudokuCell::updateBoard(int number)
{
    m_board[m_i][m_j] = static_cast<Value>(number);
}

void SudokuCell::clearNumber()
{
    m_text->setPlainText("");
    updateBoard(0);
}
