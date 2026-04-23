#include "binary_tree.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <stack>


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

bool is_op(std::string c){
    return c == "+" or c == "-" or c == "*" or c == "/" or c == "%";
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

bool is_op_coded(int x){
    return (x >= -5 and x<=-1);
}


int evaluate_subtree(Node* node){
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
        default: return 0;
    }
}

void replace_multi(Node*& node){
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