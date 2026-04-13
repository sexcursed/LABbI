#include "node.h"
Node::Node(Node* l, Node* r, int val) : left(l), right(r), value(val){};

Node* Node::get_left() const{
    return left;
}

Node* Node::get_left() const{
    return right;
}

Node* Node::get_value() const{
    return value;
}

void Node::set_left(Node* p){
    left = p;
}

void Node::set_right(Node* p){
    right = p;
}

void Node::has_left() const{
    return left != nullptr;
}

void Node::has_right() const{
    return right != nullptr;
}

void Node::is_leaf() const{
    return (!has_left() and !has_right());
}

