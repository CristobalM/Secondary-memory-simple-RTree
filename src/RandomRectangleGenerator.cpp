//
// Created by splatt on 04-10-17.
//

#include <iostream>
#include <fstream>
#include <random>
#include <cstdio>
#include "RandomRectangleGenerator.h"


float getRandomFloat(int lower, int upper){
  return lower + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(upper-lower)));
}

int* RandomRectangleGenerator::generateRandomRect() {
  int coords[4];
  std::uniform_int_distribution<float> coordinatesDistribution(0,500000);
  std::uniform_int_distribution<float> heightWidthDistribution(1,100);
  float x1 = getRandomFloat(0,500000);
  float y1 = getRandomFloat(0,500000);
  float height = getRandomFloat(1,100);
  float width = getRandomFloat(1,100);
  coords[0] = x1;
  coords[1] = x1 + height;
  coords[2] = y1;
  coords[3] = y1 + width;
  return coords;
}

void RandomRectangleGenerator::generateDataFile(int n) {
  std::ofstream pFile;
  pFile.open("testt1.txt");
  for (int i=0; i<n; i++){
    int* coords = generateRandomRect();
    pFile << std::to_string(coords[0]) + "," + std::to_string(coords[1]) + "," + std::to_string(coords[2]) + "," + std::to_string(coords[3]) + "\n";
  }
  pFile.close();
}