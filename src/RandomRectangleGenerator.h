//
// Created by splatt on 04-10-17.
//

#ifndef LOGARITMOS_TAREA1_RANDOMRECTANGLEGENERATOR_H
#define LOGARITMOS_TAREA1_RANDOMRECTANGLEGENERATOR_H


#include "Rectangle.h"

class RandomRectangleGenerator {
private:
  int currentIndex = 0;

public:
  void generateDataFile(int n);
  int* generateRandomRect();
};


#endif //LOGARITMOS_TAREA1_RANDOMRECTANGLEGENERATOR_H
