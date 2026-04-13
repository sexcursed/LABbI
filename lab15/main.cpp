#include "main_menu.h"
#include <iostream>


int main() {
    while (true) {
        std::cout << "\n========================================\n";
        std::cout << "            ГЛАВНОЕ МЕНЮ\n";
        std::cout << "========================================\n";
        std::cout << "1 - Задание 1.3 (Name)\n";
        std::cout << "2 - Задание 2.2-2.3 (Person)\n";
        std::cout << "3 - Задание 3.3 (City)\n";
        std::cout << "4 - Задание 4.6 (Person)\n";
        std::cout << "5 - Задание 5.2 (Cat)\n";
        std::cout << "0 - Выход\n";
        std::cout << "========================================\n";
        std::cout << "Ваш выбор: ";
        
        int choice;
        std::cin >> choice;
        clear_input();
        
        switch (choice) {
            case 1:
                handle_task_1();
                break;
            case 2:
                handle_task_2();
                break;
            case 3:
                handle_task_3();
                break;
            case 4:
                handle_task_4();
                break;
            case 5:
                handle_task_5();
                break;
            case 0:
                return 0;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
                break;
        }
        
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.get();
    }
    
    return 0;
}