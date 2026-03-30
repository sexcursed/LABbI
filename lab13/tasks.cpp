#include "tasks.h"
#include "io.h"


void STL3Alg4(std::list<int>& l){
  if(l.empty()){  
    std::cout << "Список пуст.\n";
    return;
  }

  std::list<int>::iterator first_negative = std::find_if(l.begin(), l.end(), [](int x) {return x < 0;});

  if(first_negative != l.end()){
    std::list<int>::iterator first_to_delete = std::next(first_negative);
    std::list<int>::iterator last_to_delete = std::find_if(first_to_delete, l.end(), [](int x){return x < 0;});
    l.erase(first_to_delete, last_to_delete);
  }

  print_container(l.begin(), l.end());
}

void STL3Alg18(std::deque<int>& d){
  if(d.empty()){
    std::cout << "Дек пуст.\n";
    return;
  }
  int N;
  std::cout << "Введите N, такое что 2N <= " << d.size() << ": ";
  std::cin >> N;
  if(d.size() < 2 * N){
    std::cout << "Кол-во элементов дека должно быть не менне 2N.\n";
    return;
  }
  struct Gen{
    int num = 0;
    int operator()(){
      return ++num;
    }
  };
  Gen gen;
  std::generate(d.begin(), std::next(d.begin(), N), gen);
  gen.num = 0;
  std::generate(d.rbegin(), std::next(d.rbegin(), N), gen);
  print_container(d.begin(), d.end());
}

void STL3Alg48(std::vector<int>& v){
  if(v.empty()){
    std::cout << "Вектор пуст.\n";
    return;
  }
  if(v.size()%3 != 0){
    std::cout << "Необходимо кол-во элементов, которое делится на 3.\n";
    return;
  }
  struct Comparator{
    int get_group(int x){
      if(x < 0) return 1;
      if(x == 0) return 2;
      return 3;
    }
    bool operator()(int a, int b){
      return get_group(a) < get_group(b);
    }
  };
  Comparator comp;
  int n = v.size() / 3;
  print_container(v.begin(), v.end());
  std::sort(v.begin(), v.begin() + n);
  std::sort(v.begin() + n, v.begin() + 2* n);
  std::sort(v.begin() + 2*n, v.end());
  print_container(v.begin(), v.end());
  std::inplace_merge(v.begin(),v.begin() + n, v.begin() + 2*n,comp);
  std::inplace_merge(v.begin(), v.begin() + 2*n, v.end(), comp);
  print_container(v.begin(), v.end());
}

void STL3Alg60(std::list<int> l){
  if(l.empty()){
    std::cout << "Список пуст.\n";
    return;
  }
  std::vector<double> v;
  std::adjacent_difference(l.begin(), l.end(), std::back_inserter(v), [](double x, double y){return (x + y)/2.0;});
  v.erase(v.begin());
  print_container(v.begin(), v.end());
}

void tasks_handler(){
  std::cout << "Выберете задачу (1 - 4):";
  int choice;
  std::cin >> choice;
  std::cin.clear();
  switch (choice)
  {
    case 1:{
      int N;
      std::cout << "Введите кол-во элементов:";
      std::cin >> N;
      std::list<int> List(N);
      fill_handler(List);
      print_container(List.begin(), List.end());
      STL3Alg4(List);
      break;
    }
    case 2:{
      int N;
      std::cout << "Введите кол-во элементов:";
      std::cin >> N;
      std::deque<int> Deque(N);
      fill_handler(Deque);
      print_container(Deque.begin(), Deque.end());
      STL3Alg18(Deque);
      break;
    }
    case 3:{
      int N;
      std::cout << "Введите кол-во элементов, которое делится на 3:";
      std::cin >> N;
      std::vector<int> Vector(N);
      fill_handler(Vector);
      STL3Alg48(Vector);
      break;
    }
    case 4:{
      int N;
      std::cout << "Введите кол-во элементов:";
      std::cin >> N;
      std::list<int> List(N);
      fill_handler(List);
      print_container(List.begin(), List.end());
      STL3Alg60(List);
      break;
    }
    default:{
      break;
    }
  }
}