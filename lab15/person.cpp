#include "person.h"

Person::Person(Name n, int h, std::shared_ptr<Person> f): name(n), father(f){

  height = h;
  if(father){
    if(name.get_second_name().empty() and !father->name.get_second_name().empty()){
      name.set_second_name(father->name.get_second_name());
    }
    if(name.get_patronymic().empty() and !father->name.get_first_name().empty()){
      name.set_patronymic(father->name.get_first_name() + "ович");
    }
  }
  name.build_full_name();
}


void Person::print() const{
  std::cout << name.get_full_name() << ", " << height << std::endl;
}

std::string Person::get_first_name() const{
  return name.get_first_name();
}

std::string Person::get_second_name() const{
  return name.get_second_name();
}

std::string Person::get_patronymic() const{
  return name.get_patronymic();
}