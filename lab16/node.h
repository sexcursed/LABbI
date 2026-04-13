
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

        Node get_left() const;
        Node get_right() const;
        Node get_value() const;

        void has_left() const;
        void has_right() const;
        void is_leaf() const;

        Node insert(Node* p, int v);
        void clear();
};
