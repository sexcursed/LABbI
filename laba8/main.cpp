#include "header.h"

int main(){
  int choice;
  std::cout << "Выберете задачу(1-3):";
  std::cin >> choice;
  switch (choice)
  {
  case 1:{
    backrec9();
    return 0;
  }
  case 2:{
    homedyn3();
    return 0;
  }
  case 3:{
    homedyn15();
    return 0;
  }
  default:{
    return 1;
  }
  }
}