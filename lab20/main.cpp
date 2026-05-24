#include "point.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <stdexcept>

// Глобальные переменные для хранения текущих точек
Point currentPoint1;
Point currentPoint2;
bool hasPoint1 = false;
bool hasPoint2 = false;

enum InputMethod { MANUAL = 1, RANDOM, FILE_INPUT };

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getValidDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << "Ошибка! Введите число.\n";
            clearInput();
        } else {
            clearInput();
            return value;
        }
    }
}

int getValidInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cout << "Ошибка! Введите целое число.\n";
            clearInput();
        } else {
            clearInput();
            return value;
        }
    }
}

// Ввод одной точки
Point inputSinglePoint(InputMethod method, const std::string& pointName) {
    if (method == MANUAL) {
        std::cout << "\n--- Ввод " << pointName << " ---\n";
        double x = getValidDouble("Введите x: ");
        double y = getValidDouble("Введите y: ");
        return Point(x, y);
    }
    else if (method == RANDOM) {
        double x = (rand() % 2000 - 1000) / 100.0;
        double y = (rand() % 2000 - 1000) / 100.0;
        std::cout << "Сгенерирована " << pointName << ": (" << x << ", " << y << ")\n";
        return Point(x, y);
    }
    else {
        return Point(); // заглушка
    }
}

