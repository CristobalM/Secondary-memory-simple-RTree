//
// Created by Cristobal M on 9/26/17.
//

#include "Rectangle.h"

Rectangle::Rectangle(float x1, float x2, float y1, float y2, std::string &address, bool isLeaf) :
  x1(x1), x2(x2), y1(y1), y2(y2), address(address) {}

float Rectangle::getArea(Rectangle &rectangle) {
  return (rectangle.x2 - rectangle.x1) * (rectangle.y2 - rectangle.y1);
}

Rectangle Rectangle::MBR(Rectangle &rectangle1, Rectangle &rectangle2) {
  std::string mt = "";
  Rectangle mbr = Rectangle(std::min(rectangle1.x1, rectangle2.x1),
                            std::max(rectangle1.x2, rectangle2.x2),
                            std::min(rectangle1.y1, rectangle2.y1),
                            std::max(rectangle1.y2, rectangle2.y2),
                            mt, false);
  return mbr;
}

Rectangle::Rectangle() = default;


float Rectangle::areaIncrease(Rectangle &src) {
  float leftX = std::min(this->x1, src.x1);
  float rightX = std::max(this->x2, this->x2);
  float bottomY = std::min(this->x1, src.x1);
  float topY = std::max(this->x2, this->x2);

  float rectArea = (this->x2 - this->x1) * (this->y2 - this->y1);
  float incToArea = (rightX - leftX) * (topY - bottomY);

  return incToArea - rectArea;
}