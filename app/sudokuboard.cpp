#include "sudokuboard.hpp"
#include "sudokucell.hpp"

#include <QVBoxLayout>
#include <QGraphicsProxyWidget>

SudokuBoard::SudokuBoard()
{
    setWindowTitle("Sudoku Solver");
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);

    const auto padding = 5;
    const auto size = gridSize * cellSize + padding;

    initializeGrid();
    initializeUI();
}

void SudokuBoard::keyPressEvent(QKeyEvent *event)
{
    QGraphicsItem *selectedItem = m_scene->focusItem();
    SudokuCell *cell = qgraphicsitem_cast<SudokuCell *>(selectedItem);
    if (cell && event->key() >= Qt::Key_1 && event->key() <= Qt::Key_9) {
        int number = event->key() - Qt::Key_0;
        cell->setNumber(number);
    } else if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_0) {
        cell->clearNumber();
    }
}

void SudokuBoard::solveButtonClicked()
{

}

void SudokuBoard::initializeGrid()
{
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            SudokuCell *cell = new SudokuCell(i * cellSize, j * cellSize, cellSize, cellSize, i, j, m_board);
            m_scene->addItem(cell);
        }
    }
}

void SudokuBoard::initializeUI()
{
    QGraphicsProxyWidget* proxyWidget = new QGraphicsProxyWidget();

    QWidget* widget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(widget);

    m_button = new QPushButton("Solve");
    connect(m_button, &QPushButton::clicked, this, &SudokuBoard::solveButtonClicked);

    m_label = new QLabel;

    // Add the button and label to the layout
    layout->addWidget(m_button, 0, Qt::AlignBottom | Qt::AlignLeft);
    layout->addWidget(m_label, 0, Qt::AlignBottom | Qt::AlignLeft);

    proxyWidget->setWidget(widget);
    const auto padding = 5;
    proxyWidget->setPos(0, sizeHint().height() + padding); // Adjust the position as needed
    m_scene->addItem(proxyWidget);

    setMinimumSize(sizeHint().width() + padding, sizeHint().height() + padding);
}

