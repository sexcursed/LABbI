#include "tasks.h"
#include "io.h"

void STL2Seq3(std::vector<int>& v){
  if(v.size() % 2 != 0 or v.size() == 0){
    std::cout << "Необходимо четное кол-во элементов.\n";
    return;
  }
  auto begin = v.begin();
  auto end = v.end();
  auto middle = begin + (v.size()/2);
  print_container(v.begin(), v.end());
  print_container(middle, end);
  print_container(begin, middle);
};

void STL2Seq10(std::list<int>& l){
  if(l.size() % 3 != 0 or l.size() == 0){
    std::cout << "Необходимо кол-во элементов, которое делится на 3.\n";
    return;
  }
  auto third_end = std::next(l.begin(), l.size() / 3);
  auto reverse_begin = std::make_reverse_iterator(third_end);
  auto reverse_end = std::make_reverse_iterator(l.begin());

  print_container(l.begin(),l.end());
  l.insert(l.end(), reverse_begin, reverse_end);
  print_container(l.begin(),l.end());
}

void STL1Iter10(std::vector<int>& source){
  if(source.size() < 2){
    std::cout << "Необходимо кол-во элементов, большее 2.\n";
    return;
  }
  int i = 0;
  std::list<int> answer;
  print_container(source.begin(), source.end());
  std::remove_copy_if(source.begin(), source.end(), std::back_inserter(answer),[&i](int& a){
    bool to_remove = (i % 2 != 0);
    i++;
    return to_remove;
  });
  print_container(answer.begin(), answer.end());
}