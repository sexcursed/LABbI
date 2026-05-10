#pragma once
#include "node.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <sstream>
#include <functional>

class BinaryTree {
private:
    Node* root;
    
    void clear_rec(Node* p);
    void print_tree_rec(Node* p, int level) const;
    void inorder(Node* p, std::vector<int>& result) const;
    void preorder(Node* p, std::vector<int>& result) const;
    void postorder(Node* p, std::vector<int>& result) const;
    
    bool is_operator_char(char c);
    int get_precedence(char c);
    int apply_operator(int op, int left, int right);
    std::vector<std::string> infix_to_postfix(const std::string& expr);
    Node* build_from_postfix(const std::vector<std::string>& postfix);
    bool subtree_has_variable(Node* node);
    int evaluate_subtree_int(Node* node, int x_val);
    Node* replace_const_subtrees(Node* node, int x_val);
    void print_tree_sideways(Node* node, int level, std::ofstream& out) const;
    Node* build_from_prefix(const std::vector<std::string>& tokens, size_t& index);
    
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
    void build_expression_tree_from_file(std::string filename);
    bool is_op_coded(int x) const;
    int evaluate_subtree(Node* node);
    void replace_multi(Node* node);
    
    void build_from_infix(const std::string& expr);
    int evaluate_with_x(int x_val);
    void replace_constants(int x_val);
    void print_sideways(const std::string& filename) const;
    
    void print_expression_tree() const;
    void print_tree_coded() const;
    void print_tree_normal() const;

    void build_expression_tree_from_file_prefix(std::string filename);
    void replace_subtrees_range_0_9();
    Node* replace_subtrees_range_0_9_rec(Node* node);
};