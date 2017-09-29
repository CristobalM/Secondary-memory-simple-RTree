//
// Created by Cristobal M on 9/26/17.
//

#include "Rectangle.h"

Rectangle::Rectangle(float x1, float x2, float y1, float y2, std::string &address, bool isLeaf) :
  x1(x1), x2(x2), y1(y1), y2(y2), address(address), isLeaf(isLeaf) {}

Rectangle::Rectangle() = default;
