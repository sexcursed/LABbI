#pragma once
#include "search_tree.h"
#include "binary_tree.h"
#include <vector>
#include <string>

class MainMenu {
private:
    static void clear_input();
    static void wait_for_enter();
    
    static void handle_manual_fill(Search_tree& tree);
    static void handle_random_fill(Search_tree& tree);
    static void handle_file_fill(Search_tree& tree);
    
    static void handle_manual_fill_binary(BinaryTree& tree);
    static void handle_random_fill_binary(BinaryTree& tree);
    static void handle_file_fill_binary(BinaryTree& tree);
    
    static void task1_handler();
    static void task2_handler();
    static void task3_handler();
    
    static int get_fill_method_choice(const std::string& prompt);
    
public:
    static void run();
};