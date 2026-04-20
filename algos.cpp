#include <iostream>

struct Node{
    Node* left;
    Node* right;
    int key;
    Node(int v) : key(v), left(nullptr), right(nullptr) {}
};

void print_level(Node* p, int k){
    if(p == nullptr) return;
    if(k == 0){
        std::cout << p->key << " ";
        return;
    }
    print_level(p->left, k-1);
    print_level(p->right, k-1);
}

void print_tree(Node* p, int level){
    if(p == nullptr) return;
    print_tree(p->right, level + 1);
    for(int i = 0; i < level; ++i){
        std::cout << "    ";
    }
    std::cout << p->key << std::endl;
    print_tree(p->left, level + 1);
}

Node* copy_tree(Node* p){
    if(p == nullptr) return nullptr;
    Node* new_node = new Node(p->key);
    new_node->left = copy_tree(p->left);
    new_node->right = copy_tree(p->right);
    return new_node;
}

int main(){
    Node* root = new Node(89);
    root->left = new Node(4);
    root->left->left = new Node(2);
    root->left->right = new Node(65);
    root->left->right->left = new Node(11);
    root->left->right->left->right = new Node(28);
    root->left->right->left->right->left = new Node(12);
    root->left->right->left->right->left->right = new Node(17);
    root->left->right->left->right->right = new Node(33);
    root->left->right->left->right->right->right = new Node(45);
    root->right = new Node(100);
    root->right->left = new Node(99);
    int k;
    std::cin >> k;
    print_level(root, k);
    std::cout << "\n\n\n\n";
    print_tree(root,0);
    std::cout << "\n\n\n\n";
    print_tree(copy_tree(root), 0);
    return 0;
}