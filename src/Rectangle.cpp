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

RectContainer findMBR(Rectangle &rect1, Rectangle &rect2){
  RectContainer out;
  out.leftX = std::min(rect1.x1, rect2.x1);
  out.rightX = std::max(rect1.x2, rect1.x2);
  out.bottomY = std::min(rect1.x1, rect2.x1);
  out.topY = std::max(rect1.x2, rect1.x2);
  return out;
}

float Rectangle::areaIncrease(Rectangle &src) {
  float leftX = std::min(this->x1, src.x1);
  float rightX = std::max(this->x2, this->x2);
  float bottomY = std::min(this->x1, src.x1);
  float topY = std::max(this->x2, this->x2);

  float rectArea = (this->x2 - this->x1) * (this->y2 - this->y1);
  float incToArea = (rightX - leftX) * (topY - bottomY);

  return incToArea - rectArea;
}

bool Rectangle::intersect(Rectangle &otherRect) {
    return !((this->x1 > otherRect.x2) or
             (this->y1 > otherRect.y2) or
             (otherRect.x1 > this->x2) or
             (otherRect.y1 > this->y2));
}

Rectangle Rectangle::deriveParent(std::string childaddr) {
  return Rectangle(x1, x2, y1, y2, childaddr, false);
}

void Rectangle::enlargeToContain(Rectangle &src) {
  float leftX = std::min(this->x1, src.x1);
  float rightX = std::max(this->x2, this->x2);
  float bottomY = std::min(this->x1, src.x1);
  float topY = std::max(this->x2, this->x2);
}
