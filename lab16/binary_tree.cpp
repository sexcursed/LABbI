#include "binary_tree.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

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

// Подсчет количества узлов в поддереве
int BinaryTree::get_node_count(Node* p) const {
    if (p == nullptr) {
        return 0;
    }
    return 1 + get_node_count(p->get_left()) + get_node_count(p->get_right());
}

// Рекурсивная проверка сбалансированности
bool BinaryTree::is_perfectly_balanced_rec(Node* p) const {
    if (p == nullptr) {
        return true;
    }
    
    int left_count = get_node_count(p->get_left());
    int right_count = get_node_count(p->get_right());
    
    // Проверяем условие для текущей вершины
    if (abs(left_count - right_count) > 1) {
        return false;
    }
    
    // Рекурсивно проверяем левое и правое поддеревья
    return is_perfectly_balanced_rec(p->get_left()) && 
           is_perfectly_balanced_rec(p->get_right());
}

// Публичный метод для проверки
bool BinaryTree::is_perfectly_balanced() const {
    if (is_empty()) {
        return true; // Пустое дерево считается сбалансированным
    }
    return is_perfectly_balanced_rec(root);
}

