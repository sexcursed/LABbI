// main.cpp
#include "lab19.h"
#include <iostream>
#include <limits>

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
    std::cout << "ЛАБОРАТОРНАЯ РАБОТА №19\n";
    std::cout << "ВАРИАНТ 3\n";
    std::cout << "========================================\n";
    std::cout << "1. Задача 1 - Код Хэмминга\n";
    std::cout << "2. Задача 2 - Код Хаффмана\n";
    std::cout << "3. Задача 3 - Шифр Цезаря\n";
    std::cout << "0. Выход\n";
    std::cout << "========================================\n";
    std::cout << "Выберите задачу: ";
}

int main() {
    int choice;
    
    do {
        print_menu();
        
        if (!get_menu_choice(choice, 0, 3)) {
            continue;
        }
        
        switch (choice) {
            case 1:
                task1_hamming();
                break;
            case 2:
                task2_huffman();
                break;
            case 3:
                task3_caesar();
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