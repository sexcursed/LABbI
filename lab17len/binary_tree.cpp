#include "binary_tree.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <stack>
#include <functional>
#include <cctype>
#include <cmath>

bool is_op(std::string c){
    return c == "+" or c == "-" or c == "*" or c == "/" or c == "%";
}

void BinaryTree::build_expression_tree_from_file(std::string filename) {
    clear();
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Не удалось открыть файл\n";
        return;
    }

    std::stack<Node*> st;
    std::string token;

    while(file >> token){
        if(is_op(token)){
            if(st.size() < 2){
                std::cout << "Недостаточно операндов для оператора\n";
                return;
            }
            Node* right = st.top();
            st.pop();
            Node* left = st.top();
            st.pop();

            int op_coded;
            
            if(token == "+") op_coded = -1;
            else if(token == "-") op_coded = -2;
            else if(token == "*") op_coded = -3;
            else if(token == "/") op_coded = -4;
            else op_coded = -5;
            Node* node = new Node(left,right,op_coded);
            st.push(node);
        }
        else{
            if(token.length() == 1 && std::isdigit(token[0])){
                int num = std::stoi(token);
                st.push(new Node(nullptr,nullptr,num));
            }
            else{
                std::cout << "Некорректный операнд: " << token << std::endl;
                return;
            }
        }
    }
    if(st.size() == 1){
        root = st.top();
        std::cout << "Дерево выражения успешно построено\n";
    }
    else{
        std::cout << "Ошибка: некорректное выражение\n";
    }
}

void BinaryTree::print_expression_tree() const {
    if(root == nullptr){
        std::cout << "Дерево пусто\n";
        return;
    }
    
    std::function<void(Node*, int)> print_node = [&](Node* node, int level){
        if(node == nullptr) return;
        print_node(node->get_right(), level + 1);
        for(int i = 0; i < level; i++) std::cout << "   ";
        
        if(is_op_coded(node->get_value())){
            switch(node->get_value()){
                case -1: std::cout << "+"; break;
                case -2: std::cout << "-"; break;
                case -3: std::cout << "*"; break;
                case -4: std::cout << "/"; break;
                case -5: std::cout << "%"; break;
            }
        }
        else{
            std::cout << node->get_value();
        }
        std::cout << std::endl;
        print_node(node->get_left(), level + 1);
    };
    
    print_node(root, 0);
}


