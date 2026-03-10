#include "classes.h"
#include <iostream>
#include <windows.h>

void setConsoleUTF8(){
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}

int main(){
  setConsoleUTF8();
  
  int choice;
  std::cout << "Выберете задачу 1-5:\n";
  std::cin >> choice;
  switch (choice)
  {
    case 1:{}
    case 2:{
      CircularList list;
      list.set_circular(true);
      int fill_type;
      std::cout << "Выберете тип заполнения(1 - ручной, 2 - рандом, 3 - из файла): ";
      std::cin >> fill_type;
      switch (fill_type)
      {
        case 1:{
          int N;
          std::cout << "Введите кол-во чисел:";
          std::cin >> N;
          list.fill_manual(N);
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
      list.list_work42();
      break;
    }
    case 3:{
      CircularList list;
      int fill_type;
      std::cout << "Выберете тип заполнения(1 - ручной, 2 - рандом, 3 - из файла): ";
      std::cin >> fill_type;
      switch (fill_type)
      {
        case 1:{
          int N;
          std::cout << "Введите кол-во чисел:";
          std::cin >> N;
          list.fill_manual(N);
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
      list.list_work43();
      break;
    }
    case 4:{
      CircularList list;
      int fill_type;
      std::cout << "Выберете тип заполнения(1 - ручной, 2 - рандом, 3 - из файла): ";
      std::cin >> fill_type;
      switch (fill_type)
      {
        case 1:{
          int N;
          std::cout << "Введите кол-во чисел:";
          std::cin >> N;
          list.fill_manual(N);
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
      list.list_work46();
      break;
    }
    case 5:{}
    default:{}
  }
}