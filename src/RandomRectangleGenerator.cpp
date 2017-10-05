//
// Created by splatt on 04-10-17.
//

#include <iostream>
#include <fstream>
#include <random>
#include <cstdio>
#include "RandomRectangleGenerator.h"

int* RandomRectangleGenerator::generateRandomRect(std::default_random_engine generator) {
  int coords[4];
  std::uniform_int_distribution<float> coordinatesDistribution(0,500000);
  std::uniform_int_distribution<float> heightWidthDistribution(1,100);
  float x1 = coordinatesDistribution(generator);
  float y1 = coordinatesDistribution(generator);
  float height = heightWidthDistribution(generator);
  float width = heightWidthDistribution(generator);
  coords[0] = x1;
  coords[1] = x1 + height;
  coords[2] = y1;
  coords[3] = y1 + width;
  return coords;
}

void RandomRectangleGenerator::generateDataFile(int n) {
  std::default_random_engine generator;
  std::ofstream pFile;
  pFile.open("testt1.txt");
  for (int i=0; i<n; i++){
    int* coords = generateRandomRect(generator);
    pFile << std::to_string(coords[0]) + std::to_string(coords[1]) + std::to_string(coords[2]) + std::to_string(coords[3]) + ";";
  }
  pFile.close();
}