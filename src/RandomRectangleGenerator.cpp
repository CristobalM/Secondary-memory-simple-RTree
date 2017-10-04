//
// Created by splatt on 04-10-17.
//

#include <random>
#include "RandomRectangleGenerator.h"

Rectangle RandomRectangleGenerator::generateRandomRect(std::default_random_engine generator) {
  std::uniform_int_distribution<float> coordinatesDistribution(0,500000);
  std::uniform_int_distribution<float> heightWidthDistribution(1,100);
  float x1 = coordinatesDistribution(generator);
  float y1 = coordinatesDistribution(generator);
  float height = heightWidthDistribution(generator);
  float width = heightWidthDistribution(generator);
  return Rectangle(x1, x1+width, y1, y1+height, currentIndex++, true);
}

void RandomRectangleGenerator::generateDataFile(int n) {
  std::default_random_engine generator;
}

