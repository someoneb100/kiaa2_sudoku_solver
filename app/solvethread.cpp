#include "solvethread.hpp"
#include "solver.hpp"

SolveThread::SolveThread(const Board& board, QObject* parent)
    : QThread(parent), m_board(board)
{}

void SolveThread::run()
{
    SudokuSolver solver(m_board);
    auto result = solver.solution(false);
    QSharedDataPointer<Result> res_ptr(new Result(std::move(result)));
    emit solution(res_ptr);
}
