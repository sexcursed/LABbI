#pragma once
#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <limits>

class Validator {
private:
    std::set<char> operators_rpn;
    std::set<char> operators_infix;
    
public:
    Validator();
    

    bool validate_rpn_expression(const std::vector<std::string>& tokens);
    

    bool validate_infix_expression(const std::string& expression);
    

    bool validate_file_exists(const std::string& filename);
    

    bool validate_number_in_range(int value, int min, int max, const std::string& error_msg);
    

    bool validate_positive_number(int value, const std::string& error_msg);
    

    bool validate_rpn_file(const std::string& filename, std::vector<std::string>& tokens);
    

    bool validate_infix_file(const std::string& filename, std::string& expression);
    

    std::string trim(const std::string& str);
    

    bool has_variable(const std::string& expression);
    

    bool is_number(const std::string& str);
    

    bool is_valid_expression_string(const std::string& str);
    

    bool is_valid_rpn_token(const std::string& token);
    

    void clear_input_buffer();
    

    bool get_int_input(int& value);
    

    bool get_menu_choice(int& choice, int min_val, int max_val);
};