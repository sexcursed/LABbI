#include "cat.h"

Cat::Cat(std::string n) : name(n){};

std::string Cat::to_string() const{
  return "кот:" + name;
}

void Cat::meow(int n) const{
  std::cout << name << ": ";
  for(int i = 0; i < n; ++i){
    if(i > 0) std::cout << "-мяу";
    else std::cout << "мяу";
  }
  std::cout << "!\n";
}

void Cat::print() const{
  std::cout << to_string() + "\n";
}