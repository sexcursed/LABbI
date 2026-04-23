#pragma once
#include "node.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class BinaryTree {
private:
    Node* root;
    
    void clear_rec(Node* p);
    void print_tree_rec(Node* p, int level) const;
    void inorder(Node* p, std::vector<int>& result) const;
    void preorder(Node* p, std::vector<int>& result) const;
    void postorder(Node* p, std::vector<int>& result) const;
    

    
public:
    BinaryTree(Node* r = nullptr);
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();
    
    BinaryTree& operator=(const BinaryTree& other);
    
    void insert(int v);
    void clear();
    
    void print_ascending() const;
    void print_descending() const;
    Node* get_root() const;
    
    bool is_empty() const;
    void print_tree() const;
    
    void fill_manual(int N);
    void fill_random(int N, int min_val, int max_val);
    void fill_from_file(std::string filename);
    
    std::vector<int> to_vector() const;
    
    void print_preorder() const;
    void print_postorder() const;
    
    void build_expression_tree();
    bool is_op_coded(int x);
    int evaluate_subtree(Node* node);
    void replace_multi(Node* node);
};