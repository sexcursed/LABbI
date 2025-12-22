#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <limits>

enum shapeType {CIRCLE, SQUARE, SEGMENT};

struct Shape{
  std::string color;
  shapeType type;

  union{
    short int radius;
    int side;
    float length;
  } parametr;

};

void answer2(int N);