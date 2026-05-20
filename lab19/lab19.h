#ifndef LAB19_H
#define LAB19_H

#include <string>
#include <vector>
#include <map>
#include <queue>

// ============================================================
// ЗАДАЧА 1: КОД ХЭММИНГА
// ============================================================

int count_control_bits(int data_bits);
std::vector<int> insert_control_bits(const std::string& message);
void print_code(const std::vector<int>& code);
int detect_error(const std::vector<int>& code);
void print_syndrome_calculation(const std::vector<int>& code);
void task1_hamming();

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

// ============================================================
// ЗАДАЧА 3: ШИФР ЦЕЗАРЯ
// ============================================================

std::string encrypt_caesar(const std::string& text, int shift);
std::string decrypt_caesar(const std::string& text, int shift);
void task3_caesar();

#endif