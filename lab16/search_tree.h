#include "node.h"
#include <vector>

class Search_tree{
    private:
        Node* root;

        Node* insert_rec(Node* p, int v);
        void clear_rec(Node* p = root);

        Node* get_root() const;
        void set_root(Node* p);

        void print_tree_rec(Node* p, int level) const;
        void inorder(Node* p, std::vector<int>& result) const;
        void reverse_inorder(Node* p, std::vector<int>& result) const;

    public:
        Search_tree(Node* r = nullptr);
        ~Search_tree();

        void insert(int v);
        void clear();

        void print_ascending() const;
        void print_descending() const;

        bool is_empty() const;
        void print_tree() const;
};