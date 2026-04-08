#include "city.h"

City::City(std::string n): name(n){};

void City::add_path(City* target, int cost){
  paths[target] = cost;
}

std::string City::get_name() const{
  return name;
}

void City::print() const{
  std::cout << "Name: " << name << "\n";

  bool first = true;
  for(std::pair<City*, int> item : paths){
    if(!first) std::cout << ", ";
    std::cout << item.first->get_name() << ":" << item.second;
    first = false;
  }
  
  std::cout << "\n";
}