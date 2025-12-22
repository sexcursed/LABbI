#include "task1.h"
#include "task2.h"
#include <windows.h>

int main(){
  int N;
  std::cin >> N;
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  

  int choice;
  std::cin >> choice;

  switch (choice)
  {
    case 1:{
      answer1(N);
      break;
    }
    case 2:{
      answer2(N);
      break;
    }
  }

  return 0;
}