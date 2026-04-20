
#include "validator.h"
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

bool TreeValidator::has_no_cycles(Node* root) {
    if (root == nullptr) {
        return true;
    }
    
    std::vector<Node*> visited;
    std::vector<Node*> stack;
    return !detect_cycle(root, visited, stack);
}

bool TreeValidator::detect_cycle(Node* node, std::vector<Node*>& visited, std::vector<Node*>& stack) {
    if (node == nullptr) {
        return false;
    }
    
    if (std::find(stack.begin(), stack.end(), node) != stack.end()) {
        std::cout << "Обнаружен цикл в узле " << node->get_value() << "\n";
        return true;
    }
    
    if (std::find(visited.begin(), visited.end(), node) != visited.end()) {
        return false;
    }
    
    visited.push_back(node);
    stack.push_back(node);
    
    if (detect_cycle(node->get_left(), visited, stack) ||
        detect_cycle(node->get_right(), visited, stack)) {
        return true;
    }
    
    stack.pop_back();
    return false;
}

bool TreeValidator::all_nodes_reachable(Node* root) {
    if (root == nullptr) {
        return true;
    }
    
    std::vector<Node*> reachable_nodes;
    collect_nodes(root, reachable_nodes);
    
    std::unordered_set<Node*> all_pointers;
    for (Node* node : reachable_nodes) {
        if (node->get_left() != nullptr) {
            all_pointers.insert(node->get_left());
        }
        if (node->get_right() != nullptr) {
            all_pointers.insert(node->get_right());
        }
    }
    
    for (Node* ptr : all_pointers) {
        if (std::find(reachable_nodes.begin(), reachable_nodes.end(), ptr) == reachable_nodes.end()) {
            std::cout << "Узел " << ptr->get_value() << " недостижим из корня\n";
            return false;
        }
    }
    
    return true;
}

void TreeValidator::collect_nodes(Node* node, std::vector<Node*>& nodes) {
    if (node == nullptr) {
        return;
    }
    
    nodes.push_back(node);
    collect_nodes(node->get_left(), nodes);
    collect_nodes(node->get_right(), nodes);
}

bool TreeValidator::no_dangling_pointers(Node* root) {
    return check_dangling_pointers(root);
}

bool TreeValidator::check_dangling_pointers(Node* node) {
    if (node == nullptr) {
        return true;
    }
    
    Node* left = node->get_left();
    Node* right = node->get_right();
    
    if (left != nullptr) {
        int val = left->get_value();
    }
    
    if (right != nullptr) {
        int val = right->get_value();
    }
    
    return check_dangling_pointers(left) && check_dangling_pointers(right);
}

bool TreeValidator::no_duplicate_nodes(Node* root) {
    if (root == nullptr) {
        return true;
    }
    
    std::vector<Node*> nodes;
    collect_nodes(root, nodes);
    
    std::unordered_set<Node*> unique_nodes;
    for (Node* node : nodes) {
        if (unique_nodes.find(node) != unique_nodes.end()) {
            std::cout << "Обнаружен дублирующийся узел с адресом " << node << " и значением " << node->get_value() << "\n";
            return false;
        }
        unique_nodes.insert(node);
    }
    
    return true;
}

bool TreeValidator::no_self_pointers(Node* root) {
    return check_self_pointers(root);
}

bool TreeValidator::check_self_pointers(Node* node) {
    if (node == nullptr) {
        return true;
    }
    
    if (node->get_left() == node) {
        std::cout << "Узел " << node->get_value() << " имеет указатель left на самого себя\n";
        return false;
    }
    
    if (node->get_right() == node) {
        std::cout << "Узел " << node->get_value() << " имеет указатель right на самого себя\n";
        return false;
    }
    
    return check_self_pointers(node->get_left()) && 
           check_self_pointers(node->get_right());
}

