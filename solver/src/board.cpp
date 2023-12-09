#include "board.hpp"
#include <exception>
#include <algorithm>

Board::Board()
    : board_t(Board::size, row_t(Board::size, Value::EMPTY))
{}

Board::Board(Board&& other)
    : board_t(std::move(other))
{
    other = Board::emptyBoard();
}

Board::Board(const board_t& other)
    : board_t(other)
{
    checkBoardT();
}

Board::Board(const std::vector<std::vector<size_t>>& other)
    : Board()
{
    for(size_t i = 0; i != Board::size; ++i){
        for(size_t j = 0; j != Board::size; ++j){
            auto v = static_cast<Value>(other[i][j]);
            if(v != Value::EMPTY) (*this)[i][j] = v;
        }
    }
}

Board::Board(board_t&& other)
    : board_t(std::move(other))
{
    checkBoardT();
}

Board Board::emptyBoard()
{
    static Board board;
    return board;
}

bool Board::empty() const
{
    return *this == Board::emptyBoard();
}

Board &Board::operator=(const Board &other)
{
    for(size_t i = 0; i != Board::size; ++i){
        for(size_t j = 0; j != Board::size; ++j){
            (*this)[i][j] = other[i][j];
        }
    }
    return *this;
}

void Board::checkBoardT() const
{
    if(board_t::size() != Board::size || std::any_of(cbegin(), cend(), [](auto& row){return row.size() != Board::size;})){
        throw std::invalid_argument("Bad board_t size: must be a 9x9 matrix");
    }
}

bool Board::valid() const
{
    // Check each row
    for (const auto& row : *this) {
        if (!isSubsetValid(row)) {
            return false;
        }
    }

    // Check each column
    for (size_t col = 0; col < Board::size; ++col) {
        row_t column;
        for (size_t row = 0; row < Board::size; ++row) {
            column.push_back((*this)[row][col]);
        }
        if (!isSubsetValid(column)) {
            return false;
        }
    }

    // Check each 3x3 block
    for (size_t blockRow = 0; blockRow < 3; ++blockRow) {
        for (size_t blockCol = 0; blockCol < 3; ++blockCol) {
            row_t block;
            for (size_t row = 0; row < 3; ++row) {
                for (size_t col = 0; col < 3; ++col) {
                    block.push_back((*this)[blockRow * 3 + row][blockCol * 3 + col]);
                }
            }
            if (!isSubsetValid(block)) {
                return false;
            }
        }
    }

    return true;
}

bool Board::isSubsetValid(const row_t& subset) const
{
    std::vector<bool> seen(Board::size, false);

    for (const auto& value : subset) {
        if (value != Value::EMPTY) {
            size_t index = static_cast<size_t>(value) - 1;
            if (seen[index]) {
                return false;  // Duplicate value in subset
            }
            seen[index] = true;
        }
    }

    return true;
}
