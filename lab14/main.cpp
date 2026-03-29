#include <windows.h>
#include "tasks.h"
#include "io.h"

void setConsoleUTF8(){
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}

int main(){
  setConsoleUTF8();
  tasks_handler();
  return 0;
}