#include "task3.h"

bool compare(Student a, Student b){
  if(a.score != b.score){
    return a.score < b.score;
  }
  return a.surname < b.surname;
}

void shellSort(std::vector<Student>& students, bool (*compare)(Student, Student)){
  int N = students.size();

  int gap = 1;
  while(gap < N/3){
    gap = gap*3 + 1;
  }

  while(gap > 0){
    for(int i = gap; i < N; ++i){
      Student temp = students[i];
      int j;
      for(j = i; j >= gap and compare(temp, students[j - gap]); j -= gap){
        students[j] = students[j-gap];
      }
      students[j] = temp;
    }
    gap /= 3;
  }
}

std::vector<Student> readFile(){
  std::ifstream file("input.txt");
  std::vector <Student> students;
  std::string surname;
  int score;
  while(file >> surname >> score){
    students.push_back({surname,score});
  }
  file.close();
  return students;
}

void writeFile(std::vector<Student> students){
  std::ofstream file("out.txt");
  for(Student student : students){
    file << std::left << std::setw(15) << student.surname;
    file << std::right << std::setw(3) << student.score << std::endl;
  }
  file.close();
  std::cout << "Данные записаны в out.txt\n";
}

void answer3(){
  std::vector <Student> students = readFile();
  shellSort(students, compare);
  writeFile(students);
}