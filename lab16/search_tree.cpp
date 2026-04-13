#include "search_tree.h"
#include "node.h"

Node Search_tree::insert_rec(Node* p, int v){
    if(p == nullptr){
        return new Node(nullptr, nullptr,v);
    }

    if(value < p->get_value()){
        p->set_left(insert_recursive(p->get_left(),v));
    }
    else if(value > p->get_value()){
        p->set_right(insert_recursive(p->get_right(), v));
    }
    return p;
}

void Search_tree::clear_rec(Node* p){
    if(p == nullptr){
        return;
    }
    clear(p->get_left());
    clear(p->get_right());
    delete p;
}

void Search_tree::print_tree_rec(Node* p, int level) const{
    if(p == nullptr) return;
    print_tree(p->get_right(), level + 1);
    for(int i = 0; i < level; ++i){
        std::cout << " ";
    }
    std::cout << p->get_value() << std::endl;
    print_tree(p->get_left(), level + 1);
}

void Search_tree::inorder(Node* p, std::vector<int>& result){
    if(p == nullptr) return;
    inorder(p->get_left(), result);
    result.push_back(p->get_value());
    inorder(p->get_right(), result);
}

void Search_tree::reverse_inorder(Node* p, std::vector<int>& result){
    if(p == nullptr) return;
    inorder(p->get_right(), result);
    result.push_back(p->get_value());
    inorder(p->get_left(), result);
}

Search_tree::Search_tree(Node* r) : root(r){};

Search_tree::~Search_tree(){
    clear_rec(root);
}

Node* Search_tree::get_root(){
    return root;
}

Node* Search_tree::set_root(Node* p){
    root = p;
}

void Search_tree::insert(int v){
    insert_rec(root, v);
}

void Search_tree::clear(){
    clear_rec();
    root = nullptr;
}

bool Search_tree::is_empty() const{
    return root == nullptr;
}

void Search_tree::print_ascending() const{
    std::vector<int> result;
    inorder(root, result);
    for(int val : result){
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void Search_tree::print_ascending() const{
    std::vector<int> result;
    reverse_inorder(root, result);
    for(int val : result){
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void Search_tree::print_tree() const{
    if(is_empty()){
        std::cout << "Дерево пусто.\n";
        return;
    }
    print_tree_rec(root, 0);
}