#pragma once

#include "dlx.hpp"
#include "board.hpp"
#include <vector>
#include <memory>


class SudokuSolver {
public:
    SudokuSolver();
    SudokuSolver(const Board&);

    std::vector<Board> solution();
private:
    static init_matrix_t emptyMatrix();
    static init_matrix_t getEmptyMatrix();
    static size_t fieldToRow(size_t i, size_t j, Value v);
    static std::pair<std::pair<size_t, size_t>, Value> rowToField(size_t row);
    void solve();

    std::unique_ptr<DLX> m_dlx;
    std::unique_ptr<std::vector<Board>> m_solution;
};
