#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <cmath>
#include <string>

class Point {
private:
    double x;
    double y;

public:
    // Конструкторы (не менее трех)
    Point();                                    // по умолчанию (0,0)
    Point(double x, double y);                  // с параметрами
    Point(const Point& other);                  // копирования
    
    // Геттеры и сеттеры
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double x);
    void setY(double y);
    
    // Метод согласно варианту: расстояние от точки до другой точки
    double distanceTo(const Point& other) const;
    
    // Метод: расстояние от точки до начала координат
    double distanceToOrigin() const;
    
    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    
    // Унарные операции (вариант 3)
    Point& operator++();    // увеличить x на 1
    Point& operator--();    // уменьшить x на 1
    
    // Операции приведения типа
    explicit operator int() const;   // целая часть x
    operator double() const;         // координата y
    
    // Бинарные операции (вариант 3)
    double operator+(const Point& p) const;  // расстояние до точки p
    Point operator+(int value) const;        // увеличить x на целое число
};

#endif