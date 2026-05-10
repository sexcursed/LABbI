#include "validator.h"

Validator::Validator() {

    operators_rpn = {'+', '-', '*', '/', '%'};
    

    operators_infix = {'+', '-', '*', '/', '%', '^', '(', ')'};
}

std::string Validator::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

bool Validator::is_number(const std::string& str) {
    if(str.empty()) return false;
    
    size_t start = 0;
    if(str[0] == '-' || str[0] == '+') {
        start = 1;
        if(str.length() == 1) return false;
    }
    
    for(size_t i = start; i < str.length(); i++) {
        if(!std::isdigit(str[i])) return false;
    }
    return true;
}

void Validator::clear_input_buffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Validator::get_int_input(int& value) {
    std::cin >> value;
    
    if(std::cin.fail()) {
        clear_input_buffer();
        std::cout << "Ошибка: введите целое число!\n";
        return false;
    }
    
    return true;
}

bool Validator::get_menu_choice(int& choice, int min_val, int max_val) {
    if(!get_int_input(choice)) {
        return false;
    }
    
    if(choice < min_val || choice > max_val) {
        std::cout << "Ошибка: выберите число от " << min_val << " до " << max_val << "!\n";
        return false;
    }
    
    return true;
}

bool Validator::validate_rpn_expression(const std::vector<std::string>& tokens) {
    if(tokens.empty()) {
        std::cout << "Ошибка: пустое выражение\n";
        return false;
    }
    
    int operand_count = 0;
    int operator_count = 0;
    
    for(const auto& token : tokens) {

        if(token.length() == 1 && operators_rpn.count(token[0])) {
            operator_count++;
            if(operand_count < 2) {
                std::cout << "Ошибка: недостаточно операндов для оператора '" << token << "'\n";
                return false;
            }
            operand_count--; 
        }

        else if(token.length() == 1 && std::isdigit(token[0])) {
            operand_count++;
        }

        else if(token.length() > 1 && std::isdigit(token[0])) {
            bool all_digits = true;
            for(char c : token) {
                if(!std::isdigit(c)) {
                    all_digits = false;
                    break;
                }
                int num = std::stoi(token);
                if(num < 0 || num > 9) {
                    std::cout << "Ошибка: число " << num << " выходит за пределы [0;9]\n";
                    return false;
                }
            }
            if(all_digits) {
                operand_count++;
            } else {
                std::cout << "Ошибка: некорректный токен '" << token << "'\n";
                return false;
            }
        }
        else {
            std::cout << "Ошибка: некорректный токен '" << token << "'\n";
            return false;
        }
    }
    

    if(operand_count != 1) {
        std::cout << "Ошибка: некорректное выражение (осталось " << operand_count << " операндов)\n";
        return false;
    }
    
    return true;
}

bool Validator::validate_infix_expression(const std::string& expression) {
    std::string expr = trim(expression);
    
    if(expr.empty()) {
        std::cout << "Ошибка: пустое выражение\n";
        return false;
    }
    
    int bracket_balance = 0;
    bool last_was_operator = true;
    bool last_was_operand = false;
    
    for(size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];
        

        if(std::isspace(c)) continue;
        

        if(c == '(') {
            bracket_balance++;
            last_was_operator = true;
            last_was_operand = false;
        }
        else if(c == ')') {
            bracket_balance--;
            if(bracket_balance < 0) {
                std::cout << "Ошибка: лишняя закрывающая скобка\n";
                return false;
            }
            last_was_operator = false;
            last_was_operand = true;
        }

        else if(operators_infix.count(c)) {
            if(c != '(' && c != ')') {
                if(last_was_operator && c != '(') {
                    std::cout << "Ошибка: два оператора подряд\n";
                    return false;
                }
                last_was_operator = true;
                last_was_operand = false;
            }
        }

        else if(c == 'x') {
            last_was_operator = false;
            last_was_operand = true;
        }

        else if(std::isdigit(c)) {

            std::string num_str;
            while(i < expr.length() && std::isdigit(expr[i])) {
                num_str += expr[i++];
            }
            i--;
            
            int num = std::stoi(num_str);
            if(num < 1 || num > 30) {
                std::cout << "Ошибка: число " << num << " выходит за пределы [1;30]\n";
                return false;
            }
            last_was_operator = false;
            last_was_operand = true;
        }
        else {
            std::cout << "Ошибка: недопустимый символ '" << c << "'\n";
            return false;
        }
    }
    

    if(bracket_balance != 0) {
        std::cout << "Ошибка: несбалансированные скобки\n";
        return false;
    }
    

    if(last_was_operator) {
        std::cout << "Ошибка: выражение не может заканчиваться оператором\n";
        return false;
    }
    
    return true;
}

