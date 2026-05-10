#include "binary_tree.h"
#include "validator.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>

void setConsoleUTF8(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void print_menu() {
    std::cout << "\n========================================\n";
    std::cout << "        КАЛЬКУЛЯТОР ВЫРАЖЕНИЙ\n";
    std::cout << "========================================\n";
    std::cout << "1. CalcTree7 - Префиксная запись\n";
    std::cout << "2. CalcTree25 - Инфиксная запись\n";
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

void print_calctree7_menu() {
    std::cout << "\n--- CalcTree7: Префиксная запись ---\n";
    std::cout << "Операции: + - * / % ^\n";
    std::cout << "Операнды: целые числа от 0 до 9\n";
    std::cout << "Пример: + 2 * 3 4  (2+3*4)\n";
    std::cout << "Пример: * + 2 3 4  ((2+3)*4)\n";
    std::cout << "Кодирование операций: +(-1), -(-2), *(-3), /(-4), %(-5), ^(-6)\n\n";
}

void print_calctree25_menu() {
    std::cout << "\n--- CalcTree25: Инфиксная запись ---\n";
    std::cout << "Операции: + - * / % ^\n";
    std::cout << "Операнды: целые числа от 1 до 30, переменная x\n";
    std::cout << "Пример: 2*x+3*(4-x)/2\n";
    std::cout << "Кодирование операций: +(-1), -(-2), *(-3), /(-4), %(-5), ^(-6)\n\n";
}

// Генерация корректного префиксного выражения
std::string generate_random_prefix(int num_operands) {
    if(num_operands < 2) return "+ 0 1";
    
    const char* ops[] = {"+", "-", "*", "/", "%", "^"};
    std::vector<std::string> result;
    
    // Для префиксной записи используем рекурсивную генерацию
    std::function<std::string(int)> generate = [&](int remaining) -> std::string {
        if(remaining == 1) {
            return std::to_string(std::rand() % 10);
        }
        
        // Выбираем оператор
        int op_idx = std::rand() % 6;
        std::string expr = ops[op_idx];
        
        // Распределяем операнды между левым и правым поддеревом
        int left_count = 1 + std::rand() % (remaining - 1);
        int right_count = remaining - left_count;
        
        expr += " " + generate(left_count);
        expr += " " + generate(right_count);
        
        return expr;
    };
    
    return generate(num_operands);
}

void handle_calctree7() {
    print_calctree7_menu();
    
    Validator validator;
    BinaryTree tree;
    int choice;
    
    while(true) {
        print_input_menu();
        if(!validator.get_menu_choice(choice, 1, 3)) {
            continue;
        }
        break;
    }
    
    switch(choice) {
        case 1: { // Ручной ввод
            std::cout << "Введите выражение в префиксной форме (каждый элемент через пробел):\n";
            std::cout << "Пример: + 2 * 3 4\n";
            std::cout << "Ваш ввод: ";
            
            std::vector<std::string> tokens;
            validator.clear_input_buffer();
            std::string line;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            std::string token;
            
            while(ss >> token) {
                tokens.push_back(token);
            }
            
            if(!validator.validate_prefix_expression(tokens)) {
                std::cout << "Некорректное выражение. Построение дерева отменено.\n";
                return;
            }
            
            // Создаем временный файл для ввода
            std::ofstream temp("temp_prefix.txt");
            for(const auto& t : tokens) {
                temp << t << " ";
            }
            temp.close();
            
            tree.build_expression_tree_from_file_prefix("temp_prefix.txt");
            break;
        }
        case 2: { // Случайные данные
            int N;
            while(true) {
                std::cout << "Введите количество операндов (минимум 2): ";
                if(!validator.get_int_input(N)) {
                    continue;
                }
                if(validator.validate_positive_number(N, "Количество операндов") && N >= 2) {
                    break;
                }
                std::cout << "Ошибка: количество операндов должно быть не менее 2\n";
            }
            
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            std::string expression = generate_random_prefix(N);
            
            std::cout << "Сгенерировано выражение: " << expression << std::endl;
            
            // Сохраняем во временный файл
            std::ofstream temp("temp_prefix.txt");
            temp << expression;
            temp.close();
            
            tree.build_expression_tree_from_file_prefix("temp_prefix.txt");
            break;
        }
        case 3: { // Из файла
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;
            
            std::vector<std::string> tokens;
            if(!validator.validate_prefix_file(filename, tokens)) {
                std::cout << "Файл содержит некорректное выражение.\n";
                return;
            }
            
            tree.build_expression_tree_from_file_prefix(filename);
            break;
        }
    }
    
    if(!tree.is_empty()) {
        std::cout << "\n=== Исходное дерево (кодированный вывод) ===\n";
        tree.print_tree_coded();
        
        std::cout << "\n=== Результат вычислений ===\n";
        int result = tree.evaluate_subtree(tree.get_root());
        std::cout << "Значение выражения: " << result << std::endl;
        
        std::cout << "\n=== После замены поддеревьев со значением от 0 до 9 ===\n";
        tree.replace_subtrees_range_0_9();
        tree.print_tree_coded();
        
        std::cout << "\n=== Указатель на корень полученного дерева ===\n";
        std::cout << "Адрес корня: " << tree.get_root() << std::endl;
        
        std::ofstream out("result.txt");
        out << "Указатель на корень: " << tree.get_root() << std::endl;
        out.close();
    }
}

void handle_calctree25() {
    // ... (оставляем без изменений)
    print_calctree25_menu();
    
    Validator validator;
    BinaryTree tree;
    int choice;
    
    while(true) {
        print_input_menu();
        if(!validator.get_menu_choice(choice, 1, 3)) {
            continue;
        }
        break;
    }
    
    std::string expression;
    
    switch(choice) {
        case 1: {
            std::cout << "Введите выражение в инфиксной форме: ";
            validator.clear_input_buffer();
            std::getline(std::cin, expression);
            
            if(!validator.is_valid_expression_string(expression)) {
                std::cout << "Ошибка: выражение содержит недопустимые символы\n";
                return;
            }
            
            if(!validator.validate_infix_expression(expression)) {
                std::cout << "Некорректное выражение. Построение дерева отменено.\n";
                return;
            }
            
            tree.build_from_infix(expression);
            break;
        }
        case 2: {
            int len;
            while(true) {
                std::cout << "Введите количество операндов (минимум 2): ";
                if(!validator.get_int_input(len)) {
                    continue;
                }
                if(validator.validate_positive_number(len, "Длина выражения") && len >= 2) {
                    break;
                }
                std::cout << "Ошибка: количество операндов должно быть не менее 2\n";
            }
            
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            // Генерация инфиксного выражения
            const char* ops[] = {"+", "-", "*", "/", "%", "^"};
            expression = std::to_string(std::rand() % 30 + 1);
            for(int i = 1; i < len; i++) {
                int op_idx = std::rand() % 6;
                expression += ops[op_idx];
                if(std::rand() % 2 == 0) {
                    expression += std::to_string(std::rand() % 30 + 1);
                } else {
                    expression += "x";
                }
            }
            
            std::cout << "Сгенерировано выражение: " << expression << std::endl;
            
            if(!validator.validate_infix_expression(expression)) {
                std::cout << "Сгенерировано некорректное выражение. Попробуйте еще раз.\n";
                return;
            }
            
            tree.build_from_infix(expression);
            break;
        }
        case 3: {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::cin >> filename;
            
            if(!validator.validate_infix_file(filename, expression)) {
                std::cout << "Файл содержит некорректное выражение.\n";
                return;
            }
            
            tree.build_from_infix(expression);
            break;
        }
    }
    
    if(!tree.is_empty()) {
        std::cout << "\n=== Исходное дерево (кодированный вывод) ===\n";
        tree.print_tree_coded();
        
        std::ofstream out("FN2.txt");
        out << "=== Исходное дерево (кодированный вывод) ===\n";
        out.close();
        tree.print_sideways("FN2.txt");
        
        int x_value;
        if(validator.has_variable(expression)) {
            while(true) {
                std::cout << "\nВведите значение x: ";
                if(!validator.get_int_input(x_value)) {
                    continue;
                }
                if(validator.validate_number_in_range(x_value, -1000, 1000, "Значение x")) {
                    break;
                }
            }
        } else {
            x_value = 0;
            std::cout << "\nВыражение не содержит переменную x, вычисляем константу.\n";
        }
        
        int result = tree.evaluate_with_x(x_value);
        
        tree.replace_constants(x_value);
        
        std::cout << "\n=== Преобразованное дерево (кодированный вывод) ===\n";
        tree.print_tree_coded();
        
        std::ofstream out2("FN2.txt", std::ios::app);
        out2 << "\n=== Результат при x = " << x_value << ": " << result << " ===\n";
        out2 << "\n=== Преобразованное дерево (кодированный вывод) ===\n";
        out2.close();
        
        tree.print_sideways("FN2.txt");
        
        std::cout << "\n=== Результат ===\n";
        std::cout << "Значение выражения при x = " << x_value << ": " << result << std::endl;
        std::cout << "Результат сохранен в файл FN2.txt\n";
    }
}

int main() {
    setConsoleUTF8();
    Validator validator;
    int choice;
    
    do {
        print_menu();
        
        if(!validator.get_menu_choice(choice, 0, 2)) {
            continue;
        }
        
        switch(choice) {
            case 1:
                handle_calctree7();
                break;
            case 2:
                handle_calctree25();
                break;
            case 0:
                std::cout << "Завершение программы...\n";
                break;
        }
        
        if(choice != 0) {
            std::cout << "\nНажмите Enter для продолжения...";
            validator.clear_input_buffer();
            std::cin.get();
        }
    } while(choice != 0);
    
    return 0;
}