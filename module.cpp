#include "header.h"

int element(std::string s){
    if(s[0] == '(' and s[s.length() - 1] == ')') return calc(s.substr(1,s.length() - 2));
    return std::stoi(s);
}

int term(std::string s){
    int i = s.length() - 1;
    int level = 0;
    int pos = -1;
    while(i >= 0){
        if(s[i] == ')') level++;
        if(s[i] == '(') level--;
        if(level == 0 and s[i] == '*'){
            pos = i;
            break;
        }
        i--;
    }
    if(pos == -1) return element(s);
    return term(s.substr(0,pos)) * element(s.substr(pos + 1));
}

int calc(std::string s){
    int i = s.length() - 1;
    int level = 0;
    int pos = -1;
    while(i >= 0){
        if(s[i] == ')') level++;
        if(s[i] == '(') level--;
        if(level == 0 and (s[i] == '-' or s[i] == '+')){
            pos = i;
            break;
        }
        i--;
    }
    if(pos == -1) return term(s);
    char op = s[pos];
    if(op == '+') return calc(s.substr(0,pos)) + term(s.substr(pos + 1));
    if(op == '-') return calc(s.substr(0,pos)) - term(s.substr(pos + 1));
}

void writeFile(){
    std::vector <int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};
    std::ofstream iFile("input.dat", std::ios::binary|std::ios::trunc);
    for(int i = 0; i < numbers.size(); ++i){
        iFile.write((char *)&numbers[i],sizeof(numbers[i]));
    }
    iFile.close();
}

void writeFileManual(std::string name, int N){
    std::vector <double> numbers;
    std::ofstream iFile(name, std::ios::binary);
    double num;
    for(int i = 0; i<N; ++i){
        std::cout << "\nВведите вещественное число: ";
        std::cin >> num;
        numbers.push_back(num);
    }
    for(int i = 0; i < numbers.size(); ++i){
        iFile.write((char *)&numbers[i],sizeof(numbers[i]));
    }
    iFile.close();
}
void readFileDouble(std::string fileName){
    std::ifstream file(fileName, std::ios::binary);
    double number;
    while(file.read((char *)&number, sizeof(number))){
        std::cout << number << " ";
    }
    std::cout << std::endl;
    file.close();
}

void readFileInt(std::string fileName){
    std::ifstream file(fileName, std::ios::binary);
    int number;
    while(file.read((char *)&number, sizeof(number))){
        std::cout << number << " ";
    }
    std::cout << std::endl;
    file.close();
}

void file8(){
    std::ifstream iFile;
    std::ofstream oFile;
    std::string inName, outName;
    int N;

    std::cout << "\nВведите название исходного файла: ";
    std::cin >> inName;
    std::cout << "\nВведите название второго файла: ";
    std::cin >> outName;
    std::cout << "\nВведите количество чисел: ";
    std::cin >> N;

    writeFileManual(inName, N);
    iFile.open(inName,std::ios::binary);
    oFile.open(outName, std::ios::binary);
    std::vector <double> numbers;

    double number;
    while(iFile.read((char *)&number, sizeof(number))){
        numbers.push_back(number);
    }
    oFile.write((char *)&numbers[0], sizeof(numbers[0]));
    oFile.write((char *)&numbers[numbers.size() - 1], sizeof(numbers[-1]));

    iFile.close();
    oFile.close();

    readFileDouble(inName);
    readFileDouble(outName);
}

void file31(){
    writeFile();
    std::ifstream inFile("input.dat",std::ios::binary);
    std::vector <int> nums;
    int num;
    while(inFile.read((char *)&num, sizeof(num))){
        nums.push_back(num);
    }
    inFile.close();
    std::ofstream outFile("input.dat",std::ios::binary|std::ios::trunc);
    
    nums.erase(nums.begin(),nums.begin() + 50);
    for(int x : nums){
        outFile.write((char *)&x, sizeof(x));
    }

    outFile.close();
    readFileInt("input.dat");
}