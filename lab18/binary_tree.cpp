#include "binary_tree.h"

// ================ ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ ================

void BinaryTree::clear_rec(Node* p) {
    if (p == nullptr) return;
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

// ================ КОНСТРУКТОРЫ И ДЕСТРУКТОР ================

BinaryTree::BinaryTree(Node* r) : root(r) {}

BinaryTree::~BinaryTree() {
    clear_rec(root);
}

// ================ ВСТАВКА В ДЕРЕВО ПОИСКА (BST) ================

void BinaryTree::insert_bst(int v) {
    if (root == nullptr) {
        root = new Node(nullptr, nullptr, nullptr, v);
        return;
    }
    
    Node* current = root;
    Node* parent = nullptr;
    
    while (current != nullptr) {
        parent = current;
        if (v < current->get_value()) {
            current = current->get_left();
        } else {
            current = current->get_right();
        }
    }
    
    if (v < parent->get_value()) {
        parent->set_left(new Node(nullptr, nullptr, parent, v));
    } else {
        parent->set_right(new Node(nullptr, nullptr, parent, v));
    }
}

// ================ ВСТАВКА В ОБЫЧНОЕ ДЕРЕВО (СЛУЧАЙНАЯ) ================

void BinaryTree::insert_random(int v) {
    if (root == nullptr) {
        root = new Node(nullptr, nullptr, nullptr, v);
        return;
    }
    
    Node* current = root;
    while (true) {
        if (rand() % 2 == 0) {
            if (current->get_left() == nullptr) {
                current->set_left(new Node(nullptr, nullptr, current, v));
                return;
            }
            current = current->get_left();
        } else {
            if (current->get_right() == nullptr) {
                current->set_right(new Node(nullptr, nullptr, current, v));
                return;
            }
            current = current->get_right();
        }
    }
}

// ================ ОСНОВНЫЕ ОПЕРАЦИИ ================

void BinaryTree::clear() {
    clear_rec(root);
    root = nullptr;
}

bool BinaryTree::is_empty() const {
    return root == nullptr;
}

void BinaryTree::print_tree() const {
    if (is_empty()) {
        std::cout << "Дерево пусто.\n";
        return;
    }
    print_tree_rec(root, 0);
}

void BinaryTree::fill_manual_bst(int N) {
    clear();
    int data;
    for (int i = 0; i < N; ++i) {
        std::cin >> data;
        insert_bst(data);
    }
}

void BinaryTree::fill_manual_random(int N) {
    clear();
    int data;
    for (int i = 0; i < N; ++i) {
        std::cin >> data;
        insert_random(data);
    }
}

void BinaryTree::fill_random(int N, int min_val, int max_val) {
    clear();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < N; ++i) {
        int data = min_val + std::rand() % (max_val - min_val + 1);
        insert_random(data);
    }
}

// ================ ЗАДАНИЕ 1: ПРЕОБРАЗОВАНИЕ В ДВУСВЯЗНЫЙ СПИСОК (INORDER) ================

void BinaryTree::inorder_convert(Node* node, Node*& prev, Node*& head) {
    if (node == nullptr) return;
    
    // Левое поддерево
    inorder_convert(node->get_left(), prev, head);
    
    // Текущий узел
    node->set_left(prev);
    if (prev != nullptr) {
        prev->set_right(node);
    } else {
        head = node;
    }
    prev = node;
    
    // Правое поддерево
    inorder_convert(node->get_right(), prev, head);
}

void BinaryTree::convert_to_doubly_linked_list_inplace() {
    if (root == nullptr) return;
    
    Node* prev = nullptr;
    Node* head = nullptr;
    
    inorder_convert(root, prev, head);
    
    // Замыкаем список в кольцо
    if (head != nullptr && prev != nullptr) {
        head->set_left(prev);
        prev->set_right(head);
        root = head;
    }
}

void BinaryTree::print_as_list() const {
    if (root == nullptr) {
        std::cout << "Список пуст\n";
        return;
    }
    
    Node* current = root;
    Node* start = current;
    
    do {
        std::cout << current->get_value();
        current = current->get_right();
        if (current != start) std::cout << " <-> ";
    } while (current != start);
    
    std::cout << std::endl;
}

// ================ ЗАДАНИЕ 2: ИТЕРАТОР ПОСТ-ОБХОДА (ДЛЯ ОБЫЧНОГО ДЕРЕВА) ================

Node* BinaryTree::PostorderIterator::find_first(Node* root) {
    if (root == nullptr) return nullptr;
    
    Node* node = root;
    while (true) {
        if (node->get_left() != nullptr) {
            node = node->get_left();
        } else if (node->get_right() != nullptr) {
            node = node->get_right();
        } else {
            break;
        }
    }
    return node;
}

Node* BinaryTree::PostorderIterator::get_next_postorder() {
    if (current == nullptr) return nullptr;
    
    Node* parent = current->get_parent();
    
    if (parent == nullptr) return nullptr;
    
    if (parent->get_left() == current && parent->get_right() != nullptr) {
        return find_first(parent->get_right());
    }
    
    return parent;
}

BinaryTree::PostorderIterator::PostorderIterator(Node* root) {
    current = find_first(root);
}

bool BinaryTree::PostorderIterator::has_next() {
    return current != nullptr;
}

int BinaryTree::PostorderIterator::next() {
    if (current == nullptr) return -1;
    
    int value = current->get_value();
    current = get_next_postorder();
    
    return value;
}

BinaryTree::PostorderIterator BinaryTree::get_postorder_iterator() {
    return PostorderIterator(root);
}