bool Validator::validate_file_exists(const std::string& filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cout << "Ошибка: не удалось открыть файл '" << filename << "'\n";
        return false;
    }
    file.close();
    return true;
}

bool Validator::validate_number_in_range(int value, int min, int max, const std::string& error_msg) {
    if(value < min || value > max) {
        std::cout << "Ошибка: " << error_msg << " (должно быть от " << min << " до " << max << ")\n";
        return false;
    }
    return true;
}

bool Validator::validate_positive_number(int value, const std::string& error_msg) {
    if(value <= 0) {
        std::cout << "Ошибка: " << error_msg << " (должно быть положительным)\n";
        return false;
    }
    return true;
}

bool Validator::validate_rpn_file(const std::string& filename, std::vector<std::string>& tokens) {
    if(!validate_file_exists(filename)) {
        return false;
    }
    
    std::ifstream file(filename);
    tokens.clear();
    std::string token;
    
    while(file >> token) {
        tokens.push_back(token);
    }
    file.close();
    
    return validate_rpn_expression(tokens);
}

bool Validator::validate_infix_file(const std::string& filename, std::string& expression) {
    if(!validate_file_exists(filename)) {
        return false;
    }
    
    std::ifstream file(filename);
    std::getline(file, expression);
    file.close();
    
    return validate_infix_expression(expression);
}

bool Validator::has_variable(const std::string& expression) {
    return expression.find('x') != std::string::npos;
}

bool Validator::is_valid_expression_string(const std::string& str) {
    std::string expr = trim(str);
    if(expr.empty()) return false;
    
    for(char c : expr) {
        if(std::isdigit(c)) continue;
        if(c == 'x') continue;
        if(operators_infix.count(c)) continue;
        if(std::isspace(c)) continue;
        return false;
    }
    return true;
}

bool Validator::is_valid_rpn_token(const std::string& token) {
    if(token.empty()) return false;

    if(token.length() == 1 && operators_rpn.count(token[0])) {
        return true;
    }
    

    if(is_number(token)) {
        int num = std::stoi(token);
        return (num >= 0 && num <= 9);
    }
    
    return false;
}

// Добавьте в конец validator.cpp:

bool Validator::validate_prefix_expression(const std::vector<std::string>& tokens) {
    if(tokens.empty()) {
        std::cout << "Ошибка: пустое выражение\n";
        return false;
    }
    
    // Проверяем первый токен - должен быть оператором для неодноэлементного выражения
    if(tokens.size() > 1) {
        std::set<char> prefix_ops = {'+', '-', '*', '/', '%', '^'};
        if(tokens[0].length() != 1 || !prefix_ops.count(tokens[0][0])) {
            std::cout << "Ошибка: префиксное выражение должно начинаться с оператора\n";
            return false;
        }
    }
    
    // Используем стек для проверки корректности
    std::stack<int> st;
    
    for(int i = tokens.size() - 1; i >= 0; i--) {
        const std::string& token = tokens[i];
        
        // Проверяем токен
        if(token.length() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || 
                                   token[0] == '/' || token[0] == '%' || token[0] == '^')) {
            // Оператор требует 2 операнда
            if(st.size() < 2) {
                std::cout << "Ошибка: недостаточно операндов для оператора '" << token << "'\n";
                return false;
            }
            st.pop();
            st.pop();
            st.push(1); // Пушим 1 как признак успешной обработки
        }
        else if(token.length() == 1 && std::isdigit(token[0])) {
            int num = token[0] - '0';
            if(num < 0 || num > 9) {
                std::cout << "Ошибка: число " << num << " выходит за пределы [0;9]\n";
                return false;
            }
            st.push(1);
        }
        else if(token.length() > 1 && std::isdigit(token[0])) {
            bool all_digits = true;
            for(char c : token) {
                if(!std::isdigit(c)) {
                    all_digits = false;
                    break;
                }
            }
            if(all_digits) {
                int num = std::stoi(token);
                if(num < 0 || num > 9) {
                    std::cout << "Ошибка: число " << num << " выходит за пределы [0;9]\n";
                    return false;
                }
                st.push(1);
            } else {
                std::cout << "Ошибка: некорректный токен '" << token << "'\n";
                return false;
            }
        }
        else {
            std::cout << "Ошибка: некорректный токен '" << token << "'\n";
            return false;
        }
    }
    
    if(st.size() != 1) {
        std::cout << "Ошибка: некорректное выражение\n";
        return false;
    }
    
    return true;
}

bool Validator::validate_prefix_file(const std::string& filename, std::vector<std::string>& tokens) {
    if(!validate_file_exists(filename)) {
        return false;
    }
    
    std::ifstream file(filename);
    tokens.clear();
    std::string token;
    
    while(file >> token) {
        tokens.push_back(token);
    }
    file.close();
    
    return validate_prefix_expression(tokens);
}