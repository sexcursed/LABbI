#include "tasks.h"
#include "io.h"

void STL2Seq3(std::vector<int>& v){
  if(v.size() % 2 != 0 or v.size() == 0){
    std::cout << "Необходимо четное кол-во элементов.\n";
    return;
  }
  std::vector<int>::iterator begin = v.begin();
  std::vector<int>::iterator end = v.end();
  std::vector<int>::iterator middle = begin + (v.size()/2);
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

void STL2Seq28(std::deque<int>& d){
  if(d.size() % 4 != 0){
    std::cout << "Размер дека должен быть кратным четырем.\n";
    return;
  }
  print_container(d.begin(), d.end());
  auto i = d.begin();
  auto N = d.size();
  for(auto j = 0; j < N/4; ++j){
    i = d.erase(++i);
  }
  print_container(d.begin(), d.end());
}

void STL1Iter10(){

  int i = 1;
  std::cout << "Введите 2 и более числа (ctrl+d для завершения): ";
  std::ostream_iterator<double> out_iter(std::cout, " ");

  std::remove_copy_if(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), out_iter,[&i](double){
    return (i++ % 2 != 0);
  });

}

void tasks_handler(){
  std::cout << "Выберете задачу (1 - 4):";
  int choice;
  std::cin >> choice;
  switch (choice)
  {
  case 1:{
    int N;
    std::cout << "Введите четное кол-во элементов: ";
    std::cin >> N;
    std::vector<int> vector(N);
    fill_handler(vector);
    STL2Seq3(vector);
    break;
  }
  case 2:{
    int N;
    std::cout << "Введите кол-во элементов, кратное трем: ";
    std::cin >> N;
    std::list<int> list(N);
    fill_handler(list);
    STL2Seq10(list);
    break;
  }
  case 3:{
    int N;
    std::cout << "Введите кол-во элементов, кратное четырем: ";
    std::cin >> N;
    std::deque<int> deque(N);
    fill_handler(deque);
    STL2Seq28(deque);
    break;
  }
  case 4:{
    STL1Iter10();
    break;
  }
  default:{
    std::cout << "Ошибка ввода\n";
    break;
  }
  }
}