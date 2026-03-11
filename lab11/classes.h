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

class DoubleCircularList{
  private:
    std::unique_ptr<Node> head;
    Node* tail;
    bool circular;
    int count;

    void make_circular_connections();
    void break_circular_connections();

public:
    DoubleCircularList();
    ~DoubleCircularList();

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
    void list_work68(std::string filename);
    void text_task() const;

    int get_size() const { return count; }
    Node* get_head() const { return head.get(); }
    Node* get_tail() const { return tail; }
    void print_with_barrier() const;
};

class TList {
  private:
    Node* First;
    Node* Last;
    Node* Current;
    DoubleCircularList* list;
  public:
    TList(DoubleCircularList& l);
    ~TList();

    void to_first();
    void to_next();
    void set_data(int D);
    bool is_last() const;
    void insert_last(int D);
    void list_work45();

    Node* get_first() const { return First; }
    Node* get_last() const { return Last; }
    Node* get_current() const { return Current; }

    void print_addresses() const;
    int get_size() const;
    void list_work46();
};
