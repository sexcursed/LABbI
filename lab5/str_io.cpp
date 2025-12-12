#include "str_io.h"

std::vector <std::string> manualInput(){

    std::string text;
    std::cout << "Введите строку: ";
    std::getline(std::cin, text);

    std::string sep = " ", word;
    std::vector <std::string> words;
    size_t start = text.find_first_not_of(sep), end;

    while(start != std::string::npos){
        end = text.find_first_of(sep, start + 1);
        if (end == std::string::npos) end = text.length();
        word = text.substr(start, end - start);
        words.push_back(word);
        start = text.find_first_not_of(sep, end + 1);
    }

    return words;
}

std::vector <std::string> randomInput(){
    
    int choice;
    int amount;
    srand(time(0));
    std::cout << "Выберете алфавит( 1 - русские, 2 - английские, 3 - смешанный, 4 - 16-тиричный алфавит): ";
    std::cin >> choice;
    std::cout << "Введите кол-во слов: ";
    std::cin >> amount;


    std::vector <std::string> words;
    std::string word, charSet;

    switch (choice){
        case 1:{
            charSet = "АБВГДЕЁЖЗИКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзиклмнопрстуфхцчшщъыьэюя";
            break;
        }
        case 2:{
            charSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            break;
        }
        case 3:{
            charSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzАБВГДЕЁЖЗИКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзиклмнопрстуфхцчшщъыьэюя";
            break;
        }
        case 4:{
            charSet = "0123456789ABCDEF";
            break;
        }
        default:{
            break;
        }
    }

    for(int i = 0; i < amount; ++i){

        int wordLength = rand() % 10 + 1;
        word.clear();
        
        for(int j = 0; j < wordLength; ++j){

            size_t index = rand() % (charSet.length() / 2);
            size_t byteIndex = index * 2;

            if(byteIndex + 1 < charSet.length()){
                word += charSet[byteIndex];
                word += charSet[byteIndex + 1];
            }
        }
        
        words.push_back(word);

    }
    
    return words;
}

std::vector <std::string> fileInput(){

    std::string text;
    std::ifstream file("input.txt");
    if(file.is_open()){
        std::getline(file,text);
    }
    else{
        std::cout << "ошибка открытия файла";
    }

    std::string sep = " ", word;
    std::vector <std::string> words;
    size_t start = text.find_first_not_of(sep), end;

    while(start != std::string::npos){
        end = text.find_first_of(sep, start + 1);
        if (end == std::string::npos) end = text.length();
        word = text.substr(start, end - start);
        words.push_back(word);
        start = text.find_first_not_of(sep, end + 1);
    }

    return words;
}