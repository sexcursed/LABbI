#include "linked_list.h"
#include "stack.h"
#include <windows.h>

void setConsoleUTF8(){
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}
int main(){
  setConsoleUTF8();
  int choice;
  std::cout << "Выбор задания (1 - 5):";
  std::cin >> choice;
  switch (choice)
  {
    case 1:{
      Stack stack;
      int fill_type;
      std::cout << "Выберете тип заполнения(1 - ручной, 2 - рандом, 3 - из файла): ";
      std::cin >> fill_type;
      switch (fill_type)
      {
        case 1:{
          stack.fill_manual(10);
          break;
        }
        case 2:{
          int N;
          std::cout << "Введите кол-во чисел:";
          std::cin >> N;
          stack.fill_random(N);
          break;
        }
        case 3:{
          std::string filename;
          std::cout << "Введите название файла: ";
          std::cin >> filename;
          stack.fill_from_file(filename);
          break;
        }
      }
      stack.print();
      stack.Dynamic5();
      break;
    }
    case 3:{
      int fill_type;
      LinkedList list;
      std::cout << "Выберете тип заполнения(1 - ручной, 2 - рандом, 3 - из файла): ";
      std::cin >> fill_type;
      switch (fill_type)
      {
        case 1:{
          list.fill_manual();
          break;
        }
        case 2:{
          int N;
          std::cout << "Введите кол-во чисел:";
          std::cin >> N;
          list.fill_random(N);
          break;
        }
        case 3:{
          std::string filename;
          std::cout << "Введите название файла: ";
          std::cin >> filename;
          list.fill_from_file(filename);
          break;
        }
      }
      list.print();
      list.ListWork3();
      break;
    }
    case 4:{
      int fill_type;
      std::string M;
      std::cout << "Введите число M:";
      std::cin >> M;
      LinkedList list;
      std::cout << "Выберете тип заполнения(1 - ручной, 2 - рандом, 3 - из файла): ";
      std::cin >> fill_type;
      switch (fill_type)
      {
        case 1:{
          list.fill_manual();
          break;
        }
        case 2:{
          int N;
          std::cout << "Введите кол-во чисел:";
          std::cin >> N;
          list.fill_random(N);
          break;
        }
        case 3:{
          std::string filename;
          std::cout << "Введите название файла: ";
          std::cin >> filename;
          list.fill_from_file(filename);
          break;
        }
      }
      list.print();
      list.ListWork24(M);
      list.print();
      break;
    }
    case 5:{
      LinkedList list;
      list.ListWork61("input4.txt");
      list.print();
      break;
    }
  }
  
  return 0;
}