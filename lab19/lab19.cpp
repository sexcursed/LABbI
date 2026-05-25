#include "lab19.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <string>
#include <map>
#include <cctype>
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>
#include <stdexcept>

// ============================================================
// ОБЩИЕ ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ============================================================

void clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int get_menu_choice(int min_val, int max_val) {
    int choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        clear_input_buffer();
        throw std::invalid_argument("Ошибка: введите целое число!");
    }
    if (choice < min_val || choice > max_val) {
        throw std::out_of_range("Ошибка: выберите число от " + std::to_string(min_val) + 
                                 " до " + std::to_string(max_val) + "!");
    }
    return choice;
}

int get_input_mode(const std::string& task_name) {
    std::cout << "\n--- " << task_name << " ---\n";
    std::cout << "1. Использовать пример (встроенные данные)\n";
    std::cout << "2. Ручной ввод\n";
    std::cout << "Выберите режим: ";
    
    try {
        return get_menu_choice(1, 2);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1; // По умолчанию возвращаем пример
    }
}

int get_manual_input_method(const std::string& task_name) {
    std::cout << "\n--- Ручной ввод (" << task_name << ") ---\n";
    std::cout << "1. Ввод с клавиатуры\n";
    std::cout << "2. Случайные данные\n";
    std::cout << "3. Из файла\n";
    std::cout << "Выберите способ ввода: ";
    
    try {
        return get_menu_choice(1, 3);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}

// ============================================================
// ЗАДАЧА 1: КОД ХЭММИНГА
// ============================================================

std::string generate_random_binary_string(int length) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<int> dist(0, 1);
    
    std::string result;
    for (int i = 0; i < length; ++i) {
        result += std::to_string(dist(rng));
    }
    return result;
}

std::string read_binary_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        // Удаляем пробелы и проверяем, что строка состоит только из 0 и 1
        for (char c : line) {
            if (c == '0' || c == '1') {
                content += c;
            } else if (c != ' ' && c != '\t' && c != '\r') {
                throw std::runtime_error("Файл должен содержать только символы '0' и '1'!");
            }
        }
    }
    
    if (content.empty()) {
        throw std::runtime_error("Файл пуст или не содержит двоичных данных!");
    }
    
    return content;
}

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
        if (data_pos < m) {
            code[i] = message[data_pos++] - '0';
        }
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
    
    std::string message;
    int mode = get_input_mode("Код Хэмминга");
    
    try {
        if (mode == 1) {
            // Использование примера
            message = "0100111010010";
            std::cout << "Сообщение (пример): " << message << std::endl;
        } else {
            // Ручной ввод
            int method = get_manual_input_method("Код Хэмминга");
            
            if (method == 1) {
                // Ввод с клавиатуры
                std::cout << "Введите двоичное сообщение (только 0 и 1): ";
                std::cin >> message;
                clear_input_buffer();
                
                for (char c : message) {
                    if (c != '0' && c != '1') {
                        throw std::invalid_argument("Сообщение должно содержать только символы '0' и '1'!");
                    }
                }
            } 
            else if (method == 2) {
                // Случайные данные
                int length;
                std::cout << "Введите длину случайного сообщения: ";
                std::cin >> length;
                clear_input_buffer();
                
                if (length <= 0) {
                    throw std::invalid_argument("Длина должна быть положительным числом!");
                }
                
                message = generate_random_binary_string(length);
                std::cout << "Сгенерированное сообщение: " << message << std::endl;
            } 
            else {
                // Из файла
                std::string filename;
                std::cout << "Введите имя файла (например, input.txt): ";
                std::cin >> filename;
                clear_input_buffer();
                
                message = read_binary_from_file(filename);
                std::cout << "Сообщение из файла: " << message << std::endl;
            }
        }
        
        std::cout << "Длина сообщения: " << message.length() << " бит\n";
        
        int r = count_control_bits(message.length());
        std::cout << "Количество контрольных битов: " << r << std::endl;
        std::cout << "Общая длина кода: " << message.length() + r << " бит\n";
        
        std::vector<int> code = insert_control_bits(message);
        print_code(code);
        
        int error_bit;
        std::cout << "\nВведите номер бита (1-" << code.size() - 1 << ") для имитации ошибки: ";
        error_bit = get_menu_choice(1, code.size() - 1);
        
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
        
    } catch (const std::exception& e) {
        std::cout << "\nОШИБКА: " << e.what() << std::endl;
        std::cout << "Задача прервана.\n";
    }
}

// ============================================================
// ЗАДАЧА 2: КОД ХАФФМАНА
// ============================================================

std::string generate_random_text(int length) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<int> dist(0, 25);
    
    std::string result;
    std::string chars = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ ";
    
    for (int i = 0; i < length; ++i) {
        result += chars[dist(rng) % chars.length()];
    }
    return result;
}

