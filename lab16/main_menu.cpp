#include "main_menu.h"
#include "validator.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <ctime>

void MainMenu::clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void MainMenu::wait_for_enter() {
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore();
    std::cin.get();
}

int MainMenu::get_fill_method_choice(const std::string& prompt) {
    int choice;
    std::cout << prompt << "\n";
    std::cout << "1. Вручную\n";
    std::cout << "2. Случайными числами\n";
    std::cout << "3. Из файла\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    return choice;
}

void MainMenu::handle_manual_fill(Search_tree& tree) {
    int N;
    std::cout << "Введите количество элементов: ";
    
    std::string input;
    std::cin >> input;
    
    if (!TreeValidator::validate_number_input(input, N)) {
        std::cout << "Операция отменена\n";
        return;
    }
    
    if (N <= 0) {
        std::cout << "Ошибка: количество элементов должно быть положительным\n";
        return;
    }
    
    std::cout << "Введите " << N << " чисел: ";
    std::vector<int> numbers;
    int count = 0;
    
    while (count < N) {
        std::cin >> input;
        int val;
        if (TreeValidator::validate_number_input(input, val)) {
            numbers.push_back(val);
            count++;
        } else {
            std::cout << "Попробуйте снова: ";
        }
    }
    
    for (int val : numbers) {
        tree.insert(val);
    }
}

void MainMenu::handle_file_fill(Search_tree& tree) {
    std::string filename;
    std::cout << "Введите имя файла: ";
    std::cin >> filename;
    
    std::vector<int> numbers;
    if (TreeValidator::validate_file_numbers(filename, numbers)) {
        for (int val : numbers) {
            tree.insert(val);
        }
        std::cout << "Дерево успешно заполнено из файла\n";
    } else {
        std::cout << "Заполнение из файла отменено\n";
    }
}

void MainMenu::handle_random_fill(Search_tree& tree) {
    int N, min_val, max_val;
    std::cout << "Введите количество элементов: ";
    std::cin >> N;
    std::cout << "Введите минимальное и максимальное значение: ";
    std::cin >> min_val >> max_val;
    tree.fill_random(N, min_val, max_val);
}


void MainMenu::task1_handler() {
    std::cout << "\n=== Задание 1: вывод дерева в обратном порядке ===\n";
    
    Search_tree tree;
    int choice = get_fill_method_choice("Выберите способ заполнения дерева:");
    
    switch (choice) {
        case 1:
            handle_manual_fill(tree);
            break;
        case 2:
            handle_random_fill(tree);
            break;
        case 3:
            handle_file_fill(tree);
            break;
        default:
            std::cout << "Неверный выбор!\n";
            return;
    }

    std::cout << "\nВизуальное представление дерева:\n";
    tree.print_tree();
    std::cout << "\nС помощью вложенных скобок:\n";
    tree.print_inline(tree.get_root());
    std::cout << "\nСодержимое дерева в обратном порядке (убывание): ";
    tree.print_descending();
}

