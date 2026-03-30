//#include <windows.h>
#include "tasks.h"
#include "io.h"

/*
void setConsoleUTF8(){
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}
*/

int main(){
  //setConsoleUTF8();
  tasks_handler();
  return 0;
}

/*
STL5Assoc2 - дан вектор0 и набор векторов, найти кол-во векторов, в которых содержатся все элементы вектора0
STL5Assoc17 - определить суммарную длину слов с каждой буквы из вектора со словами
STL5Assoc21 - сгруппировать числа из вектора по последней цифре
*/