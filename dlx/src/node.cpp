#include "node.hpp"

Node::Node(ColumnNode* column) 
    : m_column(column)
{}

void Node::horizontal_cover() 
{
    m_left->m_right = m_right;
    m_right->m_left = m_left;
}

void Node::vertical_cover() 
{
    m_up->m_down = m_down;
    m_down->m_up = m_up;
    m_column->m_count -=1;
}

void Node::cover()
{
    m_column->cover();
}

void Node::row_cover()
{
    auto elem = this;
    do{
        elem->vertical_cover();
        elem = elem->m_right;
    } while (elem != this);
}

void Node::horizontal_uncover()
{
    m_left->m_right = this;
    m_right->m_left = this;
    m_column->m_count +=1;
}

void Node::vertical_uncover()
{
    m_up->m_down = this;
    m_down->m_up = this;
}

void Node::uncover()
{
    m_column->uncover();
}

ColumnNode::ColumnNode()
    : Node(this)
{}

void ColumnNode::cover()
{
    horizontal_cover();
    for(auto row = m_down; row != this; row = row->m_down){
        for(
            auto right = row->m_right; right != row; right = right->m_right){
            right->vertical_cover();
        }
    }
}

void ColumnNode::uncover()
{
    for(auto row = m_up; row != this; row = row->m_up){
        for(auto left = row->m_left; left != row; left = left->m_left){
            left->vertical_uncover();
        }
    }
    horizontal_uncover();
}

ColumnNode* HeaderNode::min() const
{
    if(done()) return nullptr;

    ColumnNode* min = nullptr;
    for(
        ColumnNode* current = static_cast<ColumnNode*>(m_right);
        current != this;
        current = static_cast<ColumnNode*>(current->m_right)
    ){
        if(current->m_count == 0) return current;
        if(min == nullptr || *current < *min) min = current;
    }

    return min;
}
