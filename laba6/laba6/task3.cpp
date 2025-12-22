#include "task3.h"

void printPoint(Point point){
  std::cout << "x: " << point.x << " y: " << point.y << std::endl;
}

float dist(Point point1, Point point2){
  float X = point2.x - point1.x;
  float Y = point2.y - point1.y;

  return sqrt(X*X + Y*Y);
}

void movePoint(Point& point){
  float newX, newY;
  std::cout << "Введите новую x-координату и y-координату соответственно\n";
  std::cin >> newX >> newY;
  point.x = newX;
  point.y = newY;
  std::cout << "Точка передвинута";
}

void printDist(Point point1, Point point2){
  std::cout << dist(point1, point2);
}