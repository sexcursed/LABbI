#include "stack.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

Stack::Stack() : head(-1) {}

void Stack::push(int value) {
    if (head >= 99) {
        std::cout << "Стек переполнен\n";
        return;
    }
    data[++head] = value;
}

int Stack::pop() {
    if (is_empty()) {
        std::cout << "Стек пуст\n";
        return -1;
    }
    
    int value = data[head];
    data[head] = int();
    head--;
    
    return value;
}

void Stack::clear() {
    for (int i = 0; i <= head; ++i) {
        data[i] = int();
    }
    head = -1;
}

int Stack::top() const {
    if (is_empty()) {
        std::cout << "Стек пуст\n";
        return -1;
    }
    return data[head];
}

int Stack::size() const {
    return head + 1;
}

bool Stack::is_empty() const {
    return head == -1;
}

void Stack::print() const {
    if (is_empty()) {
        std::cout << "Стек пуст\n";
        return;
    }
    std::cout << "Стек (вершина слева): ";
    for (int i = head; i >= 0; --i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

void Stack::fill_manual(int N) {
    for (int i = 0; i < N; ++i) {
        int x;
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
        int x = rand() % 1000 + 1;
        push(x);
    }
}

void Stack::fill_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл\n";
        return;
    }
    
    int x;
    while (file >> x && head < 99) {
        push(x);
    }
    file.close();
    std::cout << "Файл успешно обработан\n";
}

void Stack::Dynamic5(){
    if (is_empty()) {
        std::cout << "P2 = nullptr (стек пуст)\n";
        return;
    }
    
    int D = pop();
    
    int* P2 = nullptr;
    if (!is_empty()) {
        P2 = &data[head];
    }
    
    std::cout << "D = " << D << "\n";
    std::cout << "P2 = " << P2 << "\n";
}