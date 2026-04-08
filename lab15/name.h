#pragma once
#include <string>

class Name{
  private:
    std::string first_name;
    std::string second_name;
    std::string patronymic;
    std::string full_name;

  public:
    Name(std::string sn="", std::string fn="", std::string pt="");

    void build_full_name();
    void print() const;

    void set_first_name(std::string firstn);
    void set_second_name(std::string secondn);
    void set_patronymic(std::string patr);

    std::string get_first_name() const;
    std::string get_second_name() const;
    std::string get_patronymic() const;
    std::string get_full_name() const;
};