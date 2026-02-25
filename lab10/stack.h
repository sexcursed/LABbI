#include <string>

class Stack {
private:
    int data[100];
    int head;
    
public:
    Stack();
    
    void push(int value);
    int pop();
    void clear();
    int top() const;
    int size() const;
    bool is_empty() const;
    void print() const;
    
    void fill_manual(int N);
    void fill_random(int N);
    void fill_from_file(const std::string& filename);
    
    void Dynamic5();
};