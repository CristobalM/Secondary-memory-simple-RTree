//
// Created by splatt on 04-10-17.
//

#ifndef LOGARITMOS_TAREA1_RANDOMRECTANGLEGENERATOR_H
#define LOGARITMOS_TAREA1_RANDOMRECTANGLEGENERATOR_H


#include "Rectangle.h"
#include "commontypes.h"

class RandomRectangleGenerator {
public:
  static void generateDataFile(int n, std::string filename);
  static std::vector<float> generateRandomRect();
  static vRect generateVRect(int quantity);
};


#endif //LOGARITMOS_TAREA1_RANDOMRECTANGLEGENERATOR_H
