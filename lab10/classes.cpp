#include "classes.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>


Node::Node(const std::string& val) : value(val), next(nullptr) {
    //std::cout << "Создан элемент: " << value << "\n";
}

Node::~Node() {
    //std::cout << "Удален элемент: " << value << "\n";
}


LinkedList::LinkedList() : head(nullptr), tail(nullptr) {
    std::cout << "Создан односвязный список\n";
}

LinkedList::~LinkedList() {
    std::cout << "Список удален\n";
}

bool LinkedList::is_empty() const { 
    return head == nullptr;
}

void LinkedList::push_back(const std::string& val) {
    std::unique_ptr<Node> new_node = std::make_unique<Node>(val);
    Node* new_node_ptr = new_node.get();
    
    if (is_empty()) {
        head = std::move(new_node);
        tail = new_node_ptr;
    } else {
        tail->next = std::move(new_node);
        tail = new_node_ptr;
    }
    //std::cout << "Добавлен элемент: " << val << "\n";
}

Node* LinkedList::find(const std::string& val) const {
    Node* current = head.get();
    while (current && current->value != val) {
        current = current->next.get();
    }
    return current;
}

void LinkedList::remove_first() {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }

    head = std::move(head->next);
    if (head == nullptr) {
        tail = nullptr;
    }
    std::cout << "Элемент успешно удален\n";
}

void LinkedList::remove_last() {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }
    
    if (head->next == nullptr) {
        std::cout << "Удален единственный элемент: " << head->value << "\n";
        head.reset();
        tail = nullptr;
        return;
    }

    Node* current = head.get();
    while (current->next && current->next->next) {
        current = current->next.get();
    }
    
    if (current->next) {
        std::cout << "Удален последний элемент: " << current->next->value << "\n";
        current->next.reset();
        tail = current;
    }
}

void LinkedList::remove_by_value(const std::string& val) {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }
    
    if (head->value == val) {
        remove_first();
        return;
    }
    
    Node* current = head.get();
    while (current->next && current->next->value != val) {
        current = current->next.get();
    }

    if (current->next) {
        std::cout << "Удален элемент: " << val << "\n";
        Node* temp = current->next.get();
        if (temp == tail) {
            tail = current;
        }
        current->next = std::move(current->next->next);
    } else {
        std::cout << "Элемент " << val << " не существует\n";
    }
}

void LinkedList::print() const {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }

    Node* current = head.get();
    while (current) {
        std::cout << current->value;
        if (current->next) std::cout << " -> ";
        current = current->next.get();
    }
    std::cout << "\n";
}

void LinkedList::clear() {
    head.reset();
    tail = nullptr;
    std::cout << "Список очищен\n";
}

void LinkedList::fill_manual(int N) {
    for(int i = 0; i < N; ++i){
        std::string x;
        std::cout << "Введите элемент #" << (i + 1) << ": ";
        std::cin >> x;
        push_back(x);
    }
}

void LinkedList::fill_random(int N) {
    static bool seeded = false;
    if (!seeded){
        srand(time(nullptr));
        seeded = true;
    }
    
    for (int i = 0; i < N; ++i){
        int num = rand() % 1000 + 1;
        push_back(std::to_string(num));
    }
    std::cout << "Список заполнен " << N << " случайными числами\n";
}

void LinkedList::fill_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()){
        std::cerr << "Не удалось открыть файл\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)){
        if (line.empty()) {
            continue;
        }
        push_back(line);
    }
    file.close();
    std::cout << "Файл успешно считан в список\n";
}

void LinkedList::ListWork24(std::string M) {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }
    
    Node* current = head.get();
    int count = 1;
    
    while (current) {
    if (count % 4 == 0) {
        std::unique_ptr<Node> new_node = std::make_unique<Node>(M);
        Node* new_node_ptr = new_node.get();
        
        new_node->next = std::move(current->next);
        current->next = std::move(new_node);
        
        if (current == tail) {
            tail = new_node_ptr;
        }
        
        current = new_node_ptr->next.get();
    } 
    else{
        current = current->next.get();
    }
    count++;
    }
    
    std::cout << "Указатель на tail: " << tail << "\n";
}

