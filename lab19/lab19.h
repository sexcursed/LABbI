#ifndef LAB19_H
#define LAB19_H

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <random>
#include <functional>
#include <memory>

// ============================================================
// ЗАДАЧА 1: КОД ХЭММИНГА
// ============================================================

int count_control_bits(int data_bits);
std::vector<int> insert_control_bits(const std::string& message);
void print_code(const std::vector<int>& code);
int detect_error(const std::vector<int>& code);
void print_syndrome_calculation(const std::vector<int>& code);
void task1_hamming();

// Дополнительные функции для задачи 1
std::string generate_random_binary_string(int length);
std::string read_binary_from_file(const std::string& filename);

// ============================================================
// ЗАДАЧА 2: КОД ХАФФМАНА
// ============================================================

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char c, int f);
    HuffmanNode(int f, HuffmanNode* l, HuffmanNode* r);
    bool isLeaf() const;
};

struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b);
};

void build_huffman_codes(HuffmanNode* root, std::string code, std::map<char, std::string>& codes);
void print_huffman_tree(HuffmanNode* root, int level);
void delete_huffman_tree(HuffmanNode* root);
void task2_huffman();

// Дополнительные функции для задачи 2
std::string generate_random_text(int length);
std::string read_text_from_file(const std::string& filename);

// ============================================================
// ЗАДАЧА 3: ШИФР ЦЕЗАРЯ
// ============================================================

std::string encrypt_caesar(const std::string& text, int shift);
std::string decrypt_caesar(const std::string& text, int shift);
void task3_caesar();

// Дополнительные функции для задачи 3
std::string generate_random_text_russian(int length);
std::string read_text_from_file_caesar(const std::string& filename);

// ============================================================
// ОБЩИЕ ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ============================================================

void clear_input_buffer();
int get_menu_choice(int min_val, int max_val);
int get_input_mode(const std::string& task_name);
int get_manual_input_method(const std::string& task_name);
std::string get_string_from_method(int method, const std::string& task_name, int length = 0);

#endif