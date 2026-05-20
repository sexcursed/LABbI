#include "node.h"

Node::Node(Node* l, Node* r, int val) : left(l), right(r), value(val) {}

Node* Node::get_left() const {
    return left;
}

Node* Node::get_right() const {
    return right;
}

int Node::get_value() const {
    return value;
}

void Node::set_value(int n) {
    value = n;
}

void Node::set_left(Node* p) {
    left = p;
}

void Node::set_right(Node* p) {
    right = p;
}

bool Node::has_left() const {
    return left != nullptr;
}

bool Node::has_right() const {
    return right != nullptr;
}

bool Node::is_leaf() const {
    return (!has_left() && !has_right());
}