void LinkedList::ListWork61(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл\n";
        return;
    }

    clear();

    int N;
    file >> N;

    if(file.fail() or N <= 0){
        std::cerr << "Некорректное N в файле\n";
        return;
    }

    for(int i = 0; i < N; ++i){
        int value;
        file >> value;

        if(file.fail()){
            std::cerr << "Недостаточно чисел в файле\n";
            return;
        }

        insert_sorted(std::to_string(value));
    }
    file.close();
    std::cout << "Файл успешно обработан\n";
}

void LinkedList::insert_sorted(const std::string& val) {
    std::unique_ptr<Node> new_node = std::make_unique<Node>(val);
    
    int int_val = std::stoi(val);
    if (!head) {
        new_node->next = std::move(head);
        head = std::move(new_node);
        tail = head.get();
        return;
    }
    
    int first_val = std::stoi(head->value);
    if (int_val < first_val) {
        new_node->next = std::move(head);
        head = std::move(new_node);
        if (!head->next) {
            tail = head.get();
        }
        return;
    }
    
    Node* current = head.get();
    while (current->next) {
        int current_next_val = std::stoi(current->next->value);
        if (current_next_val < int_val) {
            current = current->next.get();
        } else {
            break;
        }
    }
    
    new_node->next = std::move(current->next);
    current->next = std::move(new_node);
    
    if (!current->next->next) {
        tail = current->next.get();
    }
}

void LinkedList::ListWork3() {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }
    
    Node* current = head.get();
    int count = 1;
    
    while (current && count < 4) {
        current = current->next.get();
        count++;
    }
    
    if (count == 4 && current) {
        std::cout << "Найден 4-й элемент: " << current->value << "\n" << "Указатель на него: " << current << "\n";
    } else {
        std::cout << "В списке меньше 4 элементов\n";
    }
}

Stack::Stack() : head(nullptr), count(0) {
    std::cout << "Стек создан\n";
}
Stack::~Stack() {
    std::cout << "Стек удален\n";
}

void Stack::push(const std::string& value) {
    auto newNode = std::make_unique<Node>(value);
    newNode->next = std::move(head);
    head = std::move(newNode);
    count++;
    std::cout << "Элемент добавлен в стек\n";
}

std::string Stack::pop() {
    if (is_empty()) {
        std::cout << "Стек пуст\n";
        return "";
    }
    
    std::string value = head->value;
    head = std::move(head->next);
    count--;
    
    return value;
}

void Stack::clear() {
    while (!is_empty()) {
        head = std::move(head->next);
    }
    count = 0;
    std::cout << "Стек очищен\n";
}

std::string Stack::top() const {
    if (is_empty()) {
        std::cout << "Стек пуст\n";
        return "";
    }
    return head->value;
}

int Stack::size() const {
    return count;
}

bool Stack::is_empty() const {
    return head == nullptr;
}

void Stack::print() const {
    if (is_empty()) {
        std::cout << "Стек пуст\n";
        return;
    }
    
    std::cout << "Стек: ";
    Node* current = head.get();
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->next.get();
    }
    std::cout << "\n";
}

void Stack::fill_manual(int N) {
    for (int i = 0; i < N; ++i) {
        std::string x;
        std::cout << "Введите элемент #" << (i + 1) << ": ";
        std::cin >> x;
        push(x);
    }
}

void Stack::fill_random(int N) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }
    
    for (int i = 0; i < N; ++i) {
        int num = rand() % 1000 + 1;
        push(std::to_string(num));
    }
    std::cout << "Стек заполнен случайными числами\n";
}

void Stack::fill_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл\n";
        return;
    }
    
    std::string x;
    while (file >> x) {
        push(x);
    }
    file.close();
    std::cout << "Файл успешно обработан\n";
}

void Stack::Dynamic5() {
    if (is_empty()) {
        std::cout << "P2 = nullptr\n";
        return;
    }
    
    std::string D = pop();
    
    Node* P2 = nullptr;
    if (!is_empty()) {
        P2 = head.get();
    }
    
    std::cout << "D = " << D << "\n";
    if (P2 != nullptr) {
    std::cout << "P2 = указывает на вершину стека\n";
    }
    else {
    std::cout << "P2 = nullptr\n";
    }
    if (P2) {
        std::cout << "Значение по адресу P2: " << P2->value << "\n";
    }
}