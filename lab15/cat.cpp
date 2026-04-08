#include "cat.h"

Cat::Cat(std::string n) : name(n){};

std::string Cat::to_string() const{
  return "cat:" + name;
}

void Cat::meow(int n) const{
  std::cout << name << ": ";
  for(int i = 0; i < n; ++i){
    if(i > 0) std::cout << "-meow";
    else std::cout << "meow";
  }
  std::cout << "!\n";
}

void Cat::print() const{
  std::cout << to_string() + "\n";
}