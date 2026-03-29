#include "tasks.h"
#include "io.h"

void STL5Assoc2(std::vector<int> v0){
  std::set<int> v0_set(v0.begin(), v0.end());
  std::vector<std::vector<int>> vN;
  int count = 0;
  int N;
  std::cout << "Введите желаемое кол-во векторов:";
  std::cin >> N;
  for(int i = 0; i < N; ++i){
    std::cout << "Введите размер генерируемого вектора: ";
    int size;
    std::cin >> size;
    std::vector<int> vi(size);
    fill_handler(vi);
    vN.push_back(vi);
  }
  std::cout << "Исходный вектор: ";
  print_container(v0.begin(), v0.end());
  for(std::vector<int>& x: vN){
    std::cout << "Текущий вектор: ";
    print_container(x.begin(), x.end());
    std::set<int> vi_set(x.begin(), x.end());
    if(std::includes(vi_set.begin(), vi_set.end(), v0_set.begin(), v0_set.end())){
      count++;
    }
    std::cout << "count = " << count << "\n";
  }
}

void STL5Assoc17(std::vector<std::string> words){
  std::map<char, int> M;
  for(std::vector<std::string>::iterator it = words.begin(); it != words.end(); ++it){
    M[(*it)[0]] += (*it).size();
  }
  for(std::map<char, int>::iterator it = M.begin(); it != M.end(); ++it){
    std::cout << it->first << " -> " << it->second << "\n";
  }
}

void STL5Assoc21(std::vector<int> numbers){
  std::multimap<int,int> M;
  for(std::vector<int>::iterator it = numbers.begin(); it != numbers.end(); ++it){
    M.insert(std::make_pair(std::abs(*it % 10), *it));
  }
  for(std::multimap<int, int>::iterator it = M.begin(); it != M.end(); ++it){
    std::cout << it->first << " -> " << it->second << "\n";
  }
}

void tasks_handler(){
  std::cout << "Выберете задачу ( 1 - 3 ):";
  int choice;
  std::cin >> choice;
  std::cin.clear();
  switch (choice)
  {
    case 1:{
      int N;
      std::cout << "Введите кол-во элементов:";
      std::cin >> N;
      std::vector<int> vector0(N);
      fill_handler(vector0);
      STL5Assoc2(vector0);
      break;
    }
    case 2:{
      int N;
      std::cout << "Введите кол-во элементов:";
      std::cin >> N;
      std::vector<std::string> W(N);
      fill_manual_strings(W.begin(), W.end());
      STL5Assoc17(W);
      break;
    }
    case 3:{
      int N;
      std::cout << "Введите кол-во элементов:";
      std::cin >> N;
      std::vector<int> V(N);
      fill_handler(V);
      STL5Assoc21(V);
      break;
    }
    default:{
      break;
    }
  }
}