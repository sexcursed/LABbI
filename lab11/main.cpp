#include "classes.h"
#include <windows.h>

void setConsoleUTF8(){
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}

int main(){
  setConsoleUTF8();
  CircularList list;
  list.set_circular(true);
  list.fill_manual(4);
  list.list_work42();
  return 0;
}