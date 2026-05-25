// main.cpp
#include "lab19.h"
#include <iostream>
#include <limits>

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
    try {
        int choice;
        
        do {
            print_menu();
            
            try {
                choice = get_menu_choice(0, 3);
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                clear_input_buffer();
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
        
    } catch (const std::exception& e) {
        std::cout << "\nКРИТИЧЕСКАЯ ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}