#include "task1.h"
#include "task2.h"
#include "task3.h"
//#include <windows.h>

int main(){

  //SetConsoleCP(1251);
  //SetConsoleOutputCP(1251);
  

  int choice;
  std::cout << "Выберете задачу 1 - 3\n";
  std::cin >> choice;

  switch (choice)
  {
    case 1:{
      int N;
      std::cout << "Введите кол-во клиентов\n";
      std::cin >> N;
      answer1(N);
      break;
    }
    case 2:{
      int N;
      std::cout << "Введите кол-во фигур\n";
      std::cin >> N;
      answer2(N);
      break;
    }
    case 3:{
      std::vector <Point> tempPol = inputPolygon();
      answer3(tempPol);
      break;
    }
  }

  return 0;
}