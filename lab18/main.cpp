#include "binary_tree.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <vector>

void clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool get_int_input(int& value) {
    std::cin >> value;
    if (std::cin.fail()) {
        clear_input_buffer();
        std::cout << "Ошибка: введите целое число!\n";
        return false;
    }
    return true;
}

bool get_range_input(int& min_val, int& max_val) {
    std::cout << "Введите минимальное и максимальное значение через пробел: ";
    if (!get_int_input(min_val)) return false;
    if (!get_int_input(max_val)) return false;
    
    if (min_val >= max_val) {
        std::cout << "Ошибка: минимальное значение должно быть меньше максимального!\n";
        return false;
    }
    
    return true;
}

bool get_menu_choice(int& choice, int min_val, int max_val) {
    if (!get_int_input(choice)) {
        return false;
    }
    if (choice < min_val || choice > max_val) {
        std::cout << "Ошибка: выберите число от " << min_val << " до " << max_val << "!\n";
        clear_input_buffer();
        return false;
    }
    return true;
}

void print_menu() {
    std::cout << "\n========================================\n";
    std::cout << "        ЛАБОРАТОРНАЯ РАБОТА №18\n";
    std::cout << "             ВАРИАНТ 3\n";
    std::cout << "========================================\n";
    std::cout << "1. TreeFun1 - Преобразование BST в список\n";
    std::cout << "2. TreeFun5 - Итератор (лево-право-корень)\n";
    std::cout << "0. Выход\n";
    std::cout << "========================================\n";
    std::cout << "Выберите задачу: ";
}

void print_input_menu() {
    std::cout << "\n--- Способ ввода данных ---\n";
    std::cout << "1. Ручной ввод\n";
    std::cout << "2. Случайные данные\n";
    std::cout << "3. Из файла\n";
    std::cout << "Выберите способ: ";
}

bool get_positive_number(int& N, const char* msg) {
    while (true) {
        std::cout << msg;
        if (!get_int_input(N)) {
            continue;
        }
        if (N > 0) {
            return true;
        }
        std::cout << "Ошибка: количество должно быть больше 0!\n";
    }
}

bool read_numbers_from_file(const std::string& filename, std::vector<int>& numbers) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return false;
    }
    
    int num;
    while (file >> num) {
        numbers.push_back(num);
    }
    
    file.close();
    
    if (numbers.empty()) {
        std::cout << "Ошибка: файл пуст\n";
        return false;
    }
    
    return true;
}

void fill_tree_from_file_bst(BinaryTree& tree) {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;
    
    std::vector<int> numbers;
    if (!read_numbers_from_file(filename, numbers)) {
        return;
    }
    
    tree.clear();
    for (int num : numbers) {
        tree.insert_bst(num);
    }
    
    std::cout << "Загружено " << numbers.size() << " чисел из файла\n";
}

void fill_tree_from_file_random(BinaryTree& tree) {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;
    
    std::vector<int> numbers;
    if (!read_numbers_from_file(filename, numbers)) {
        return;
    }
    
    tree.clear();
    for (int num : numbers) {
        tree.insert_random(num);
    }
    
    std::cout << "Загружено " << numbers.size() << " чисел из файла\n";
}

void handle_treefun1() {
    std::cout << "\n=== TreeFun1: Преобразование дерева поиска (BST) в двусвязный список ===\n";
    
    BinaryTree tree;
    int choice, N;
    
    while (true) {
        print_input_menu();
        if (!get_menu_choice(choice, 1, 3)) continue;
        break;
    }
    
    if (choice == 1) {
        if (!get_positive_number(N, "Введите количество узлов: ")) return;
        std::cout << "Введите " << N << " чисел для BST: ";
        tree.fill_manual_bst(N);
    } else if (choice == 2) {
        if (!get_positive_number(N, "Введите количество узлов: ")) return;
        
        int min_val, max_val;
        while (true) {
            if (!get_range_input(min_val, max_val)) continue;
            break;
        }
        
        tree.clear();
        for (int i = 0; i < N; ++i) {
            int data = min_val + std::rand() % (max_val - min_val + 1);
            tree.insert_bst(data);
        }
        std::cout << "Сгенерировано " << N << " случайных чисел для BST в диапазоне [" 
                  << min_val << ", " << max_val << "]\n";
    } else {
        fill_tree_from_file_bst(tree);
        if (tree.is_empty()) return;
    }
    
    std::cout << "\nИсходное дерево поиска (BST):\n";
    tree.print_tree();
    
    tree.convert_to_doubly_linked_list_inplace();
    
    std::cout << "\nПолученный двусвязный список (в порядке возрастания):\n";
    tree.print_as_list();
}

void handle_treefun5() {
    std::cout << "\n=== TreeFun5: Итератор пост-обхода (лево-право-корень) для обычного дерева ===\n";
    
    BinaryTree tree;
    int choice, N;
    
    while (true) {
        print_input_menu();
        if (!get_menu_choice(choice, 1, 3)) continue;
        break;
    }
    
    if (choice == 1) {
        if (!get_positive_number(N, "Введите количество узлов: ")) return;
        std::cout << "Введите " << N << " чисел: ";
        tree.fill_manual_random(N);
    } else if (choice == 2) {
        if (!get_positive_number(N, "Введите количество узлов: ")) return;
        
        int min_val, max_val;
        while (true) {
            if (!get_range_input(min_val, max_val)) continue;
            break;
        }
        
        tree.fill_random(N, min_val, max_val);
        std::cout << "Сгенерировано " << N << " случайных чисел для обычного дерева в диапазоне ["
                  << min_val << ", " << max_val << "]\n";
    } else {
        fill_tree_from_file_random(tree);
        if (tree.is_empty()) return;
    }
    
    std::cout << "\nОбычное дерево:\n";
    tree.print_tree();
    
    std::cout << "\nОбход в порядке (лево-право-корень):\n";
    BinaryTree::PostorderIterator it = tree.get_postorder_iterator();
    
    while (it.has_next()) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    int choice;
    
    do {
        print_menu();
        
        if (!get_menu_choice(choice, 0, 2)) {
            continue;
        }
        
        switch(choice) {
            case 1:
                handle_treefun1();
                break;
            case 2:
                handle_treefun5();
                break;
            case 0:
                std::cout << "Завершение программы...\n";
                break;
        }
        
        if (choice != 0) {
            std::cout << "\nНажмите Enter для продолжения...";
            clear_input_buffer();
            std::cin.get();
        }
    } while (choice != 0);
    
    return 0;
}