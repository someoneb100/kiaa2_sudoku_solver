#include "solver.hpp"

init_matrix_t SudokuSolver::emptyMatrix()
{
    const size_t totalOptions = Board::size * Board::size * Board::size;
    const size_t totalConstraints = Board::size * Board::size * 4;
    init_matrix_t sudokuMatrix(totalOptions, std::vector<bool>(totalConstraints, false));

    for (size_t i = 0; i < Board::size; ++i) {
        for (size_t j = 0; j < Board::size; ++j) {
            for (size_t v = 0; v != Board::size; ++v) {
                const size_t row = fieldToRow(i, j, static_cast<Value>(v+1));
                const size_t offset = Board::size * Board::size;
                const size_t valueConstraint = i * Board::size + j;
                const size_t rowConstraint =  i * Board::size + v;
                const size_t columnConstraint = j * Board::size + v;
                const size_t blockConstraint = (i / 3 * 3 + j / 3) * Board::size + v;
                sudokuMatrix[row][0*offset + valueConstraint] = true;
                sudokuMatrix[row][1*offset + rowConstraint] = true;
                sudokuMatrix[row][2*offset + columnConstraint] = true;
                sudokuMatrix[row][3*offset + blockConstraint] = true;
            }
        }
    }

    return sudokuMatrix;
}

SudokuSolver::SudokuSolver()
    : m_dlx(std::make_unique<DLX>(SudokuSolver::getEmptyMatrix()))
{}

SudokuSolver::SudokuSolver(const Board& other)
    : SudokuSolver()
{
    for(size_t i = 0; i != Board::size; ++i){
        for(size_t j = 0; j != Board::size; ++j){
            auto v = other[i][j];
            if(v != Value::EMPTY){
                m_dlx->add(fieldToRow(i, j, v));
            }
        }
    }
}

std::vector<Board> SudokuSolver::solution()
{
    solve();
    return *m_solution;
}

init_matrix_t SudokuSolver::getEmptyMatrix()
{
    static init_matrix_t matrix = SudokuSolver::emptyMatrix();
    return matrix;
}

size_t SudokuSolver::fieldToRow(size_t i, size_t j, Value v)
{
    if(v == Value::EMPTY){
        throw std::invalid_argument("Can't convert Value::EMPTY to row");
    }
    return i * Board::size * Board::size + j * Board::size + static_cast<size_t>(v) - 1;
}

std::pair<std::pair<size_t, size_t>, Value> SudokuSolver::rowToField(size_t row)
{
    size_t i = row / Board::size / Board::size, j = row / Board::size % Board::size;
    Value v = static_cast<Value>(row % Board::size + 1);
    return {{i, j}, v};
}

void SudokuSolver::solve()
{
    if(m_solution) return;
    auto results = m_dlx->search();
    std::vector<Board> solution;
    solution.reserve(results.size());
    for(auto& result : results){
        Board b;
        for(auto row : result){
            auto [pos, v] = rowToField(row);
            b[pos.first][pos.second] = v;
        }
        solution.emplace_back(b);
    }
    m_solution = std::make_unique<std::vector<Board>>(solution);
}
