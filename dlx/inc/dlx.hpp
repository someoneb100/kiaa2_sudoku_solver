#pragma once

#include "node.hpp"
#include <vector>

using init_matrix_t = std::vector<std::vector<bool>>;
using solution_t = std::vector<size_t>;
using matrix_t = std::vector<solution_t>;

class DLX {
public:
    DLX(const init_matrix_t&);

    const size_t m_row_size;
    const size_t m_column_size;

    matrix_t search(bool find_all = true);
    void add(size_t row_id);
private:
    bool search_help(matrix_t& solutions, solution_t& current_solution, bool find_all);

    HeaderNode m_header;
    std::vector<ColumnNode> m_columns;
    std::vector<std::vector<Node>> m_nodes;

    //init
    void link_columns(const init_matrix_t&);
    void link_nodes(const init_matrix_t&);
    Node* get_left(const init_matrix_t&, size_t i, size_t j);
    Node* get_right(const init_matrix_t&, size_t i, size_t j);
    Node* get_up(const init_matrix_t&, size_t i, size_t j);
    Node* get_down(const init_matrix_t&, size_t i, size_t j);
};
