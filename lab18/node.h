#pragma once

class Node {
private:
    Node* left;
    Node* right;
    Node* parent;
    int value;

public:
    Node(Node* l = nullptr, Node* r = nullptr, Node* p = nullptr, int val = 0);

    void set_left(Node* p);
    void set_right(Node* p);
    void set_parent(Node* p);
    void set_value(int n);

    Node* get_left() const;
    Node* get_right() const;
    Node* get_parent() const;
    int get_value() const;

    bool has_left() const;
    bool has_right() const;
    bool is_leaf() const;
};