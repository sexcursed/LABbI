#include "lab19.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <map>
#include <cctype>

// ============================================================
// ЗАДАЧА 1: КОД ХЭММИНГА
// ============================================================

int count_control_bits(int data_bits) {
    int r = 0;
    while (pow(2, r) < data_bits + r + 1) {
        r++;
    }
    return r;
}

std::vector<int> insert_control_bits(const std::string& message) {
    int m = message.length();
    int r = count_control_bits(m);
    int total = m + r;
    
    std::vector<int> code(total + 1, 0);
    
    int data_pos = 0;
    for (int i = 1; i <= total; i++) {
        if ((i & (i - 1)) == 0) {
            continue;
        }
        code[i] = message[data_pos++] - '0';
    }
    
    for (int i = 0; i < r; i++) {
        int control_pos = pow(2, i);
        int parity = 0;
        
        for (int j = control_pos; j <= total; j++) {
            if (j & control_pos) {
                parity ^= code[j];
            }
        }
        
        code[control_pos] = parity;
    }
    
    return code;
}

void print_code(const std::vector<int>& code) {
    std::cout << "\nИтоговый код Хэмминга:\n";
    for (size_t i = 1; i < code.size(); i++) {
        if ((i & (i - 1)) == 0) {
            std::cout << "P" << i << "=" << code[i] << " ";
        } else {
            std::cout << "D" << i << "=" << code[i] << " ";
        }
        if (i % 8 == 0) std::cout << "\n";
    }
    std::cout << "\n\nПоследовательность битов: ";
    for (size_t i = 1; i < code.size(); i++) {
        std::cout << code[i];
    }
    std::cout << std::endl;
}

int detect_error(const std::vector<int>& code) {
    int total = code.size() - 1;
    int r = 0;
    while (pow(2, r) < total) {
        r++;
    }
    
    int syndrome = 0;
    
    for (int i = 0; i < r; i++) {
        int control_pos = pow(2, i);
        int parity = 0;
        
        for (int j = control_pos; j <= total; j++) {
            if (j & control_pos) {
                parity ^= code[j];
            }
        }
        
        if (parity != 0) {
            syndrome += control_pos;
        }
    }
    
    return syndrome;
}

void print_syndrome_calculation(const std::vector<int>& code) {
    int total = code.size() - 1;
    int r = 0;
    while (pow(2, r) < total) {
        r++;
    }
    
    std::cout << "\n=== Расчёт синдрома ===\n";
    
    for (int i = 0; i < r; i++) {
        int control_pos = pow(2, i);
        int parity = 0;
        std::vector<int> positions;
        
        for (int j = control_pos; j <= total; j++) {
            if (j & control_pos) {
                positions.push_back(j);
                parity ^= code[j];
            }
        }
        
        std::cout << "P" << control_pos << " проверяет биты: ";
        for (int pos : positions) {
            std::cout << pos << " ";
        }
        std::cout << "→ сумма XOR = " << parity;
        
        if (parity != 0) {
            std::cout << " (ошибка!)";
        }
        std::cout << std::endl;
    }
}

