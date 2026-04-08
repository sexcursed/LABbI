#pragma once
#include <string>
#include <iostream>

class Cat{
  private:
    std::string name;
  public:
    Cat(std::string n);
    std::string to_string() const;
    void print() const;
    void meow(int n = 1) const;
};