#include "node.h"

Node::Node(Node* l, Node* r, Node* p, int val) 
    : left(l), right(r), parent(p), value(val) {}

Node* Node::get_left() const { return left; }
Node* Node::get_right() const { return right; }
Node* Node::get_parent() const { return parent; }
int Node::get_value() const { return value; }

void Node::set_value(int n) { value = n; }

void Node::set_left(Node* p) { 
    left = p; 
    if (p) p->set_parent(this); 
}

void Node::set_right(Node* p) { 
    right = p; 
    if (p) p->set_parent(this); 
}

void Node::set_parent(Node* p) { parent = p; }

bool Node::has_left() const { return left != nullptr; }
bool Node::has_right() const { return right != nullptr; }
bool Node::is_leaf() const { return (!has_left() && !has_right()); }