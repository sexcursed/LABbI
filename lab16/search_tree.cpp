#include "search_tree.h"
#include <ctime>
#include <cstdlib>

Node* Search_tree::insert_rec(Node* p, int v) {
    if(p == nullptr) {
        return new Node(nullptr, nullptr, v);
    }

    if(v < p->get_value()) {
        p->set_left(insert_rec(p->get_left(), v));
    }
    else if(v > p->get_value()) {
        p->set_right(insert_rec(p->get_right(), v));
    }
    return p;
}

void Search_tree::print_inline(Node* p) const{
    if(p != nullptr){
        std::cout << p->get_value();
        std::cout << " (";
        print_inline(p->get_left());
        std::cout << ") ";
        std::cout << " (";
        print_inline(p->get_right());
        std::cout << ") ";
    }
    else{
        std::cout << "null";
    }
}
void Search_tree::clear_rec(Node* p) {
    if(p == nullptr) {
        return;
    }
    clear_rec(p->get_left());
    clear_rec(p->get_right());
    delete p;
}

void Search_tree::print_tree_rec(Node* p, int level) const {
    if(p == nullptr) return;
    print_tree_rec(p->get_right(), level + 1);
    for(int i = 0; i < level; ++i) {
        std::cout << "   ";
    }
    std::cout << p->get_value() << std::endl;
    print_tree_rec(p->get_left(), level + 1);
}

void Search_tree::inorder(Node* p, std::vector<int>& result) const {
    if(p == nullptr) return;
    inorder(p->get_left(), result);
    result.push_back(p->get_value());
    inorder(p->get_right(), result);
}

void Search_tree::reverse_inorder(Node* p, std::vector<int>& result) const {
    if(p == nullptr) return;
    reverse_inorder(p->get_right(), result);
    result.push_back(p->get_value());
    reverse_inorder(p->get_left(), result);
}

Search_tree::Search_tree(Node* r) : root(r) {}

Search_tree::~Search_tree() {
    clear_rec(root);
}

Node* Search_tree::get_root() const {
    return root;
}

void Search_tree::insert(int v) {
    root = insert_rec(root, v);
}

void Search_tree::clear() {
    clear_rec(root);
    root = nullptr;
}

bool Search_tree::is_empty() const {
    return root == nullptr;
}

void Search_tree::print_ascending() const {
    std::vector<int> result;
    inorder(root, result);
    for(int val : result) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void Search_tree::print_descending() const {
    std::vector<int> result;
    reverse_inorder(root, result);
    for(int val : result) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void Search_tree::print_tree() const {
    if(is_empty()) {
        std::cout << "Дерево пусто.\n";
        return;
    }
    print_tree_rec(root, 0);
}

void Search_tree::fill_manual(int N) {
    clear();
    int data;
    for(int i = 0; i < N; ++i) {
        std::cin >> data;
        insert(data);
    }
}

void Search_tree::fill_random(int N, int min_val, int max_val) {
    clear();
    srand(time(0));
    for(int i = 0; i < N; ++i) {
        int data = min_val + rand() % (max_val - min_val + 1);
        insert(data);
    }
}

void Search_tree::fill_from_file(std::string filename) {
    clear();
    std::ifstream file(filename);
    int data;
    while(file >> data) {
        insert(data);
    }
    file.close();
}

std::vector<int> Search_tree::to_vector() const {
    std::vector<int> result;
    inorder(root, result);
    return result;
}