bool BinaryTree::is_operator_char(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

int BinaryTree::get_precedence(char c) {
    switch(c) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '%': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int BinaryTree::apply_operator(int op, int left, int right) {
    switch(op) {
        case -1: return left + right;
        case -2: return left - right;
        case -3: return left * right;
        case -4: return left / right;
        case -5: return left % right;
        case -6: {
            int result = 1;
            for(int i = 0; i < right; i++) result *= left;
            return result;
        }
        default: return 0;
    }
}

std::vector<std::string> BinaryTree::infix_to_postfix(const std::string& expr) {
    std::vector<std::string> output;
    std::stack<char> ops;
    
    for(size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];
        if(std::isspace(c)) continue;
        
        if(std::isdigit(c)) {
            std::string num;
            while(i < expr.length() && std::isdigit(expr[i])) {
                num += expr[i++];
            }
            i--;
            output.push_back(num);
        }
        else if(c == 'x') {
            output.push_back("x");
        }
        else if(c == '(') {
            ops.push(c);
        }
        else if(c == ')') {
            while(!ops.empty() && ops.top() != '(') {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            if(!ops.empty()) ops.pop();
        }
        else if(is_operator_char(c)) {
            while(!ops.empty() && ops.top() != '(' && (get_precedence(ops.top()) > get_precedence(c) || (get_precedence(ops.top()) == get_precedence(c) && c != '^'))) {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            ops.push(c);
        }
    }
    
    while(!ops.empty()) {
        output.push_back(std::string(1, ops.top()));
        ops.pop();
    }
    return output;
}

Node* BinaryTree::build_from_postfix(const std::vector<std::string>& postfix) {
    std::stack<Node*> st;
    for(const auto& token : postfix) {
        if(token == "x") {
            Node* node = new Node(nullptr, nullptr, -100);
            st.push(node);
        }
        else if(std::isdigit(token[0])) {
            int val = std::stoi(token);
            st.push(new Node(nullptr, nullptr, val));
        }
        else {
            char op = token[0];
            int code;
            switch(op) {
                case '+': code = -1; break;
                case '-': code = -2; break;
                case '*': code = -3; break;
                case '/': code = -4; break;
                case '%': code = -5; break;
                case '^': code = -6; break;
                default: code = 0;
            }
            Node* right = st.top(); st.pop();
            Node* left = st.top(); st.pop();
            st.push(new Node(left, right, code));
        }
    }
    return st.top();
}

void BinaryTree::build_from_infix(const std::string& expr) {
    clear();
    std::vector<std::string> postfix = infix_to_postfix(expr);
    root = build_from_postfix(postfix);
}

int BinaryTree::evaluate_with_x(int x_val) {
    return evaluate_subtree_int(root, x_val);
}

bool BinaryTree::subtree_has_variable(Node* node) {
    if(!node) return false;
    if(node->get_value() == -100) return true;
    return subtree_has_variable(node->get_left()) || subtree_has_variable(node->get_right());
}

int BinaryTree::evaluate_subtree_int(Node* node, int x_val) {
    if(!node) return 0;
    if(node->get_value() == -100) return x_val;
    if(node->get_value() >= 0) return node->get_value();
    
    int left_val = evaluate_subtree_int(node->get_left(), x_val);
    int right_val = evaluate_subtree_int(node->get_right(), x_val);
    return apply_operator(node->get_value(), left_val, right_val);
}

Node* BinaryTree::replace_const_subtrees(Node* node, int x_val) {
    if(!node) return nullptr;
    
    node->set_left(replace_const_subtrees(node->get_left(), x_val));
    node->set_right(replace_const_subtrees(node->get_right(), x_val));
    
    if(!subtree_has_variable(node)) {
        int val = evaluate_subtree_int(node, x_val);
        delete node->get_left();
        delete node->get_right();
        node->set_left(nullptr);
        node->set_right(nullptr);
        node->set_value(val);
    }
    return node;
}

void BinaryTree::replace_constants(int x_val) {
    replace_const_subtrees(root, x_val);
}

void BinaryTree::print_tree_sideways(Node* node, int level, std::ofstream& out) const {
    if(!node) return;
    print_tree_sideways(node->get_right(), level + 1, out);
    
    std::stringstream ss;
    if(node->get_value() == -100) ss << "x";
    else if(node->get_value() >= 0) ss << node->get_value();
    else {
        switch(node->get_value()) {
            case -1: ss << "+"; break;
            case -2: ss << "-"; break;
            case -3: ss << "*"; break;
            case -4: ss << "/"; break;
            case -5: ss << "%"; break;
            case -6: ss << "^"; break;
        }
    }
    
    out << std::string(level * 8, ' ');
    out.width(8);
    out << std::right << ss.str() << std::endl;
    
    print_tree_sideways(node->get_left(), level + 1, out);
}

void BinaryTree::print_sideways(const std::string& filename) const {
    std::ofstream out(filename, std::ios::app);
    if(!root) {
        out << "Дерево пусто\n";
        return;
    }
    print_tree_sideways(root, 0, out);
    out << std::endl;
    out.close();
}


void BinaryTree::clear_rec(Node* p) {
    if (p == nullptr) {
        return;
    }
    clear_rec(p->get_left());
    clear_rec(p->get_right());
    delete p;
}

void BinaryTree::print_tree_rec(Node* p, int level) const {
    if (p == nullptr) return;
    print_tree_rec(p->get_right(), level + 1);
    for (int i = 0; i < level; ++i) {
        std::cout << "   ";
    }
    std::cout << p->get_value() << std::endl;
    print_tree_rec(p->get_left(), level + 1);
}

void BinaryTree::inorder(Node* p, std::vector<int>& result) const {
    if (p == nullptr) return;
    inorder(p->get_left(), result);
    result.push_back(p->get_value());
    inorder(p->get_right(), result);
}

void BinaryTree::preorder(Node* p, std::vector<int>& result) const {
    if (p == nullptr) return;
    result.push_back(p->get_value());
    preorder(p->get_left(), result);
    preorder(p->get_right(), result);
}

void BinaryTree::postorder(Node* p, std::vector<int>& result) const {
    if (p == nullptr) return;
    postorder(p->get_left(), result);
    postorder(p->get_right(), result);
    result.push_back(p->get_value());
}

BinaryTree::BinaryTree(Node* r) : root(r) {}

BinaryTree::BinaryTree(const BinaryTree& other) {
    root = nullptr;
    std::vector<int> values = other.to_vector();
    for (int val : values) {
        insert(val);
    }
}

BinaryTree::~BinaryTree() {
    clear_rec(root);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) {
    if (this != &other) {
        clear();
        std::vector<int> values = other.to_vector();
        for (int val : values) {
            insert(val);
        }
    }
    return *this;
}

void BinaryTree::insert(int v) {
    if (root == nullptr) {
        root = new Node(nullptr, nullptr, v);
        return;
    }
    
    Node* current = root;
    
    while (true) {
        if (rand() % 2 == 0) {
            if (current->get_left() == nullptr) {
                current->set_left(new Node(nullptr, nullptr, v));
                return;
            }
            current = current->get_left();
        } else {
            if (current->get_right() == nullptr) {
                current->set_right(new Node(nullptr, nullptr, v));
                return;
            }
            current = current->get_right();
        }
    }
}

void BinaryTree::clear() {
    clear_rec(root);
    root = nullptr;
}

bool BinaryTree::is_empty() const {
    return root == nullptr;
}

void BinaryTree::print_ascending() const {
    std::vector<int> result;
    inorder(root, result);
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void BinaryTree::print_descending() const {
    std::vector<int> result;
    inorder(root, result);
    std::reverse(result.begin(), result.end());
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

Node* BinaryTree::get_root() const {
    return root;
}

void BinaryTree::print_tree() const {
    if (is_empty()) {
        std::cout << "Дерево пусто.\n";
        return;
    }
    print_tree_rec(root, 0);
}

void BinaryTree::fill_manual(int N) {
    clear();
    int data;
    for (int i = 0; i < N; ++i) {
        std::cin >> data;
        insert(data);
    }
}

void BinaryTree::fill_random(int N, int min_val, int max_val) {
    clear();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < N; ++i) {
        int data = min_val + std::rand() % (max_val - min_val + 1);
        insert(data);
    }
}

void BinaryTree::fill_from_file(std::string filename) {
    clear();
    std::ifstream file(filename);
    int data;
    while (file >> data) {
        insert(data);
    }
    file.close();
}

std::vector<int> BinaryTree::to_vector() const {
    std::vector<int> result;
    inorder(root, result);
    return result;
}

void BinaryTree::print_preorder() const {
    std::vector<int> result;
    preorder(root, result);
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void BinaryTree::print_postorder() const {
    std::vector<int> result;
    postorder(root, result);
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}



void BinaryTree::build_expression_tree() {
    clear();
    std::ifstream file("text.txt");
    if(!file.is_open()){
        std::cout << "Не удалось открыть файл\n";
        return;
    }

    std::stack<Node*> st;
    std::string token;

    while(file >> token){
        if(is_op(token)){
            if(st.size() < 2){
                std::cout << "Недостаточно опрендов для оператора\n";
                return;
            }
            Node* right = st.top();
            st.pop();
            Node* left = st.top();
            st.pop();

            int op_coded;
            
            if(token == "+") op_coded = -1;
            else if(token == "-") op_coded = -2;
            else if(token == "*") op_coded = -3;
            else if(token == "/") op_coded = -4;
            else op_coded = -5;
            Node* node = new Node(left,right,op_coded);
            st.push(node);
        }
        else{
            if(token.length() == 1 and std::isdigit(token[0])){
                int num = std::stoi(token);
                st.push(new Node(nullptr,nullptr,num));
            }
            else{
                std::cout << "Некорректный операнд\n";
                return;
            }
        }
    }
    root = st.top();
}

bool BinaryTree::is_op_coded(int x) const{
    return (x >= -6 and x<=-1);
}


int BinaryTree::evaluate_subtree(Node* node){
    if(!node) return 0;
    if(!is_op_coded(node->get_value())){
        return node->get_value();
    }

    int left_val = evaluate_subtree(node->get_left());
    int right_val = evaluate_subtree(node->get_right());

    switch(node->get_value()){
        case -1: return left_val+right_val;
        case -2: return left_val-right_val;
        case -3: return left_val*right_val;
        case -4: return left_val/right_val;
        case -5: return left_val%right_val;
        case -6: {
            int result = 1;
            if (right_val < 0) return 0;
            for (int i = 0; i < right_val; ++i) {
                result *= left_val;
            }
            return result;
        }
        default: return 0;
    }
}

void BinaryTree::replace_multi(Node* node){
    if(!node) return;

    replace_multi(node->get_left());
    replace_multi(node->get_right());

    if(node->get_value() == -3){
        int result = evaluate_subtree(node);

        delete node->get_left();
        delete node->get_right();
        node->set_left(nullptr);
        node->set_right(nullptr);
        node->set_value(result);
    }
}

void BinaryTree::print_tree_coded() const {
    if(root == nullptr){
        std::cout << "Дерево пусто\n";
        return;
    }
    
    std::function<void(Node*, int)> print_node = [&](Node* node, int level){
        if(node == nullptr) return;
        print_node(node->get_right(), level + 1);
        
        for(int i = 0; i < level; i++) {
            std::cout << "   ";
        }
        

        std::cout << node->get_value() << std::endl;
        
        print_node(node->get_left(), level + 1);
    };
    
    print_node(root, 0);
}

void BinaryTree::print_tree_normal() const {
    if(root == nullptr){
        std::cout << "Дерево пусто\n";
        return;
    }
    
    std::function<void(Node*, int)> print_node = [&](Node* node, int level){
        if(node == nullptr) return;
        print_node(node->get_right(), level + 1);
        
        for(int i = 0; i < level; i++) {
            std::cout << "   ";
        }
        

        if(is_op_coded(node->get_value())){
            switch(node->get_value()){
                case -1: std::cout << "+"; break;
                case -2: std::cout << "-"; break;
                case -3: std::cout << "*"; break;
                case -4: std::cout << "/"; break;
                case -5: std::cout << "%"; break;
                case -6: std::cout << "^"; break;
                default: std::cout << node->get_value(); break;
            }
        }
        else if(node->get_value() == -100) {
            std::cout << "x";
        }
        else {
            std::cout << node->get_value();
        }
        std::cout << std::endl;
        
        print_node(node->get_left(), level + 1);
    };
    
    print_node(root, 0);
}


void BinaryTree::build_expression_tree_from_file_prefix(std::string filename) {
    clear();
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cout << "Не удалось открыть файл\n";
        return;
    }
    
    std::vector<std::string> tokens;
    std::string token;
    while(file >> token){
        tokens.push_back(token);
    }
    file.close();
    
    if(tokens.empty()){
        std::cout << "Файл пуст\n";
        return;
    }
    
    size_t index = 0;
    root = build_from_prefix(tokens, index);
    
    if(index != tokens.size()){
        std::cout << "Ошибка: некорректное выражение (лишние токены)\n";
        clear();
    }
    else{
        std::cout << "Дерево выражения успешно построено из префиксной формы\n";
    }
}

Node* BinaryTree::build_from_prefix(const std::vector<std::string>& tokens, size_t& index) {
    if(index >= tokens.size()){
        return nullptr;
    }
    
    std::string token = tokens[index++];
    
    if(token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^"){
        int op_coded;
        if(token == "+") op_coded = -1;
        else if(token == "-") op_coded = -2;
        else if(token == "*") op_coded = -3;
        else if(token == "/") op_coded = -4;
        else if(token == "%") op_coded = -5;
        else op_coded = -6;
        
        Node* left = build_from_prefix(tokens, index);
        Node* right = build_from_prefix(tokens, index);
        
        if(left == nullptr || right == nullptr){
            delete left;
            delete right;
            return nullptr;
        }
        
        return new Node(left, right, op_coded);
    }
    else{
        if(token.length() == 1 && std::isdigit(token[0])){
            int num = std::stoi(token);
            if(num >= 0 && num <= 9){
                return new Node(nullptr, nullptr, num);
            }
        }
        std::cout << "Некорректный операнд: " << token << std::endl;
        return nullptr;
    }
}

void BinaryTree::replace_subtrees_range_0_9() {
    root = replace_subtrees_range_0_9_rec(root);
}

Node* BinaryTree::replace_subtrees_range_0_9_rec(Node* node) {
    if(!node) return nullptr;
    
    node->set_left(replace_subtrees_range_0_9_rec(node->get_left()));
    node->set_right(replace_subtrees_range_0_9_rec(node->get_right()));
    
    if(is_op_coded(node->get_value())){
        int result = evaluate_subtree(node);
        
        if(result >= 0 && result <= 9){
            delete node->get_left();
            delete node->get_right();
            node->set_left(nullptr);
            node->set_right(nullptr);
            node->set_value(result);
        }
    }
    
    return node;
}