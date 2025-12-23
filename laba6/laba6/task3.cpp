#include "task3.h"

Point inputPoint(){
  float X, Y;
  std::cout << "Введите х и у координаты соотвественно\n";
  std::cin >> X >> Y;
  Point point;
  point.x = X;
  point.y = Y;
  return point;
}

std::vector <Point> inputPolygon(){
  int N;
  std::cout << "Введите количество точек, не меньшее трех\n";
  std::cin >> N;
  std::vector <Point> polygon;
  for(int i = 0; i < N; ++i){
    polygon.push_back(inputPoint());
  }
  return polygon;
}

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
  std::cout << "Точка передвинута\n";
}

void printDist(Point point1, Point point2){
  std::cout << dist(point1, point2);
}

double polygonArea(std::vector <Point>& polygon){
  int N = polygon.size();
  float area = 0.0;
  Point point1, point2;

  for(int i  = 0; i < N; ++i){
    point1 = polygon[i];
    point2 = polygon[(i+1)%N];

    area += point1.x * point2.y - point1.y * point2.x;
  }

  return std::abs(area) / 2.0;
}

void answer3(std::vector <Point>& polygon){
  int c;
  std::cout << "-----\n";
  std::cout << "Выберете действие\n1 - ввести набор точек\n2 - перемещение выбраной точки\n3 - вычисление площади многоугольника, заданного набором точек\n4 - выход\n";
  std::cin >> c;
  switch (c)
  {
    case 1:{
      polygon = inputPolygon();
      break;
    }
    case 2:{
      if(polygon.size() != 0){
        std::cout << "Выберете индекс точки, которую хотите передвинуть\n";
        int i = 0, pointIndex;
        for(auto x : polygon){
          std::cout << "i=" << i << " x:" << x.x << " y:" << x.y << "\n";
          i++; 
        }
        std::cin >> pointIndex;
        movePoint(polygon[pointIndex]);
        break;
      }
      std::cout << "Набор точек еще не задан\n";
      break;
    }
    case 3:{
      if(polygon.size() >= 3){
        float area = polygonArea(polygon);
        std::cout << "Площадь многоугольника = " << area << "\n";
        break;
      }
      std::cout << "Набор точек еще не задан или меньше трех\n";
      break;
    }
    case 4:{
      return;
    }
  }
  std::cout << "-----\n";
  answer3(polygon);
}