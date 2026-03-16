#include "classes.h"
#include <iostream>
//#include <windows.h>

/*
void setConsoleUTF8(){
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}
*/

int main(){
  //setConsoleUTF8();
  
  int choice;
  std::cout << "Выберете задачу (1-5):\n";
  std::cin >> choice;
  switch (choice)
  {
    case 1:{
      DoubleCircularList list;
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
      std::string f_name;
      std::cout << "Введите название файла:";
      std::cin >> f_name;
      list.list_work68(f_name);
      list.print();
      break;
    }
    case 2:{
      DoubleCircularList list;
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
      DoubleCircularList list;
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
      TList tlist(list);
      tlist.print_addresses();
      tlist.list_work45();
      list.print();
      break;
    }
    case 4:{
      DoubleCircularList list;
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
      list.set_circular(true);
      list.print();
      TList tlist(list);
      tlist.list_work46();
      list.print_with_barrier();
      break;
    }
    case 5:{
      DoubleCircularList list;
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
      list.text_task();
      break;
    }
    default:{
      std::cout << "Неверный выбор\n";
      break;
    }
  }
  return 0;
}

/*
1. list_work68 - выводит содержимое кольца с шагом 4 в файл
2. list_work42 - удалить элементы с одинаковыми соседями, также вернуть ссылку на последний элемент
3. list_work45 - удалить с помощью TList элементы на нечет позициях и вывести всякую инфу
4. list_work48 - то же самое с барьерным элементом
5. 3 текстовая задача - в циклич списке найти последовательность отрицательных чисел максимальной длины
*/