std::string read_text_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        if (!content.empty()) content += "\n";
        content += line;
    }
    
    if (content.empty()) {
        throw std::runtime_error("Файл пуст!");
    }
    
    return content;
}

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
    
    std::string text;
    int mode = get_input_mode("Код Хаффмана");
    
    try {
        if (mode == 1) {
            // Использование примера
            text = "КРИЧАЛ АРХИП, АРХИП ОХРИП";
            std::cout << "Текст (пример): " << text << std::endl;
        } else {
            // Ручной ввод
            int method = get_manual_input_method("Код Хаффмана");
            
            if (method == 1) {
                // Ввод с клавиатуры
                std::cout << "Введите текст для кодирования: ";
                clear_input_buffer();
                std::getline(std::cin, text);
                
                if (text.empty()) {
                    throw std::invalid_argument("Текст не может быть пустым!");
                }
            } 
            else if (method == 2) {
                // Случайные данные
                int length;
                std::cout << "Введите длину случайного текста: ";
                std::cin >> length;
                clear_input_buffer();
                
                if (length <= 0) {
                    throw std::invalid_argument("Длина должна быть положительным числом!");
                }
                
                text = generate_random_text(length);
                std::cout << "Сгенерированный текст: " << text << std::endl;
            } 
            else {
                // Из файла
                std::string filename;
                std::cout << "Введите имя файла (например, text.txt): ";
                std::cin >> filename;
                clear_input_buffer();
                
                text = read_text_from_file(filename);
                std::cout << "Текст из файла:\n" << text << std::endl;
            }
        }
        
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
        print_huffman_tree(root, 0);
        
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
        
    } catch (const std::exception& e) {
        std::cout << "\nОШИБКА: " << e.what() << std::endl;
        std::cout << "Задача прервана.\n";
    }
}

// ============================================================
// ЗАДАЧА 3: ШИФР ЦЕЗАРЯ (с поддержкой русских букв)
// ============================================================

std::string generate_random_text_russian(int length) {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    static std::string uppercase = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    static std::string lowercase = "абвгдежзийклмнопрстуфхцчшщъыьэюя";
    
    std::string result;
    for (int i = 0; i < length; ++i) {
        if (rng() % 2 == 0) {
            result += uppercase[rng() % uppercase.length()];
        } else {
            result += lowercase[rng() % lowercase.length()];
        }
        // Иногда добавляем пробел
        if (rng() % 5 == 0 && result.length() < length - 1) {
            result += ' ';
        }
    }
    return result;
}

std::string read_text_from_file_caesar(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        if (!content.empty()) content += "\n";
        content += line;
    }
    
    if (content.empty()) {
        throw std::runtime_error("Файл пуст!");
    }
    
    return content;
}

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
    std::cout << "ЗАДАЧА 3: ШИФР ЦЕЗАРЯ\n";
    std::cout << "========================================\n";
    
    std::string input;
    int shift;
    int operation;
    
    try {
        std::cout << "1. Шифрование\n2. Дешифрование\nВыберите операцию: ";
        operation = get_menu_choice(1, 2);
        
        std::cout << "Введите сдвиг (целое число, может быть отрицательным): ";
        std::cin >> shift;
        clear_input_buffer();
        
        int mode = get_input_mode("Шифр Цезаря");
        
        if (mode == 1) {
            // Использование примера
            if (operation == 1) {
                input = "Привет, Мир!";
                std::cout << "Текст для шифрования (пример): " << input << std::endl;
            } else {
                std::string example_encrypted = encrypt_caesar("Привет, Мир!", 3);
                input = example_encrypted;
                std::cout << "Текст для дешифрования (пример): " << input << std::endl;
            }
        } else {
            // Ручной ввод
            int method = get_manual_input_method("Шифр Цезаря");
            
            if (method == 1) {
                // Ввод с клавиатуры
                if (operation == 1) {
                    std::cout << "Введите текст для шифрования: ";
                } else {
                    std::cout << "Введите текст для дешифрования: ";
                }
                std::getline(std::cin, input);
                
                if (input.empty()) {
                    throw std::invalid_argument("Текст не может быть пустым!");
                }
            } 
            else if (method == 2) {
                // Случайные данные
                int length;
                std::cout << "Введите длину случайного текста: ";
                std::cin >> length;
                clear_input_buffer();
                
                if (length <= 0) {
                    throw std::invalid_argument("Длина должна быть положительным числом!");
                }
                
                input = generate_random_text_russian(length);
                std::cout << "Сгенерированный текст: " << input << std::endl;
            } 
            else {
                // Из файла
                std::string filename;
                std::cout << "Введите имя файла (например, text.txt): ";
                std::cin >> filename;
                clear_input_buffer();
                
                input = read_text_from_file_caesar(filename);
                std::cout << "Текст из файла:\n" << input << std::endl;
            }
        }
        
        if (operation == 1) {
            std::string encrypted = encrypt_caesar(input, shift);
            std::cout << "\nРезультат шифрования:\n" << encrypted << std::endl;
            
            // Дополнительно показываем расшифровку для проверки
            std::string decrypted = decrypt_caesar(encrypted, shift);
            std::cout << "\nПроверка (дешифрование):\n" << decrypted << std::endl;
        } else {
            std::string decrypted = decrypt_caesar(input, shift);
            std::cout << "\nРезультат дешифрования:\n" << decrypted << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "\nОШИБКА: " << e.what() << std::endl;
        std::cout << "Задача прервана.\n";
    }
}