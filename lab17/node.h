#pragma once
class Node{
    private:
        Node* left;
        Node* right;
        int value;

    public:
        Node(Node* l = nullptr, Node* r = nullptr, int val = 0);

        void set_left(Node* p);
        void set_right(Node* p);
        void set_value(int n);

        Node* get_left() const;
        Node* get_right() const;
        int get_value() const;

        bool has_left() const;
        bool has_right() const;
        bool is_leaf() const;

        Node* insert(Node* p, int v);
        void clear();
};
