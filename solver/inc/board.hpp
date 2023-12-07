#pragma once

#include <vector>

enum class Value {
    EMPTY = 0,
    ONE, TWO, THREE,
    FOUR, FIVE, SIX,
    SEVEN, EIGHT, NINE
};

using row_t = std::vector<Value>;
using board_t = std::vector<row_t>;

class Board : public board_t {
public:
    Board();
    Board(const Board&) = default;
    Board(const board_t&);
    Board(const std::vector<std::vector<size_t>>&);
    Board(Board&&);
    Board(board_t&&);

    static const size_t size = 9;
    static Board emptyBoard();

    bool empty() const;
    bool valid() const;
    Board& operator=(const Board&);
private:
    bool isSubsetValid(const row_t& subset) const;
    void checkBoardT() const;
};