bool TreeValidator::is_valid_tree(Node* root) {
    bool valid = true;
    
    std::cout << "\nПРОВЕРКА ВАЛИДНОСТИ ДЕРЕВА\n";
    
    if (!has_no_cycles(root)) {
        std::cout << "Обнаружены циклы в дереве\n";
        valid = false;
    } else {
        std::cout << "Циклы не обнаружены\n";
    }
    
    if (!all_nodes_reachable(root)) {
        std::cout << "Есть недостижимые узлы\n";
        valid = false;
    } else {
        std::cout << "Все узлы достижимы из корня\n";
    }
    
    if (!no_self_pointers(root)) {
        std::cout << "Обнаружены указатели на самих себя\n";
        valid = false;
    } else {
        std::cout << "Нет указателей на самих себя\n";
    }
    
    if (!no_duplicate_nodes(root)) {
        std::cout << "Обнаружены дублирующиеся узлы\n";
        valid = false;
    } else {
        std::cout << "Нет дублирующихся узлов\n";
    }
    
    if (!no_dangling_pointers(root)) {
        std::cout << "Обнаружены подозрительные указатели\n";
        valid = false;
    } else {
        std::cout << "Указатели корректны\n";
    }
    
    std::cout << "\nРезультат: " << (valid ? "Дерево валидно" : "Дерево невалидно") << "\n";
    
    return valid;
}

void TreeValidator::print_validation_results(Node* root, const std::string& tree_name) {
    std::cout << "\nПроверка дерева: " << tree_name << "\n";
    
    if (root == nullptr) {
        std::cout << "Дерево пустое\n";
        return;
    }
    
    std::cout << "Корень: " << root << " (значение: " << root->get_value() << ")\n";
    std::cout << "Количество узлов: " << get_node_count(root) << "\n";
    std::cout << "Высота дерева: " << get_height(root) << "\n";
    
    is_valid_tree(root);
}

int TreeValidator::get_node_count(Node* root) {
    return get_node_count_rec(root);
}

int TreeValidator::get_node_count_rec(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + get_node_count_rec(node->get_left()) + get_node_count_rec(node->get_right());
}

int TreeValidator::get_height(Node* root) {
    return get_height_rec(root);
}

int TreeValidator::get_height_rec(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(get_height_rec(node->get_left()), get_height_rec(node->get_right()));
}

bool TreeValidator::is_number(const std::string& str) {
    if (str.empty()) {
        return false;
    }
    
    size_t start = 0;
    if (str[0] == '-') {
        if (str.length() == 1) {
            return false;
        }
        start = 1;
    }
    
    for (size_t i = start; i < str.length(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    
    return true;
}

bool TreeValidator::validate_number_input(const std::string& input, int& result) {
    if (!is_number(input)) {
        std::cout << "Ошибка: '" << input << "' не является целым числом\n";
        return false;
    }
    
    try {
        result = std::stoi(input);
        return true;
    } catch (...) {
        std::cout << "Ошибка: не удалось преобразовать '" << input << "' в число\n";
        return false;
    }
}

bool TreeValidator::validate_file_numbers(const std::string& filename, std::vector<int>& numbers) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл '" << filename << "'\n";
        return false;
    }
    
    numbers.clear();
    std::string line;
    int line_number = 1;
    bool has_error = false;
    
    while (std::getline(file, line)) {
        if (line.empty()) {
            line_number++;
            continue;
        }
        
        std::istringstream iss(line);
        std::string token;
        
        while (iss >> token) {
            int value;
            if (!is_number(token)) {
                std::cout << "Ошибка в файле, строка " << line_number << ": '" << token << "' не является целым числом\n";
                has_error = true;
            } else {
                try {
                    value = std::stoi(token);
                    numbers.push_back(value);
                } catch (...) {
                    std::cout << "Ошибка в файле, строка " << line_number << ": не удалось преобразовать '" << token << "' в число\n";
                    has_error = true;
                }
            }
        }
        line_number++;
    }
    
    file.close();
    
    if (has_error) {
        numbers.clear();
        return false;
    }
    
    if (numbers.empty()) {
        std::cout << "Ошибка: файл не содержит чисел\n";
        return false;
    }
    
    std::cout << "Файл успешно прочитан. Найдено чисел: " << numbers.size() << "\n";
    return true;
}