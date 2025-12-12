#include "tasks.h"
#include "str_io.h"
//#include <windows.h>

int main(){

    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);

    
    int choice;
    std::vector <std::string> Input;
    std::cout << "Выберете тип ввода(1-3): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice)
    {
        case 1:{
            Input = manualInput();
            break;
        }
        case 2:{
            Input = randomInput();
            break;
        }
        case 3:{
            Input = fileInput();
            break;
        }
    }

    for(std::string x : Input){
        std::cout << x << " ";
    }

    std::cout << "\nВыберете задачу(1-7): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch(choice){
        case 1:{
            String43(Input);
            break;
        }
        case 2:{
            Str15(Input);
            break;
        }
        case 3:{
            Str24(Input);
            break;
        }
        case 4:{
            Str39(Input);
            break;
        }
        case 5:{
            Str28(Input);
            break;
        }
        case 6:{
            task6(Input);
            break;
        }
        case 7:{
            Five3();
            break;
        }
    }
    return 0;
}