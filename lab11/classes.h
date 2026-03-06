#include <memory>
#include <string>

class Node{
  public:
    std::string value;
    Node* prev;
    std::unique_ptr<Node> next;

    Node(const std::string& val);
    ~Node();
};

class CircularList{
  private:
    std::unique_ptr<Node> head;
    Node* tail;
    bool circular;
    int count;

    void make_circular_connections();
    void break_circular_connections();

public:
    CircularList();
    ~CircularList();

    bool is_empty() const;
    int size() const;
    bool is_circular() const { return circular; }
    void set_circular(bool enable);
    
    void push_front(const std::string& val);
    void push_back(const std::string& val);
    void insert_after(const std::string& target, const std::string& val);
    void insert_before(const std::string& target, const std::string& val);
    
    void remove_first();
    void remove_last();
    void remove_by_value(const std::string& val);
    Node* find(const std::string& val) const;
    
    std::string front() const;
    std::string back() const;
    
    void clear();
    void print() const;
    
    void fill_manual(int N);
    void fill_random(int N);
    void fill_from_file(const std::string& filename);

    void list_work42();
};