#pragma once

#include <cstddef>

class ColumnNode;

class Node
{
public:
    Node(ColumnNode* column = nullptr);

    void horizontal_cover();
    void vertical_cover();
    void cover();
    void row_cover();
    void horizontal_uncover();
    void vertical_uncover();
    void uncover();

	Node* m_left = nullptr;
	Node* m_right = nullptr;
	Node* m_up = nullptr;
	Node* m_down = nullptr;
    size_t m_row_id = 0;
    size_t m_col_id = 0;
    ColumnNode* m_column = nullptr;
};

class ColumnNode : public Node
{
public:
    ColumnNode();
    size_t m_count = 0;

    inline bool operator<(const ColumnNode& other) const {return m_count < other.m_count;}
    inline bool operator>(const ColumnNode& other) const {return m_count > other.m_count;}
    
    void cover();
    void uncover();
private:
    using Node::m_row_id;
    using Node::m_col_id;
};

class HeaderNode : public ColumnNode
{
public:
    HeaderNode() = default;

    inline bool done() const {return m_right == this;}
    ColumnNode* min() const;
private:
    using ColumnNode::m_count;
    using ColumnNode::m_down;
    using ColumnNode::m_up;
    using ColumnNode::horizontal_cover;
    using ColumnNode::vertical_cover;
    using ColumnNode::cover;
    using ColumnNode::horizontal_uncover;
    using ColumnNode::vertical_uncover;
    using ColumnNode::uncover;
};
