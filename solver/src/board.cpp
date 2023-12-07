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
    static_cast<board_t>(*this) = static_cast<board_t>(other);
    return *this;
}

void Board::checkBoardT() const
{
    if(board_t::size() != Board::size || std::any_of(cbegin(), cend(), [](auto& row){return row.size() != Board::size;})){
        throw std::invalid_argument("Bad board_t size: must be a 9x9 matrix");
    }
}
