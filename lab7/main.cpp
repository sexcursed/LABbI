#include "task1.h"
#include "task2.h"
#include "task3.h"

int main(){
  int choice;
  std::cout << "Введите номер задачи\n1 - Sort3\n2 - ExamTaskC15\n3 - Five13\n";
  std::cin >> choice;
  switch(choice){
    case 1:{
      answer1();
      break;
    }
    case 2:{
      answer2();
      break;
    }
    case 3:{
      answer3();
      break;
    }
  }
  return 0;
}