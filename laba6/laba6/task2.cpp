#include "task2.h"

Shape inShape(){
  Shape newShape;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  int typeChoice;
  std::cout << "¬ведите тип фигуры\n1 - круг\n2 - квадрат\n3 - отрезок\n";
  std::cin >> typeChoice;
  
  std::cout << "¬ведите цвет фигуры: ";
  std::cin >> newShape.color;

  switch(typeChoice){
    case 1:{
      newShape.type = CIRCLE;
      std::cout << "¬ведите радиус круга\n";
      std::cin >> newShape.parametr.radius;
      break;
    }
    case 2:{
      newShape.type = SQUARE;
      std::cout << "¬ведите длину стороны квадрата\n";
      std::cin >> newShape.parametr.side;
      break;
    }
    case 3:{
      newShape.type = SEGMENT;
      std::cout << "¬ведите длину отрезка\n";
      std::cin >> newShape.parametr.length;
      break;
    }
    default:{
      std::cout << "Shape type ERROR";
      break;
    }
  }

  return newShape;
}

std::vector <Shape> inShapesList(int N){
  std::vector <Shape> shapesList;

  for(int i = 0; i < N; ++i){
    shapesList.push_back(inShape());
  }

  return shapesList;
}

std::string getShapeType(Shape shape){
  switch(shape.type){
    case CIRCLE: return " руг";
    case SQUARE: return " вадрат";
    case SEGMENT: return "ќтрезок";
    default: return "Not Found";
  }
}

std::string getShapeParameter(Shape shape){
  switch (shape.type){
    case CIRCLE: return std::to_string(shape.parametr.radius);
    case SQUARE: return std::to_string(shape.parametr.side);
    case SEGMENT: return std::to_string(shape.parametr.length);
    default: return "Not Found";
  }
}

void fileFill(std::vector <Shape>& shapesList){
  std::ofstream file("out.txt");
  if(!file.is_open()) return;

  file << std::left << std::setw(15) << "“ип" << std::setw(15) << "÷вет" << std::setw(15) << "ѕараметр" << std::endl;
  for(Shape shape : shapesList){
    file << std::left << std::setw(15) << getShapeType(shape) << std::setw(15) << shape.color << std::setw(15) << getShapeParameter(shape) << std::endl;
  }
  file.close();
}

void filePrint(){
  std::ifstream file("out.txt");
  if(!file.is_open()) return;

  std::string line;
  while(std::getline(file, line)){
    std::cout << line << "\n";
  }
}

void answer2(int N){
  std::vector <Shape> shapes = inShapesList(N);
  fileFill(shapes);
  filePrint();
}