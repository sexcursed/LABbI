#include "point.h"
#include <stdexcept>

// Конструктор по умолчанию
Point::Point() : x(0.0), y(0.0) {}

// Конструктор с параметрами
Point::Point(double x, double y) : x(x), y(y) {}

// Конструктор копирования
Point::Point(const Point& other) : x(other.x), y(other.y) {}

// Сеттеры с проверкой
void Point::setX(double x) {
    this->x = x;
}

void Point::setY(double y) {
    this->y = y;
}

// Расстояние до другой точки
double Point::distanceTo(const Point& other) const {
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}

// Расстояние до начала координат
double Point::distanceToOrigin() const {
    return std::sqrt(x * x + y * y);
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

// Унарный ++: увеличить x на 1
Point& Point::operator++() {
    x += 1.0;
    return *this;
}

// Унарный --: уменьшить x на 1
Point& Point::operator--() {
    x -= 1.0;
    return *this;
}

// Явное приведение к int: целая часть x
Point::operator int() const {
    return static_cast<int>(x);
}

// Неявное приведение к double: координата y
Point::operator double() const {
    return y;
}

// Бинарный +: расстояние до точки p
double Point::operator+(const Point& p) const {
    return distanceTo(p);
}

// Бинарный + с целым числом: увеличить x
Point Point::operator+(int value) const {
    return Point(x + value, y);
}