void MainMenu::task2_handler() {
    std::cout << "\n=== Задание 2: сортировка набора с помощью дерева поиска ===\n";
    
    Search_tree tree;
    std::vector<int> original_numbers;
    int choice = get_fill_method_choice("Выберите способ заполнения:");
    
    switch (choice) {
        case 1: {
            int N;
            std::cout << "Введите количество элементов N: ";
            std::cin >> N;
            std::cout << "Введите " << N << " чисел: ";
            for (int i = 0; i < N; ++i) {
                int val;
                std::cin >> val;
                original_numbers.push_back(val);
                tree.insert(val);
            }
            break;
        }
        case 2: {
            int N, min_val, max_val;
            std::cout << "Введите количество элементов N: ";
            std::cin >> N;
            std::cout << "Введите минимальное и максимальное значение: ";
            std::cin >> min_val >> max_val;
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            for (int i = 0; i < N; ++i) {
                int val = min_val + std::rand() % (max_val - min_val + 1);
                original_numbers.push_back(val);
                tree.insert(val);
            }
            break;
        }
        case 3: {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;
            std::ifstream file(filename);
            int val;
            while (file >> val) {
                original_numbers.push_back(val);
                tree.insert(val);
            }
            file.close();
            break;
        }
        default:
            std::cout << "Неверный выбор!\n";
            return;
    }
    
    // Вывод исходного набора
    std::cout << "\nИсходный набор чисел: ";
    for (int val : original_numbers) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    // Вывод визуального представления дерева
    std::cout << "\nВизуальное представление дерева:\n";
    tree.print_tree();

    std::cout << "\nС помощью вложенных скобок:\n";
    tree.print_inline(tree.get_root());
    
    // Вывод указателя на корень
    std::cout << "\nУказатель на корень дерева: " << tree.get_root() << "\n";
    
    // Вывод отсортированного набора (инфиксный обход)
    std::cout << "Возрастание: ";
    tree.print_ascending();
    
    //std::cout << "Убывание: ";
    //tree.print_descending();
}

// Задание 3: проверка дерева на идеальную сбалансированность
void MainMenu::task3_handler() {
    std::cout << "\n=== Задание 3: проверка дерева на идеальную сбалансированность ===\n";
    
    BinaryTree tree;
    
    // Выбор способа заполнения
    int fill_choice;
    std::cout << "Выберите способ построения дерева:\n";
    std::cout << "1. Вручную (ввод значений)\n";
    std::cout << "2. Случайными числами\n";
    std::cout << "3. Из файла\n";
    std::cout << "Ваш выбор: ";
    std::cin >> fill_choice;
    
    switch (fill_choice) {
        case 1: {
            int N;
            std::cout << "Введите количество элементов: ";
            std::cin >> N;
            std::cout << "Введите " << N << " чисел: ";
            tree.fill_manual(N);
            break;
        }
        case 2: {
            int N, min_val, max_val;
            std::cout << "Введите количество элементов: ";
            std::cin >> N;
            std::cout << "Введите минимальное и максимальное значение: ";
            std::cin >> min_val >> max_val;
            tree.fill_random(N, min_val, max_val);
            break;
        }
        case 3: {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;
            tree.fill_from_file(filename);
            break;
        }
        default:
            std::cout << "Неверный выбор!\n";
            return;
    }

    // Вывод визуального представления дерева
    std::cout << "\nВизуальное представление дерева:\n";
    tree.print_tree();

    
    // Вывод указателя на корень
    std::cout << "\nУказатель на корень дерева: " << tree.get_root() << "\n";
    
    // Проверка на идеальную сбалансированность
    std::cout << "\nРезультат проверки:\n";
    if (tree.is_perfectly_balanced()) {
        std::cout << "Дерево является ИДЕАЛЬНО СБАЛАНСИРОВАННЫМ.\n";
    } else {
        std::cout << "Дерево НЕ является идеально сбалансированным.\n";
    }
}

void MainMenu::run() {
    int main_choice;
    
    do {
        std::cout << "\n========================================\n";
        std::cout << "ГЛАВНОЕ МЕНЮ\n";
        std::cout << "========================================\n";
        std::cout << "1. Задание 1: Вывести дерево в обратном порядке\n";
        std::cout << "2. Задание 2: Отсортировать набор чисел с помощью дерева\n";
        std::cout << "3. Задание 3: Проверить дерево на идеальную сбалансированность\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        std::cin >> main_choice;
        
        switch (main_choice) {
            case 1:
                task1_handler();
                break;
            case 2:
                task2_handler();
                break;
            case 3:
                task3_handler();
                break;
            case 0:
                std::cout << "Программа завершена.\n";
                break;
            default:
                std::cout << "Неверный выбор! Попробуйте снова.\n";
                clear_input();
                break;
        }
        
        if (main_choice != 0) {
            wait_for_enter();
        }
        
    } while (main_choice != 0);
}