#include "header.h"

int main(){
    int choice;
    std::cout << "Выберете задачу: ";
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        file8();
        break;
    case 2:
        file31();
        break;
    case 4:
        std::string s;
        std::cout << "\nВведите выражение: ";
        std::cin >> s;
        std::cout << calc(s);
        break;
    }
    return 0;
}