// Ввод двух точек
void inputTwoPoints(InputMethod method) {
    std::cout << "\n========== ВВОД ТОЧЕК ==========\n";
    
    if (method == MANUAL) {
        currentPoint1 = inputSinglePoint(MANUAL, "точку A");
        currentPoint2 = inputSinglePoint(MANUAL, "точку B");
        hasPoint1 = true;
        hasPoint2 = true;
    }
    else if (method == RANDOM) {
        currentPoint1 = inputSinglePoint(RANDOM, "точку A");
        currentPoint2 = inputSinglePoint(RANDOM, "точку B");
        hasPoint1 = true;
        hasPoint2 = true;
    }
    else if (method == FILE_INPUT) {
        std::string filename;
        std::cout << "Введите имя файла: ";
        std::cin >> filename;
        try {
            std::ifstream file(filename.c_str());
            if (!file.is_open()) {
                throw std::runtime_error("Не удалось открыть файл");
            }
            
            std::vector<Point> points;
            double x, y;
            while (file >> x >> y) {
                points.push_back(Point(x, y));
            }
            file.close();
            
            if (points.size() >= 2) {
                currentPoint1 = points[0];
                currentPoint2 = points[1];
                hasPoint1 = true;
                hasPoint2 = true;
                std::cout << "Загружены точки из файла:\n";
                std::cout << "Точка A: " << currentPoint1 << std::endl;
                std::cout << "Точка B: " << currentPoint2 << std::endl;
            } else if (points.size() == 1) {
                currentPoint1 = points[0];
                hasPoint1 = true;
                std::cout << "Загружена только одна точка: " << currentPoint1 << std::endl;
                std::cout << "Введите вторую точку вручную:\n";
                currentPoint2 = inputSinglePoint(MANUAL, "точку B");
                hasPoint2 = true;
            } else {
                throw std::runtime_error("Файл пуст");
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << ". Будет использован ручной ввод.\n";
            currentPoint1 = inputSinglePoint(MANUAL, "точку A");
            currentPoint2 = inputSinglePoint(MANUAL, "точку B");
            hasPoint1 = true;
            hasPoint2 = true;
        }
    }
    
    std::cout << "\nТекущие точки:\n";
    std::cout << "  Точка A: " << currentPoint1 << std::endl;
    std::cout << "  Точка B: " << currentPoint2 << std::endl;
}

// Ввод одной точки (для операций, где нужна только одна точка)
void inputSinglePointForDemo(InputMethod method) {
    std::cout << "\n========== ВВОД ТОЧКИ ==========\n";
    currentPoint1 = inputSinglePoint(method, "точку");
    hasPoint1 = true;
    std::cout << "\nТекущая точка: " << currentPoint1 << std::endl;
}

// Демонстрация конструкторов
void demoConstructors() {
    std::cout << "\n========== Демонстрация конструкторов ==========\n";
    
    Point p1;
    std::cout << "1. Конструктор по умолчанию: p1 = " << p1 << std::endl;
    
    Point p2(5.7, 3.2);
    std::cout << "2. Конструктор с параметрами (5.7, 3.2): p2 = " << p2 << std::endl;
    
    Point p3(p2);
    std::cout << "3. Конструктор копирования (копия p2): p3 = " << p3 << std::endl;
    
    Point p4 = Point(2.5, 6.8);
    std::cout << "4. Конструктор с параметрами (2.5, 6.8): p4 = " << p4 << std::endl;
}

// Демонстрация методов distance
void demoDistanceMethods() {
    std::cout << "\n========== Расстояния ==========\n";
    
    if (!hasPoint1 || !hasPoint2) {
        std::cout << "ОШИБКА: Точки не введены! Сначала введите точки (пункт 1 или 2 меню)\n";
        return;
    }
    
    std::cout << "Точка A: " << currentPoint1 << std::endl;
    std::cout << "Точка B: " << currentPoint2 << std::endl;
    std::cout << "\nРезультаты:\n";
    std::cout << "  Расстояние от A до B: " << currentPoint1.distanceTo(currentPoint2) << std::endl;
    std::cout << "  Расстояние от A до начала координат (0,0): " << currentPoint1.distanceToOrigin() << std::endl;
    std::cout << "  Расстояние от B до начала координат (0,0): " << currentPoint2.distanceToOrigin() << std::endl;
}

// Демонстрация унарных операций
void demoUnaryOperations() {
    std::cout << "\n========== Унарные операции (++ и --) ==========\n";
    
    if (!hasPoint1) {
        std::cout << "ОШИБКА: Точка не введена! Сначала введите точку (пункт 1, 2 или 3 меню)\n";
        return;
    }
    
    std::cout << "Исходная точка A: " << currentPoint1 << std::endl;
    
    Point temp = currentPoint1;
    ++temp;
    std::cout << "После операции ++ (x + 1): " << temp << std::endl;
    
    temp = currentPoint1;
    --temp;
    std::cout << "После операции -- (x - 1): " << temp << std::endl;
    
    std::cout << "\nПрименение к точке B (если она введена):\n";
    if (hasPoint2) {
        std::cout << "Исходная точка B: " << currentPoint2 << std::endl;
        Point temp2 = currentPoint2;
        ++temp2;
        std::cout << "Точка B после ++: " << temp2 << std::endl;
        --temp2;
        --temp2;
        std::cout << "Точка B после двух --: " << temp2 << std::endl;
    } else {
        std::cout << "Точка B не введена.\n";
    }
}

// Демонстрация операций приведения типа
void demoTypeCastOperations() {
    std::cout << "\n========== Операции приведения типа ==========\n";
    
    if (!hasPoint1) {
        std::cout << "ОШИБКА: Точка не введена! Сначала введите точку (пункт 1, 2 или 3 меню)\n";
        return;
    }
    
    std::cout << "Исходная точка A: " << currentPoint1 << std::endl;
    
    // Явное приведение к int
    int intX = static_cast<int>(currentPoint1);
    std::cout << "\n1. Явное приведение к int (целая часть x): " << intX << std::endl;
    
    // Неявное приведение к double
    double doubleY = currentPoint1;
    std::cout << "2. Неявное приведение к double (координата y): " << doubleY << std::endl;
    
    std::cout << "\nДля точки B:\n";
    if (hasPoint2) {
        std::cout << "Точка B: " << currentPoint2 << std::endl;
        std::cout << "   Явное приведение к int (целая часть x): " << static_cast<int>(currentPoint2) << std::endl;
        std::cout << "   Неявное приведение к double (координата y): " << (double)currentPoint2 << std::endl;
    } else {
        std::cout << "Точка B не введена.\n";
    }
}

// Демонстрация бинарных операций
void demoBinaryOperations() {
    std::cout << "\n========== Бинарные операции (+) ==========\n";
    
    if (!hasPoint1) {
        std::cout << "ОШИБКА: Точка A не введена! Сначала введите точки (пункт 1 или 2 меню)\n";
        return;
    }
    
    // Оператор + для расстояния между точками
    if (hasPoint2) {
        std::cout << "1. Оператор + (расстояние между точками):\n";
        std::cout << "   " << currentPoint1 << " + " << currentPoint2 << " = ";
        double distance = currentPoint1 + currentPoint2;
        std::cout << distance << std::endl;
    } else {
        std::cout << "1. Оператор + (расстояние): точка B не введена, пропускаем.\n";
    }
    
    // Оператор + с целым числом
    std::cout << "\n2. Оператор + с целым числом (увеличение x):\n";
    int value = getValidInt("   Введите целое число для увеличения x: ");
    
    Point newPoint = currentPoint1 + value;
    std::cout << "   " << currentPoint1 << " + " << value << " = " << newPoint << std::endl;
    
    if (hasPoint2) {
        Point newPoint2 = currentPoint2 + value;
        std::cout << "   " << currentPoint2 << " + " << value << " = " << newPoint2 << std::endl;
    }
}

// Изменение текущих точек
void changePoints(InputMethod method) {
    std::cout << "\n========== ИЗМЕНЕНИЕ ТЕКУЩИХ ТОЧЕК ==========\n";
    std::cout << "Что вы хотите сделать?\n";
    std::cout << "  1 - Изменить только точку A\n";
    std::cout << "  2 - Изменить только точку B\n";
    std::cout << "  3 - Изменить обе точки\n";
    std::cout << "  4 - Вернуться в меню\n";
    std::cout << "Выбор: ";
    
    int choice;
    std::cin >> choice;
    clearInput();
    
    switch (choice) {
        case 1:
            currentPoint1 = inputSinglePoint(method, "новую точку A");
            hasPoint1 = true;
            std::cout << "Новая точка A: " << currentPoint1 << std::endl;
            break;
        case 2:
            currentPoint2 = inputSinglePoint(method, "новую точку B");
            hasPoint2 = true;
            std::cout << "Новая точка B: " << currentPoint2 << std::endl;
            break;
        case 3:
            inputTwoPoints(method);
            break;
        default:
            std::cout << "Возврат в меню.\n";
    }
}

// Показать текущие точки
void showCurrentPoints() {
    std::cout << "\n========== ТЕКУЩИЕ ТОЧКИ ==========\n";
    if (hasPoint1) {
        std::cout << "Точка A: " << currentPoint1 << std::endl;
    } else {
        std::cout << "Точка A: не введена\n";
    }
    if (hasPoint2) {
        std::cout << "Точка B: " << currentPoint2 << std::endl;
    } else {
        std::cout << "Точка B: не введена\n";
    }
}

void showMenu() {
    std::cout << "\n========================================\n";
    std::cout << "        ТЕСТИРОВАНИЕ КЛАССА POINT        \n";
    std::cout << "========================================\n";
    std::cout << "ТЕКУЩИЕ ТОЧКИ:\n";
    if (hasPoint1) {
        std::cout << "  A = " << currentPoint1 << std::endl;
    } else {
        std::cout << "  A = не введена\n";
    }
    if (hasPoint2) {
        std::cout << "  B = " << currentPoint2 << std::endl;
    } else {
        std::cout << "  B = не введена\n";
    }
    std::cout << "----------------------------------------\n";
    std::cout << "ВЫБОР СПОСОБА ЗАПОЛНЕНИЯ:\n";
    std::cout << "  1 - Ручной ввод (для следующих операций)\n";
    std::cout << "  2 - Случайные числа (для следующих операций)\n";
    std::cout << "  3 - Из файла (для следующих операций)\n";
    std::cout << "----------------------------------------\n";
    std::cout << "ОПЕРАЦИИ С ТОЧКАМИ:\n";
    std::cout << "  4 - Ввести/обновить точки A и B\n";
    std::cout << "  5 - Показать текущие точки\n";
    std::cout << "  6 - Конструкторы (демонстрация)\n";
    std::cout << "  7 - Методы distanceTo и distanceToOrigin\n";
    std::cout << "  8 - Унарные операции (++, --)\n";
    std::cout << "  9 - Операции приведения типа (int, double)\n";
    std::cout << " 10 - Бинарные операции (+)\n";
    std::cout << " 11 - Изменить отдельные точки\n";
    std::cout << "  0 - Выход\n";
    std::cout << "========================================\n";
    std::cout << "Ваш выбор: ";
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));
    
    int choice;
    InputMethod currentMethod = MANUAL;
    
    try {
        do {
            showMenu();
            std::cin >> choice;
            
            if (std::cin.fail()) {
                std::cout << "Ошибка ввода!\n";
                clearInput();
                continue;
            }
            
            if (choice >= 1 && choice <= 3) {
                currentMethod = static_cast<InputMethod>(choice);
                std::cout << "\nВыбран способ заполнения: ";
                switch (currentMethod) {
                    case MANUAL: std::cout << "Ручной ввод\n"; break;
                    case RANDOM: std::cout << "Случайные числа\n"; break;
                    case FILE_INPUT: std::cout << "Из файла\n"; break;
                }
                continue;
            }
            
            switch (choice) {
                case 4:
                    inputTwoPoints(currentMethod);
                    break;
                case 5:
                    showCurrentPoints();
                    break;
                case 6:
                    demoConstructors();
                    break;
                case 7:
                    demoDistanceMethods();
                    break;
                case 8:
                    demoUnaryOperations();
                    break;
                case 9:
                    demoTypeCastOperations();
                    break;
                case 10:
                    demoBinaryOperations();
                    break;
                case 11:
                    changePoints(currentMethod);
                    break;
                case 0:
                    std::cout << "Программа завершена.\n";
                    break;
                default:
                    std::cout << "Неверный выбор! Попробуйте снова.\n";
            }
        } while (choice != 0);
    }
    catch (const std::exception& e) {
        std::cout << "\nИсключение: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}