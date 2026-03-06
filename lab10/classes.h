#include <string>
#include <memory>
#include <iostream>

class Node {
public:
    std::string value;
    std::unique_ptr<Node> next;

    Node(const std::string& val);
    ~Node();
};

class LinkedList {
private:
    std::unique_ptr<Node> head;
    Node* tail;

public:
    LinkedList();
    ~LinkedList();

    bool is_empty() const;
    void push_back(const std::string& val);
    Node* find(const std::string& val) const;
    void remove_first();
    void remove_last();
    void remove_by_value(const std::string& val);
    void print() const;
    void clear();
    void fill_manual(int N);
    void fill_random(int N);
    void fill_from_file(const std::string& filename);
    void ListWork24(std::string M);
    void ListWork61(const std::string& filename);
    void insert_sorted(const std::string& val);
    void ListWork3();
};

class Stack {
private:
    std::unique_ptr<Node> head;
    int count;

public:
    Stack();
    ~Stack();
    
    void push(const std::string& value);
    std::string pop();
    void clear();
    std::string top() const;
    int size() const;
    bool is_empty() const;
    void print() const;
    
    void fill_manual(int N);
    void fill_random(int N);
    void fill_from_file(const std::string& filename);
    
    void Dynamic5();
};