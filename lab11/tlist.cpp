#include "classes.h"
#include <iostream>

TList::TList(DoubleCircularList& lst) : list(&lst) {
  First = lst.get_head();
  Last = lst.get_tail();
  Current = nullptr; 
  std::cout << "Создан объект TList\n";
}

TList::~TList() {
  std::cout << "Объект TList удален\n";
}

void TList::to_first() {
  if (First != nullptr) {
    Current = First;
    std::cout << "Текущим стал первый элемент: " << Current->value << "\n";
  } else {
    std::cout << "Список пуст\n";
  }
}

void TList::to_next() {
  if (Current == nullptr) {
    std::cout << "Текущий элемент не определен\n";
    return;
  }
  
  if (Current->next.get() != nullptr && Current->next.get() != First) {
    Current = Current->next.get();
    std::cout << "Текущим стал следующий элемент: " << Current->value << "\n";
  } else {
    std::cout << "Следующего элемента не существует\n";
  }
}

void TList::set_data(int D) {
  if (Current != nullptr) {
    std::string old_value = Current->value;
    Current->value = std::to_string(D);
    std::cout << "Значение элемента изменено с " << old_value << " на " << Current->value << "\n";
  } else {
    std::cout << "Текущий элемент не определен\n";
  }
}

bool TList::is_last() const {
  if (Current == nullptr) {
    std::cout << "Текущий элемент не определен\n";
    return false;
  }
  return (Current == Last);
}

void TList::insert_last(int D) {

  list->push_back(std::to_string(D));

  First = list->get_head();
  Last = list->get_tail();
  Current = Last;
  
  std::cout << "Элемент " << D << " добавлен в конец и стал текущим\n";
}


int TList::get_size() const {
  if (First == nullptr) return 0;
  
  int count = 0;
  Node* temp = First;
  while (temp != nullptr) {
    count++;
    if (temp == Last) break;
    temp = temp->next.get();
  }
  return count;
}


void TList::print_addresses() const {
  std::cout << "\nАдрес первого элемента (First): " << First << "\n";
  std::cout << "Адрес последнего элемента (Last): " << Last << "\n";
  std::cout << "Адрес текущего элемента (Current): " << Current << "\n";
  
  if (Current != nullptr) {
      std::cout << "Значение текущего элемента: " << Current->value << "\n";
  }
}

void TList::list_work45() {
  
  if (First == nullptr) {
    std::cout << "Список пуст\n";
    return;
  }
  
  to_first();
  
  int position = 1;
  
  while (Current != nullptr) {
    if (position % 2 == 1) {
      set_data(0);
    }
    if (is_last()) {
      std::cout << "Достигнут последний элемент\n";
      break;
    }
    to_next();
    position++;
  }
  
  Current = Last;
  if (Current != nullptr) {
    std::cout << "Текущим стал последний элемент: " << Current->value << "\n";
  }
  
  std::cout << "Количество элементов в списке: " << position << "\n";
  print_addresses();
}


void TList::list_work46() {

  if (First == nullptr || First->next.get() == nullptr || First->next.get() == First) {
    std::cout << "Список пуст\n";
    return;
  }


  Current = First->next.get(); 
  std::cout << "Текущим стал первый элемент после барьера: " << Current->value << "\n";

  int count = 0; 
  int index = 1; 

  while (Current != First) {
    count++;

    if (index % 2 != 0) {
      std::string old_val = Current->value;
      Current->value = "0";
      std::cout << "Элемент #" << index << " обнулен (был: " << old_val << ")\n";
    }

    Node* next_node = Current->next.get();
      
    if (next_node == nullptr) {
      break;
    }

    Current = next_node;
    index++;

  }

  std::cout << "Количество элементов в списке: " << count << "\n";
  
  Current = First; 
  std::cout << "Текущим элементом стал барьер. Адрес (Current): " << Current << "\n";
};