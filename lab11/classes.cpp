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

DoubleCircularList::DoubleCircularList() : head(nullptr), tail(nullptr), count(0), circular(false) {
    std::cout << "Создан двусвязный список (режим: " << (circular ? "циклический" : "обычный") << ")\n";
}

DoubleCircularList::~DoubleCircularList() {
    clear();
    std::cout << "Список удален\n";
}

void DoubleCircularList::make_circular_connections() {
    if (!circular || count < 2 || !head || !tail) return;
    
    tail->next = std::move(head->next);
    head->next = std::move(tail->next);
    head->prev = tail;
};

void DoubleCircularList::break_circular_connections() {
    if (!head || !tail) return;
    
    if (tail->next.get() == head.get()) {
        tail->next.release();
    }
    if (head->prev == tail) {
        head->prev = nullptr;
    }
}

void DoubleCircularList::set_circular(bool enable) {
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

bool DoubleCircularList::is_empty() const {
    return head == nullptr;
}

int DoubleCircularList::size() const {
    return count;
}

void DoubleCircularList::push_front(const std::string& val) {
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

void DoubleCircularList::push_back(const std::string& val) {
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

void DoubleCircularList::insert_after(const std::string& target, const std::string& val) {
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

void DoubleCircularList::insert_before(const std::string& target, const std::string& val) {
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

void DoubleCircularList::remove_first() {
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

void DoubleCircularList::remove_last() {
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

void DoubleCircularList::remove_by_value(const std::string& val) {
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

Node* DoubleCircularList::find(const std::string& val) const {
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

std::string DoubleCircularList::front() const {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return "";
    }
    return head->value;
}

std::string DoubleCircularList::back() const {
    if (is_empty()) {
        std::cout << "Список пуст\n";
        return "";
    }
    return tail->value;
}

void DoubleCircularList::clear() {
    if (is_empty()) return;
    
    if (circular) {
        break_circular_connections();
    }
    
    head.reset();
    tail = nullptr;
    std::cout << "Список очищен\n";
}

void DoubleCircularList::print() const {
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


void DoubleCircularList::fill_manual(int N) {
    for (int i = 0; i < N; ++i) {
        std::string x;
        std::cout << "Введите элемент #" << (i + 1) << ": ";
        std::cin >> x;
        push_back(x);
    }
}

void DoubleCircularList::fill_random(int N) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }
    
    for (int i = 0; i < N; ++i) {
        int num = -1000 + rand() % 2001;
        push_back(std::to_string(num));
    }
    std::cout << "Список заполнен " << N << " случайными числами\n";
}

void DoubleCircularList::fill_from_file(const std::string& filename) {
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

void DoubleCircularList::list_work42() {
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
    
    if (count >= 2 && head && tail) {
      make_circular_connections();
    }
    
    if (count >= 3) {
        list_work42();
    } else {
        std::cout << "Финальный результат:\n";
        print();
        std::cout << "Удалено элементов: " << (original_count - count) << "\n";
    }
}


void DoubleCircularList::print_with_barrier() const {
    if (!head) {
        std::cout << "Список не инициализирован\n";
        return;
    }

    Node* barrier = head.get();
    Node* current = barrier->next.get();

    if (current == nullptr || current == barrier) {
        std::cout << "Список содержит только барьерный элемент [" << barrier->value << "]\n";
        return;
    }

    std::cout << "Барьер(" << barrier->value << ") -> ";

    while (current && current != barrier) {
        std::cout << current->value;

        if (current->next && current->next.get() != barrier) {
            std::cout << " <-> ";
        }

        current = current->next.get();
    }

    std::cout << " -> Барьер(" << barrier->value << ")\n";
};

void DoubleCircularList::list_work68(std::string filename){
    std::ofstream output(filename);
    Node* prev = tail;
    Node* current = head.get();

    while(count > 0){
        output << current->value << "\n";

        std::unique_ptr<Node> to_delete;
        if(count == 1){
            head.reset();
        }
        else if(current == head.get()){
            to_delete = std::move(head);
            head = std::move(to_delete->next);
            current = head.get();
        }
        else{
            to_delete = std::move(prev->next);
            prev->next = std::move(to_delete->next);
            if(to_delete.get() == tail) tail = prev;
            current = (prev->next) ? prev->next.get() : head.get();
        }
        count--;
        if(count == 0) break;
        for(int i = 0; i < 3; ++i){
            prev = current;
            current = (current->next) ? current->next.get() : head.get();
        }
    }
}

void DoubleCircularList::text_task() const{
    if (!head) return;

    Node* start_node = head.get();
    bool found_positive = false;
    for (int i = 0; i < count; ++i) {
        if (std::stoi(start_node->value) >= 0) {
            found_positive = true;
            break;
        }
        start_node = (start_node->next) ? start_node->next.get() : head.get();
    }

    if (!found_positive) {
        std::cout << "Все элементы отрицательные. Длина: " << count << std::endl;
        return;
    }

    std::vector<int> current_seq;
    std::vector<int> max_seq;
    
    Node* current = (start_node->next) ? start_node->next.get() : head.get();

    for (int i = 0; i < count; ++i) {
        if (std::stoi(current->value) < 0) {
            current_seq.push_back(std::stoi(current->value));
        } else {
            if (current_seq.size() > max_seq.size()) {
                max_seq = current_seq;
            }
            current_seq.clear();
        }
        current = (current->next) ? current->next.get() : head.get();
    }

    if (current_seq.size() > max_seq.size()) {
        max_seq = current_seq;
    }

    std::cout << "Максимальная последовательность: ";
    for (int x : max_seq) std::cout << x << " ";
    std::cout << "\nДлина: " << max_seq.size() << std::endl;
}