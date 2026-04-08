#pragma once
#include <string>
#include <map>
#include <iostream>


class City{
  private:
    std::string name;
    std::map<City*, int> paths;

  public:
    City(std::string n);

    void add_path(City* target, int cost);
    void print() const;
    std::string get_name() const;
};