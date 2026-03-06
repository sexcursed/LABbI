#include "classes.h"
#include <fstream>
#include <iostream>
#include <vector>

Node::Node(const std::string& val) : value(val), next(nullptr), prev(nullptr) {
    // std::cout << "Создан элемент: " << value << "\n";
}

Node::~Node() {
    // std::cout << "Удален элемент: " << value << "\n";
}

CircularList::CircularList() : head(nullptr), tail(nullptr), count(0), circular(false) {
    std::cout << "Создан двусвязный список (режим: " << (circular ? "циклический" : "обычный") << ")\n";
}

CircularList::~CircularList() {
    clear();
    std::cout << "Список удален\n";
}

void CircularList::make_circular_connections() {
    if (!circular || count < 2 || !head || !tail) return;
    
    tail->next = std::move(head->next);
    head->next = std::move(tail->next);
    head->prev = tail;
};

void CircularList::break_circular_connections() {
    if (!head || !tail) return;
    
    if (tail->next.get() == head.get()) {
        tail->next.release();
    }
    if (head->prev == tail) {
        head->prev = nullptr;
    }
}

void CircularList::set_circular(bool enable) {
    if (circular == enable) return;
    
    circular = enable;
    
    if (circular && count >= 2) {
        make_circular_connections();
        std::cout << "Включен циклический режим\n";
    } else if (!circular && count >= 2) {
        break_circular_connections();
        std::cout << "Выключен циклический режим\n";
    }
}

bool CircularList::is_empty() const {
    return head == nullptr;
}

int CircularList::size() const {
    return count;
}

void CircularList::push_front(const std::string& val) {
    auto new_node = std::make_unique<Node>(val);
    Node* new_node_ptr = new_node.get();
    
    if (is_empty()) {
        head = std::move(new_node);
        tail = new_node_ptr;
    } else {
        new_node->next = std::move(head);
        head = std::move(new_node);
        head->next->prev = head.get();
        
        if (count == 1) {
            tail = head->next.get();
        }
    }
    count++;
    
    if (circular && count >= 2) {
        make_circular_connections();
    }
    
    std::cout << "Элемент " << val << " добавлен в начало\n";
}

void CircularList::push_back(const std::string& val) {
    auto new_node = std::make_unique<Node>(val);
    Node* new_node_ptr = new_node.get();
    
    if (is_empty()) {
        head = std::move(new_node);
        tail = new_node_ptr;
    } else {
        new_node->prev = tail;
        tail->next = std::move(new_node);
        tail = new_node_ptr;
    }
    count++;
    
    if (circular && count >= 2) {
        make_circular_connections();
    }
    
    std::cout << "Элемент " << val << " добавлен в конец\n";
}

void CircularList::insert_after(const std::string& target, const std::string& val) {
    Node* target_node = find(target);
    if (!target_node) {
        std::cout << "Элемент " << target << " не найден\n";
        return;
    }
    
    auto new_node = std::make_unique<Node>(val);
    Node* new_node_ptr = new_node.get();
    
    new_node->prev = target_node;
    
    if (target_node->next) {
        new_node->next = std::move(target_node->next);
        target_node->next = std::move(new_node);
        if (new_node->next) {
            new_node->next->prev = new_node_ptr;
        }
    } else {
        target_node->next = std::move(new_node);
        if (target_node == tail) {
            tail = new_node_ptr;
        }
    }
    
    count++;
    
    if (circular && count >= 2) {
        make_circular_connections();
    }
    
    std::cout << "Элемент " << val << " вставлен после " << target << "\n";
}

void CircularList::insert_before(const std::string& target, const std::string& val) {
    Node* target_node = find(target);
    if (!target_node) {
        std::cout << "Элемент " << target << " не найден\n";
        return;
    }
    
    if (target_node == head.get()) {
        push_front(val);
        return;
    }
    
    auto new_node = std::make_unique<Node>(val);
    Node* new_node_ptr = new_node.get();
    Node* prev_node = target_node->prev;
    
    new_node->prev = prev_node;
    new_node->next = std::move(prev_node->next);
    prev_node->next = std::move(new_node);
    
    if (new_node->next) {
        new_node->next->prev = new_node_ptr;
    }
    
    count++;
    
    if (circular && count >= 2) {
        make_circular_connections();
    }
    
    std::cout << "Элемент " << val << " вставлен перед " << target << "\n";
}

