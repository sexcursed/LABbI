#pragma once
#include "node.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

class BinaryTree {
private:
    Node* root;

    void clear_rec(Node* p);
    void print_tree_rec(Node* p, int level) const;
    
    // Для задания 1 (BST - inorder)
    void inorder_convert(Node* node, Node*& prev, Node*& head);

public:
    BinaryTree(Node* r = nullptr);
    ~BinaryTree();

    // Для задания 1 (BST - вставка по правилам дерева поиска)
    void insert_bst(int v);
    
    // Для задания 2 (обычное дерево - случайная вставка)
    void insert_random(int v);
    
    void clear();
    bool is_empty() const;
    void print_tree() const;
    
    void fill_manual_bst(int N);      // Для задания 1
    void fill_manual_random(int N);   // Для задания 2
    void fill_random(int N, int min_val, int max_val);
    
    // Задание 1
    void convert_to_doubly_linked_list_inplace();
    void print_as_list() const;
    
    // Задание 2
    class PostorderIterator {
    private:
        Node* current;
        
        Node* find_first(Node* root);
        Node* get_next_postorder();
        
    public:
        PostorderIterator(Node* root);
        bool has_next();
        int next();
    };
    
    PostorderIterator get_postorder_iterator();
};