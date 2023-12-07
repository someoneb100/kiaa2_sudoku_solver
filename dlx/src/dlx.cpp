#include "dlx.hpp"

DLX::DLX(const init_matrix_t& init_matrix)
    : m_row_size(init_matrix.size()), m_column_size(init_matrix[0].size())
    , m_header(), m_columns(std::vector<ColumnNode>(m_column_size))
    , m_nodes(m_row_size, std::vector<Node>(m_column_size))
{
    link_nodes(init_matrix);
    link_columns(init_matrix);
}

void DLX::link_nodes(const init_matrix_t& init_matrix)
{
    for(size_t i = 0; i != m_row_size; ++i){
        for(size_t j = 0; j != m_column_size; ++j){
            if(init_matrix[i][j]){
                auto& node = m_nodes[i][j];
                node.m_column = &m_columns[j];
                node.m_row_id = i;
                node.m_col_id = j;
                node.m_column->m_count += 1;
                
                node.m_left = get_left(init_matrix, i, j);
                node.m_right = get_right(init_matrix, i, j);
                node.m_up = get_up(init_matrix, i, j);
                node.m_down = get_down(init_matrix, i, j);
            }
        }
    }
}

matrix_t DLX::search()
{
    solution_t current_solution;
    matrix_t solutions;
    search_help(solutions, current_solution, 0);
    solutions.shrink_to_fit();
    return solutions;
}

void DLX::add(size_t row_id)
{
    for(auto col = m_header.m_right; col != &m_header; col = col->m_right){
        for(auto row = col->m_down; row != col; row = row->m_down){
            if(row->m_row_id == row_id){
                for(auto row = col->m_down; row != col; row = row->m_down){
                    if(row->m_row_id != row_id){
                        row->row_cover();
                    }
                }
            }
        }
    }
}

void DLX::search_help(matrix_t& solutions, solution_t& current_solution, size_t depth)
{
    if(m_header.done()){
        current_solution.shrink_to_fit();
        solutions.emplace_back(current_solution);
        return;
    }
    
    auto column = m_header.min();
    column->cover();
    for(auto row = column->m_down; row != column; row = row->m_down){
        current_solution.push_back(row->m_row_id);
        for(auto right = row->m_right; right != row; right = right->m_right){
            right->cover();
        }

        search_help(solutions, current_solution, depth+1);

        current_solution.pop_back();
        for(auto left = row->m_left; left != row; left = left->m_left){
            left->uncover();
        }
    }
    column->uncover();
}


void DLX::link_columns(const init_matrix_t& init_matrix)
{
    ColumnNode* prev = &m_header;
    for(size_t j = 0; j < m_column_size; ++j){
        if(m_columns[j].m_count){
            prev->m_right = &m_columns[j];
            m_columns[j].m_left = prev;

            prev = &m_columns[j];

            for(size_t i = 0; i < m_row_size; ++i){
                if(init_matrix[i][j]){
                    if(m_columns[j].m_down == nullptr) m_columns[j].m_down = &m_nodes[i][j];
                    m_columns[j].m_up = &m_nodes[i][j];
                }
            }
        }
    }
    prev->m_right = &m_header;
    m_header.m_left = prev;
}

Node *DLX::get_left(const init_matrix_t& init_matrix, size_t i, size_t j)
{
    size_t b = j;
    do{b = (b ? b-1 : m_column_size-1);}
    while(!init_matrix[i][b]);
    return &m_nodes[i][b];
}

Node *DLX::get_right(const init_matrix_t& init_matrix, size_t i, size_t j)
{
    size_t b = j;
    do{b = (b+1) % m_column_size;}
    while(!init_matrix[i][b]);
    return &m_nodes[i][b];
}

Node *DLX::get_up(const init_matrix_t& init_matrix, size_t i, size_t j)
{
    size_t a = i;
    do{a = (a ? a-1 : m_row_size);}
    while(a != m_row_size && !init_matrix[a][j]);
    return a == m_row_size ? &m_columns[j] : &m_nodes[a][j];
}

Node *DLX::get_down(const init_matrix_t& init_matrix, size_t i, size_t j)
{
    for(size_t a = i+1; a != m_row_size; ++a){
        if(init_matrix[a][j]) return &m_nodes[a][j];
    }
    return &m_columns[j];
}