void task1_hamming() {
    std::cout << "\n========================================\n";
    std::cout << "ЗАДАЧА 1: КОД ХЭММИНГА\n";
    std::cout << "========================================\n";
    
    std::string message = "0100111010010";
    std::cout << "Сообщение (вариант 3): " << message << std::endl;
    std::cout << "Длина сообщения: " << message.length() << " бит\n";
    
    int r = count_control_bits(message.length());
    std::cout << "Количество контрольных битов: " << r << std::endl;
    std::cout << "Общая длина кода: " << message.length() + r << " бит\n";
    
    std::vector<int> code = insert_control_bits(message);
    print_code(code);
    
    int error_bit;
    std::cout << "\nВведите номер бита (1-" << code.size() - 1 << ") для имитации ошибки: ";
    std::cin >> error_bit;
    
    if (error_bit < 1 || error_bit >= (int)code.size()) {
        std::cout << "Некорректный номер бита!\n";
        return;
    }
    
    std::vector<int> corrupted = code;
    corrupted[error_bit] ^= 1;
    std::cout << "\nБит " << error_bit << " изменён\n";
    
    std::cout << "\nИскажённый код: ";
    for (size_t i = 1; i < corrupted.size(); i++) {
        std::cout << corrupted[i];
    }
    std::cout << std::endl;
    
    print_syndrome_calculation(corrupted);
    
    int syndrome = detect_error(corrupted);
    std::cout << "\nСИНДРОМ = " << syndrome << std::endl;
    
    if (syndrome == 0) {
        std::cout << "Ошибок не обнаружено!\n";
    } else if (syndrome >= 1 && syndrome < (int)corrupted.size()) {
        std::cout << "Ошибка обнаружена в бите " << syndrome << std::endl;
        
        corrupted[syndrome] ^= 1;
        std::cout << "\nИсправленный код: ";
        for (size_t i = 1; i < corrupted.size(); i++) {
            std::cout << corrupted[i];
        }
        std::cout << std::endl;
        
        std::cout << "\nИсходное сообщение (без контрольных битов): ";
        for (size_t i = 1; i < corrupted.size(); i++) {
            if ((i & (i - 1)) != 0) {
                std::cout << corrupted[i];
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "Ошибка за пределами кода!\n";
    }
}

// ============================================================
// ЗАДАЧА 2: КОД ХАФФМАНА
// ============================================================

HuffmanNode::HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
HuffmanNode::HuffmanNode(int f, HuffmanNode* l, HuffmanNode* r) : ch(0), freq(f), left(l), right(r) {}
bool HuffmanNode::isLeaf() const { return left == nullptr && right == nullptr; }

bool CompareNodes::operator()(HuffmanNode* a, HuffmanNode* b) {
    return a->freq > b->freq;
}

void build_huffman_codes(HuffmanNode* root, std::string code, std::map<char, std::string>& codes) {
    if (root == nullptr) return;
    
    if (root->isLeaf()) {
        codes[root->ch] = code;
    }
    
    build_huffman_codes(root->left, code + "0", codes);
    build_huffman_codes(root->right, code + "1", codes);
}

void print_huffman_tree(HuffmanNode* root, int level) {
    if (root == nullptr) return;
    
    print_huffman_tree(root->right, level + 1);
    
    for (int i = 0; i < level; i++) {
        std::cout << "   ";
    }
    
    if (root->isLeaf()) {
        std::cout << "'" << root->ch << "'(" << root->freq << ")" << std::endl;
    } else {
        std::cout << "[" << root->freq << "]" << std::endl;
    }
    
    print_huffman_tree(root->left, level + 1);
}

void delete_huffman_tree(HuffmanNode* root) {
    if (root == nullptr) return;
    delete_huffman_tree(root->left);
    delete_huffman_tree(root->right);
    delete root;
}

void task2_huffman() {
    std::cout << "\n========================================\n";
    std::cout << "ЗАДАЧА 2: КОД ХАФФМАНА\n";
    std::cout << "========================================\n";
    
    std::string text = "КРИЧАЛ АРХИП, АРХИП ОХРИП";
    std::cout << "Текст (вариант 3, задача 13): " << text << std::endl;
    
    std::map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }
    
    std::cout << "\nЧастота символов:\n";
    for (auto& p : freq) {
        std::cout << "'" << p.first << "' : " << p.second << std::endl;
    }
    
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;
    for (auto& p : freq) {
        pq.push(new HuffmanNode(p.first, p.second));
    }
    
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* parent = new HuffmanNode(left->freq + right->freq, left, right);
        pq.push(parent);
    }
    
    HuffmanNode* root = pq.top();
    
    std::cout << "\nДерево Хаффмана:\n";
    print_huffman_tree(root,0);
    
    std::map<char, std::string> codes;
    build_huffman_codes(root, "", codes);
    
    std::cout << "\nКоды символов:\n";
    for (auto& p : codes) {
        std::cout << "'" << p.first << "' : " << p.second << std::endl;
    }
    
    std::string encoded = "";
    for (char c : text) {
        encoded += codes[c];
    }
    
    std::cout << "\nЗакодированное сообщение:\n" << encoded << std::endl;
    
    int uniform_size = text.length() * 8;
    int huffman_size = encoded.length();
    
    std::cout << "\n=== Сравнение размеров ===\n";
    std::cout << "Равномерное кодирование (8 бит/символ): " << uniform_size << " бит\n";
    std::cout << "Кодирование Хаффмана: " << huffman_size << " бит\n";
    std::cout << "Экономия: " << uniform_size - huffman_size << " бит (";
    std::cout << (1 - (double)huffman_size / uniform_size) * 100 << "%)\n";
    
    delete_huffman_tree(root);
}

// ============================================================
// ЗАДАЧА 3: ШИФР ЦЕЗАРЯ (с поддержкой русских букв)
// ============================================================


std::string encrypt_caesar(const std::string& text, int shift) {
    std::string result = "";
    
    for (char c : text) {
        unsigned char ch = static_cast<unsigned char>(c);
        
        if (ch >= 0xC0 && ch <= 0xFF) {
            if (ch >= 0xC0 && ch <= 0xDF) {
                int new_pos = ((ch - 0xC0 + shift) % 32);
                if (new_pos < 0) new_pos += 32;
                result += static_cast<char>(new_pos + 0xC0);
            }
            else if (ch >= 0xE0 && ch <= 0xFF) {
                int new_pos = ((ch - 0xE0 + shift) % 32);
                if (new_pos < 0) new_pos += 32;
                result += static_cast<char>(new_pos + 0xE0);
            }
            else {
                result += c;
            }
        }
        else if (c >= 'A' && c <= 'Z') {
            int new_pos = ((c - 'A' + shift) % 26);
            if (new_pos < 0) new_pos += 26;
            result += static_cast<char>(new_pos + 'A');
        }
        else if (c >= 'a' && c <= 'z') {
            int new_pos = ((c - 'a' + shift) % 26);
            if (new_pos < 0) new_pos += 26;
            result += static_cast<char>(new_pos + 'a');
        }
        else {
            result += c;
        }
    }
    return result;
}

std::string decrypt_caesar(const std::string& text, int shift) {
    return encrypt_caesar(text, -shift);
}

void task3_caesar() {
    std::cout << "\n========================================\n";
    std::cout << "ЗАДАЧА 3: ШИФР ЦЕЗАРЯ (Shifr1)\n";
    std::cout << "========================================\n";
    
    int choice, shift;
    std::string input;
    
    std::cout << "1. Шифрование\n2. Дешифрование\nВыберите: ";
    std::cin >> choice;
    
    std::cout << "Введите сдвиг (целое число): ";
    std::cin >> shift;
    std::cin.ignore();
    
    if (choice == 1) {
        std::cout << "Введите текст для шифрования: ";
        std::getline(std::cin, input);
        std::string encrypted = encrypt_caesar(input, shift);
        std::cout << "\nРезультат шифрования:\n" << encrypted << std::endl;
        std::cout << "\nПроверка дешифрованием:\n" << decrypt_caesar(encrypted, shift) << std::endl;
    } else if (choice == 2) {
        std::cout << "Введите текст для дешифрования: ";
        std::getline(std::cin, input);
        std::cout << "\nРезультат дешифрования:\n" << decrypt_caesar(input, shift) << std::endl;
    } else {
        std::cout << "Неверный выбор!\n";
    }
}