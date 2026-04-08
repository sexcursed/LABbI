#include "name.h"
#include <iostream>

Name::Name(std::string sn, std::string fn, std::string pt):first_name(fn), second_name(sn), patronymic(pt){
  build_full_name();
};

void Name::build_full_name(){
  full_name.clear();
  if(!second_name.empty()){
    full_name += second_name;
  }
  if(!first_name.empty()){
    if(!full_name.empty()) full_name += " ";
    full_name += first_name;
  }
  if(!patronymic.empty()){
    if(!full_name.empty()) full_name += " ";
    full_name += patronymic;
  }
}

void Name::print() const{
  if(full_name.empty()){
    std::cout << "Name is empty.\n";
    return;
  }
  std::cout << "Full name: " << full_name << "\n";
}

void Name::set_second_name(std::string secondn){
  second_name = secondn;
  build_full_name();
}

void Name::set_first_name(std::string firstn){
  first_name = firstn;
  build_full_name();
}

void Name::set_patronymic(std::string patr){
  patronymic = patr;
  build_full_name();
}

std::string Name::get_first_name() const{
  return first_name;
}

std::string Name::get_second_name() const{
  return second_name;
}

std::string Name::get_patronymic() const{
  return patronymic;
}

std::string Name::get_full_name() const{
  return full_name;
}