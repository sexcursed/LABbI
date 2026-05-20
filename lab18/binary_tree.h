// binary_tree.h
#pragma once
#include "node.h"
#include <vector>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <set>
#include <functional>

class BinaryTree {
private:
    Node* root;

    void clear_rec(Node* p);
    void print_tree_rec(Node* p, int level) const;
    void inorder(Node* p, std::vector<int>& result) const;

    std::string serialize(Node* node);
    bool are_equal(Node* a, Node* b);
    void collect_all_subtrees(Node* node, std::vector<Node*>& all_subtrees);
    bool is_ancestor_of(Node* ancestor, Node* descendant);

public:
    BinaryTree(Node* r = nullptr);
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();

    BinaryTree& operator=(const BinaryTree& other);

    void insert(int v);
    void clear();
    bool is_empty() const;
    Node* get_root() const;
    void print_tree() const;

    void fill_manual(int N);
    void fill_random(int N, int min_val, int max_val);
    std::vector<int> to_vector() const;

    Node* convert_to_doubly_linked_list();
    Node* build_balanced_from_list(Node*& head, int start, int end);
    void convert_from_doubly_linked_list(Node* head);
    void print_doubly_linked_list(Node* head) const;

    class PostorderIterator {
    private:
        std::stack<Node*> st1;
        std::stack<Node*> st2;
        
    public:
        PostorderIterator(Node* root);
        bool has_next();
        int next();
    };
    
    PostorderIterator get_postorder_iterator();

    void remove_duplicate_subtrees();
    void remove_duplicate_subtrees_max();
};