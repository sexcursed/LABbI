#include "task1.h"

int inputSize(){
  std::cout << "Введите размер массива\n";
  int N;
  std::cin >> N;
  return N;
}

std::vector <int> generateNums(){
  srand(time(0));
  int N = inputSize();
  std::vector <int> nums;
  for(int i = 0; i < N; ++i){
    int num = 1 + rand() % 1000;
    nums.push_back(num);
  }
  return nums;
}

void bubbleSort(std::vector <int>& nums){
  int temp;
  for(int i = 0; i < nums.size(); ++i){
    for(int j = nums.size() - 1; j > i; --j){
      if(nums[j] > nums[j-1]){
        temp = nums[j-1];
        nums[j-1] = nums[j];
        nums[j] = temp;
      }
    }
    std::cout << i + 1 << " - ";
    for(int j = 0; j < nums.size(); ++j){
      std::cout << nums[j] << " ";
    }
    std::cout << "\n";
  }
}

void answer1(){
  std::vector <int> m = generateNums();
  bubbleSort(m);
}