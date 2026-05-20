// binary_tree.cpp
#include "binary_tree.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>

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

void BinaryTree::inorder(Node* p, std::vector<int>& result) const {
    if (p == nullptr) return;
    inorder(p->get_left(), result);
    result.push_back(p->get_value());
    inorder(p->get_right(), result);
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

std::vector<int> BinaryTree::to_vector() const {
    std::vector<int> result;
    inorder(root, result);
    return result;
}

Node* BinaryTree::get_root() const {
    return root;
}

Node* BinaryTree::convert_to_doubly_linked_list() {
    if (root == nullptr) return nullptr;
    
    Node* prev = nullptr;
    std::stack<Node*> st;
    Node* current = root;
    
    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {
            st.push(current);
            current = current->get_left();
        }
        
        current = st.top();
        st.pop();
        
        current->set_left(prev);
        if (prev != nullptr) {
            prev->set_right(current);
        }
        prev = current;
        
        current = current->get_right();
    }
    
    Node* head = root;
    while (head->get_left() != nullptr) {
        head = head->get_left();
    }
    
    return head;
}

Node* BinaryTree::build_balanced_from_list(Node*& head, int start, int end) {
    if (start > end) return nullptr;
    
    int mid = (start + end) / 2;
    
    Node* left = build_balanced_from_list(head, start, mid - 1);
    
    Node* node = head;
    head = head->get_right();
    
    node->set_left(left);
    
    node->set_right(build_balanced_from_list(head, mid + 1, end));
    
    return node;
}

void BinaryTree::convert_from_doubly_linked_list(Node* head) {
    if (head == nullptr) {
        root = nullptr;
        return;
    }
    
    int n = 0;
    Node* current = head;
    while (current != nullptr) {
        n++;
        current = current->get_right();
    }
    
    root = build_balanced_from_list(head, 0, n - 1);
}

void BinaryTree::print_doubly_linked_list(Node* head) const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->get_value();
        if (current->get_right() != nullptr) std::cout << " <-> ";
        current = current->get_right();
    }
    std::cout << std::endl;
}

BinaryTree::PostorderIterator::PostorderIterator(Node* root) {
    if (root == nullptr) return;
    
    st1.push(root);
    while (!st1.empty()) {
        Node* node = st1.top();
        st1.pop();
        st2.push(node);
        
        if (node->get_left() != nullptr) {
            st1.push(node->get_left());
        }
        if (node->get_right() != nullptr) {
            st1.push(node->get_right());
        }
    }
}

bool BinaryTree::PostorderIterator::has_next() {
    return !st2.empty();
}

int BinaryTree::PostorderIterator::next() {
    Node* node = st2.top();
    st2.pop();
    return node->get_value();
}

BinaryTree::PostorderIterator BinaryTree::get_postorder_iterator() {
    return PostorderIterator(root);
}

std::string BinaryTree::serialize(Node* node) {
    if (node == nullptr) {
        return "#";
    }
    
    std::string left = serialize(node->get_left());
    std::string right = serialize(node->get_right());
    
    return "(" + std::to_string(node->get_value()) + left + right + ")";
}

bool BinaryTree::are_equal(Node* a, Node* b) {
    if (a == nullptr && b == nullptr) return true;
    if (a == nullptr || b == nullptr) return false;
    if (a->get_value() != b->get_value()) return false;
    
    return are_equal(a->get_left(), b->get_left()) && 
           are_equal(a->get_right(), b->get_right());
}

void BinaryTree::collect_all_subtrees(Node* node, std::vector<Node*>& all_subtrees) {
    if (node == nullptr) return;
    
    collect_all_subtrees(node->get_left(), all_subtrees);
    collect_all_subtrees(node->get_right(), all_subtrees);
    
    all_subtrees.push_back(node);
}

bool BinaryTree::is_ancestor_of(Node* ancestor, Node* descendant) {
    if (ancestor == nullptr) return false;
    if (ancestor == descendant) return true;
    
    return is_ancestor_of(ancestor->get_left(), descendant) ||
           is_ancestor_of(ancestor->get_right(), descendant);
}

void BinaryTree::remove_duplicate_subtrees() {
    if (root == nullptr) return;
    
    std::vector<Node*> all_subtrees;
    collect_all_subtrees(root, all_subtrees);
    
    std::unordered_map<std::string, std::vector<Node*>> groups;
    
    for (Node* node : all_subtrees) {
        std::string sig = serialize(node);
        groups[sig].push_back(node);
    }
    
    std::set<Node*> to_delete;
    
    for (auto& pair : groups) {
        std::vector<Node*>& nodes = pair.second;
        
        if (nodes.size() <= 1) continue;
        
        for (size_t i = 0; i < nodes.size(); ++i) {
            for (size_t j = i + 1; j < nodes.size(); ++j) {
                if (are_equal(nodes[i], nodes[j])) {
                    if (is_ancestor_of(nodes[i], nodes[j])) {
                        to_delete.insert(nodes[j]);
                    } else if (is_ancestor_of(nodes[j], nodes[i])) {
                        to_delete.insert(nodes[i]);
                    } else {
                        to_delete.insert(nodes[j]);
                    }
                }
            }
        }
    }
    
    if (to_delete.empty()) return;
    
    std::function<void(Node*, Node*, bool)> remove_node = [&](Node* current, Node* target, bool is_left) {
        if (current == nullptr) return;
        
        if (current->get_left() == target) {
            clear_rec(current->get_left());
            current->set_left(nullptr);
        } else if (current->get_right() == target) {
            clear_rec(current->get_right());
            current->set_right(nullptr);
        } else {
            remove_node(current->get_left(), target, true);
            remove_node(current->get_right(), target, false);
        }
    };
    
    for (Node* del : to_delete) {
        if (del == root) {
            clear_rec(root);
            root = nullptr;
            break;
        }
        
        remove_node(root, del, false);
    }
}

void BinaryTree::remove_duplicate_subtrees_max() {
    if (root == nullptr) return;
    
    std::unordered_map<std::string, Node*> first_occurrence;
    std::stack<Node*> to_delete;
    
    std::function<void(Node*, Node*, bool)> traverse = [&](Node* node, Node* parent, bool is_left) {
        if (node == nullptr) return;
        
        traverse(node->get_left(), node, true);
        traverse(node->get_right(), node, false);
        
        std::string sig = serialize(node);
        
        if (first_occurrence.find(sig) != first_occurrence.end()) {
            if (are_equal(first_occurrence[sig], node)) {
                if (parent != nullptr) {
                    if (is_left) {
                        parent->set_left(nullptr);
                    } else {
                        parent->set_right(nullptr);
                    }
                } else {
                    root = nullptr;
                }
                to_delete.push(node);
                return;
            }
        }
        
        first_occurrence[sig] = node;
    };
    
    traverse(root, nullptr, false);
    
    while (!to_delete.empty()) {
        Node* del = to_delete.top();
        to_delete.pop();
        clear_rec(del);
    }
}