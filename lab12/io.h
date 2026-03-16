#include <iostream>
#include <random>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <deque>

template <typename It>
void fill_manual(It begin, It end){
  std::cout << "Введите " << std::distance(begin, end) << " чисел:\n";
  for(auto it = begin; it != end; ++it){
    std::cin >> *it;
  }
}

template <typename It>
void fill_random(It begin, It end){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  for(auto it = begin; it != end; ++it){
    *it = dis(gen);
  }
}

template <typename It>
void fill_from_file(It begin, It end, std::string filename){
  std::ifstream file(filename);
  if(file.is_open()){
    std::copy(std::istream_iterator<int>(file), std::istream_iterator<int>(), begin);
  }
}

template <typename It>
void print_container(It begin, It end){
  std::cout << "[ ";
  for(auto it = begin; it != end; ++it){
    std::cout << *it << " ";
  }
  std::cout << "]\n";
}

template <typename Container>
void fill_handler(Container& container){
  int choice;
  std::cout << "\nВыберете тип заполнения контейнера (1 - ручной ввод, 2 - рандом, 3 - из файла): ";
  std::cin >> choice;
  switch (choice)
  {
    case 1:{
      fill_manual(container.begin(), container.end());
      break;
    }
    case 2:{
      fill_random(container.begin(), container.end());
      break;
    }
    case 3:{
      std::cout << "\nВведите название файла: ";
      std::string name;
      std::cin >> name;
      fill_from_file(container.begin(), container.end(), name);
      break;
    }
    default:{
      std::cout << "Ошибка ввода\n";
      break;
    }
  }
}