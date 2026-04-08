#pragma once
#include "name.h"
#include <memory>
#include <string>
#include <iostream>

class Person{
  private:
    Name name;
    int height;
    std::shared_ptr<Person> father;
  
  public:
    Person(Name n, int h, std::shared_ptr<Person> f);
    Person(std::string n, int h) : Person(Name("",n),h,nullptr) {};
    Person(std::string n, int h, std::shared_ptr<Person> f) : Person(Name("",n), h, f) {};
    Person(Name n, int h) : Person(n,h,nullptr) {};

    void print() const;

    std::string get_first_name() const;
    std::string get_second_name() const;
    std::string get_patronymic() const;
};