void CircularList::remove_first() {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }
    
    std::string removed_value = head->value;
    
    if (count == 1) {
        head.reset();
        tail = nullptr;
    } else {
        head = std::move(head->next);
        head->prev = nullptr;
        if (circular) {
            break_circular_connections();
        }
    }
    count--;
    
    std::cout << "Удален первый элемент: " << removed_value << "\n";
}

void CircularList::remove_last() {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }
    
    std::string removed_value = tail->value;
    
    if (count == 1) {
        head.reset();
        tail = nullptr;
    } else {
        Node* new_tail = tail->prev;
        new_tail->next.release();
        tail = new_tail;
        
        if (circular) {
            break_circular_connections();
        }
    }
    count--;
    
    std::cout << "Удален последний элемент: " << removed_value << "\n";
}

void CircularList::remove_by_value(const std::string& val) {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }
    
    if (head->value == val) {
        remove_first();
        return;
    }
    
    if (tail->value == val) {
        remove_last();
        return;
    }
    
    Node* current = head.get();
    while (current && current->value != val) {
        current = current->next.get();
    }
    
    if (current) {
        current->prev->next = std::move(current->next);
        if (current->next) {
            current->next->prev = current->prev;
        }
        count--;
        std::cout << "Удален элемент: " << val << "\n";
    } else {
        std::cout << "Элемент " << val << " не найден\n";
    }
}

Node* CircularList::find(const std::string& val) const {
    if (is_empty()) return nullptr;
    
    Node* current = head.get();
    Node* stop_point = circular ? head.get() : nullptr;
    
    do {
        if (current->value == val) {
            return current;
        }
        current = current->next.get();
    } while (current && current != stop_point);
    
    return nullptr;
}

std::string CircularList::front() const {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return "";
    }
    return head->value;
}

std::string CircularList::back() const {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return "";
    }
    return tail->value;
}

void CircularList::clear() {
    if (is_empty()) return;
    
    if (circular) {
        break_circular_connections();
    }
    
    head.reset();
    tail = nullptr;
    std::cout << "Список очищен\n";
}

void CircularList::print() const {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return;
    }
    
    Node* current = head.get();
    Node* stop_point = circular ? head.get() : nullptr;
    
    do {
        std::cout << current->value;
        current = current->next.get();
        
        if (current && current != stop_point) {
            std::cout << " <-> ";
        }
    } while (current && current != stop_point);
    
    std::cout << "\n";
}


void CircularList::fill_manual(int N) {
    for (int i = 0; i < N; ++i) {
        std::string x;
        std::cout << "Введите элемент #" << (i + 1) << ": ";
        std::cin >> x;
        push_back(x);
    }
}

void CircularList::fill_random(int N) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }
    
    for (int i = 0; i < N; ++i) {
        int num = rand() % 1000 + 1;
        push_back(std::to_string(num));
    }
    std::cout << "Список заполнен " << N << " случайными числами\n";
}

void CircularList::fill_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл\n";
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            push_back(line);
        }
    }
    file.close();
    std::cout << "Файл успешно считан в список\n";
}

void CircularList::list_work42() {
    if (!circular) {
        std::cout << "Необходим циклический режим\n";
        return;
    }
    if (count < 3) {
        std::cout << "В списке недостаточно элементов\n";
        return;
    }
    
    std::cout << "Cписок:\n";
    print();

    int original_count = count;
    bool found = false;
    
    Node* current = head.get();
    Node* first = head.get();
    
    do {
        Node* left = current->prev;
        Node* right = current->next.get();
        
        if (left && right && left->value == right->value) {
            std::string value_to_delete = current->value;
            
            remove_by_value(value_to_delete);
            found = true;
            break;
        }
        
        current = current->next.get();
    } while (current != first);
    
    if (!found) {
        std::cout << "Элементов для удаления не найдено\n";
        return;
    }
    
    // Восстанавливаем циклические связи
    if (count >= 2 && head && tail) {
      make_circular_connections();
    }
    
    // Рекурсивно вызываем метод снова, пока есть что удалять
    if (count >= 3) {
        list_work42();
    } else {
        std::cout << "Финальный результат:\n";
        print();
        std::cout << "Удалено элементов: " << (original_count - count) << "\n";
    }
}

