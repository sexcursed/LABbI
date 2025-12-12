#include "tasks.h"

void String43(std::vector <std::string> words){

    int count = 0;

    for(std::string x: words){
        if(x.find("А") != std::string::npos or x.find("а") != std::string::npos){
            count++;
            std::cout << x << " ";
        }
        
    }

    std::cout << "\n" << count;

}

void Str15(std::vector <std::string> words){
    
    for(std::string word : words){
        for(char ch : word){
            if(ch != ' '){
                unsigned char uc = static_cast<unsigned char>(ch);
                std::cout << static_cast<int>(uc);
                std::cout << "_";
            }
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

void Str24(std::vector <std::string> words){
    
    int gammaByte,charByte;
    //srand(time(0));
    std::cout << "Введите желаемую гамму (127-255): ";
    std::cin >> gammaByte;
    while(gammaByte < 127 or gammaByte > 255){
        std::cout << "Введите корректное значение от 127 до 255: ";
        std::cin >> gammaByte;
    }
    
    for(std::string word : words){
        std::cout << word << " ";
    }
    std::cout << "= ";
    for(std::string word : words){
        for(char c : word){
            charByte = (int)c ^ gammaByte;
            std::cout << (char)charByte;
        }
        std::cout << " ";
    }
    std::cout << "XOR код";
}

void Str39(std::vector <std::string> words){
    std::map <char, int> chars;
    for(std::string word : words){
        for(char c : word){
            chars[c] += 1;
        }
    }

    for(auto [c,count] : chars){
        if(count == 1){
            std::cout << c << " ";
        }
    }
}


//str28
int hexCharToDec(char c){
    c = toupper(c);
    if(c >= '0' and c <= '9'){
        return c - '0';
    }
    else if(c >= 'A' and c <= 'F'){
        return 10 + (c - 'A');
    }
    std::cout << "некорректный символ";
    return 0;
}

std::string decToOct(long long num){
    
    std::string oct = "";
    while(num > 0){
        oct = std::to_string(num % 8) + oct;
        num /= 8;
    }

    return oct;
}

void Str28(std::vector <std::string> words){
    bool flag;
    std::string oct;
    for(std::string word : words){
        int power = word.size() - 1;
        long long n = 0;
        flag = true;
        for(char c : word){
            if(hexCharToDec(c) == 0) flag = false;
            n += hexCharToDec(c) * pow(16, power);
            power--;
        }
        if(flag){
            oct = decToOct(n);
            std::cout << oct << " ";
        }
    }
}

void task6(std::vector <std::string> words){
    std::vector <std::string> result;
    std::string trans;
    std::map <char,std::string> alph{
        {'A', ".-"}, {'А', ".-"}, {'B', "-..."}, {'Б',"-..."}, {'W', ".--"}, {'В', ".--"}, {'G', "--."}, {'Г', "--."}, {'D', "-.."}, {'Д', "-.."}, {'E', "."}, {'Е', "."}, {'V', "...-"}, {'Ж', "...-"}, {'Z', "--.."}, {'З', "--.."}, {'I', ".."}, {'И', ".."}, {'J', ".---"}, {'Й', ".---"}, {'K', "-.-"}, {'К', "-.-"}, {'L', ".-.."}, {'Л', ".-.."}, {'M', "--"}, {'М', "--"}, {'N', "-."}, {'Н', "-."}, {'O', "---"}, {'О', "---"}, {'P', ".--."}, {'П', ".--."}, {'R', ".-."}, {'Р', ".-."}, {'S', "..."}, {'С', "..."}, {'T', "-"}, {'Т', "-"}, {'U', "..-"}, {'У', "..-"}, {'F', "..-."}, {'Ф', "..-."}, {'H', "...."}, {'Х', "...."}, {'C', "-.-."}, {'Ц', "-.-."}, {'Ч', "---."}, {'Ш', "----"}, {'Щ', "--.-"}, {'Ъ', "--.--"}, {'Y', "-.--"}, {'Ы', "-.--"}, {'X', "-..-"}, {'Ь', "-..-"}, {'Э', "..-.."}, {'Ю', "..--"}, {'Я', ".-.-"}, {'b', "-..."}, {'б', "-..."},
        {'a', ".-"}, {'а', ".-"},
        {'b', "-..."}, {'б', "-..."},
        {'w', ".--"}, {'в', ".--"},
        {'g', "--."}, {'г', "--."},
        {'d', "-.."}, {'д', "-.."},
        {'e', "."}, {'е', "."},
        {'v', "...-"}, {'ж', "...-"},
        {'z', "--.."}, {'з', "--.."},
        {'i', ".."}, {'и', ".."},
        {'j', ".---"}, {'й', ".---"},
        {'k', "-.-"}, {'к', "-.-"},
        {'l', ".-.."}, {'л', ".-.."},
        {'m', "--"}, {'м', "--"},
        {'n', "-."}, {'н', "-."},
        {'o', "---"}, {'о', "---"},
        {'p', ".--."}, {'п', ".--."},
        {'r', ".-."}, {'р', ".-."},
        {'s', "..."}, {'с', "..."},
        {'t', "-"}, {'т', "-"},
        {'u', "..-"}, {'у', "..-"},
        {'f', "..-."}, {'ф', "..-."},
        {'h', "...."}, {'х', "...."},
        {'c', "-.-."}, {'ц', "-.-."},
        {'ч', "---."},
        {'ш', "----"},
        {'ъ', "--.--"},
        {'y', "-.--"}, {'ы', "-.--"},
        {'x', "-..-"}, {'ь', "-..-"},
        {'э', "..-.."},
        {'ю', "..--"},
        {'я', ".-.-"}
    };

    for(std::string word : words){
        trans = "";
        for(char ch : word){
            trans += alph[ch];
        }
        result.push_back(trans);
    }

    for(std::string word : result){
        std::cout << word << "   ";
    }
}

void Five3(){
    std::ifstream input("FN1.txt");
    if(!input.is_open()){
        std::cout << "Ошибка открытия файла";
        return;
    } 
    std::vector <std::string> expressions;
    std::string line;
    while(std::getline(input, line)){
        expressions.push_back(line);
    }
    input.close();

    std::ofstream out("FN2.txt");
    for(std::string expression : expressions){
        int a, b;
        char operand;
        std::string eq;

        std::istringstream iss(expression);
        if(iss >> a >> operand >> b >> eq){
            int result;
            if(operand == '+') result = a + b;
            if(operand == '-') result = a - b;
            out << expression << " " << result << "\n";
        }
    }
    out.close();
}