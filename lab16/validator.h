
#pragma once
#include "node.h"
#include <vector>
#include <string>

class TreeValidator {
public:
    static bool has_no_cycles(Node* root);
    static bool all_nodes_reachable(Node* root);
    static bool no_dangling_pointers(Node* root);
    static bool no_duplicate_nodes(Node* root);
    static bool no_self_pointers(Node* root);
    static bool is_valid_tree(Node* root);
    static void print_validation_results(Node* root, const std::string& tree_name);
    static int get_node_count(Node* root);
    static int get_height(Node* root);
    
    static bool validate_number_input(const std::string& input, int& result);
    static bool validate_file_numbers(const std::string& filename, std::vector<int>& numbers);

private:
    static bool detect_cycle(Node* node, std::vector<Node*>& visited, std::vector<Node*>& stack);
    static void collect_nodes(Node* node, std::vector<Node*>& nodes);
    static bool check_self_pointers(Node* node);
    static bool check_dangling_pointers(Node* node);
    static int get_height_rec(Node* node);
    static int get_node_count_rec(Node* node);
    static bool is_number(const std::string& str);
};