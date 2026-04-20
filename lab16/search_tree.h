#pragma once
#include "node.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

class Search_tree{
    private:
        Node* root;

        Node* insert_rec(Node* p, int v);
        void clear_rec(Node* p);

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
        void print_inline(Node* p) const;
        Node* get_root() const;

        bool is_empty() const;
        void print_tree() const;

        void fill_manual(int N);
        void fill_random(int N, int min_val, int max_val);
        void fill_from_file(std::string filename);

        std::vector<int> to_vector() const;
};