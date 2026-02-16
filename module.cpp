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
    std::vector <double> numbers = {1.25, 1.27, 6.7, 754.54, 1345.13, 14.06, 0.46578, 623.0};
    std::ofstream iFile("input.dat", std::ios::binary);
    for(int i = 0; i < numbers.size(); ++i){
        iFile.write((char *)&numbers[i],sizeof(numbers[i]));
    }
    iFile.close();
}
void readFile(std::string fileName){
    std::ifstream file(fileName);
    double number;
    while(file.read((char *)&number, sizeof(number))){
        std::cout << number << " ";
    }
    std::cout << std::endl;
    file.close();
}

void file8(){
    std::ifstream iFile;
    std::ofstream oFile;
    writeFile();
    iFile.open("input.dat",std::ios::binary);
    oFile.open("output.dat", std::ios::binary);
    std::vector <double> numbers;

    double number;
    while(iFile.read((char *)&number, sizeof(number))){
        numbers.push_back(number);
    }
    oFile.write((char *)&numbers[0], sizeof(numbers[0]));
    oFile.write((char *)&numbers[numbers.size() - 1], sizeof(numbers[-1]));

    iFile.close();
    oFile.close();

    readFile("input.dat");
    readFile("output.dat");
}