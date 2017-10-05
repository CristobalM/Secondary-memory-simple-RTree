//
// Created by Cristobal M on 9/26/17.
//

#include <limits>
#include "Rectangle.h"
#include "commontypes.h"

Rectangle::Rectangle(float x1, float x2, float y1, float y2, int address, bool isLeaf) :
  x1(x1), x2(x2), y1(y1), y2(y2), address(address) {}

float Rectangle::getArea(Rectangle &rectangle) {
  return (rectangle.x2 - rectangle.x1) * (rectangle.y2 - rectangle.y1);
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

RectContainer findMBR(vRect &vrect){
  float minX1, minY1;
  minX1 = minY1 = std::numeric_limits<float>::infinity();
  float maxX2, maxY2;
  maxX2 = maxY2 = -std::numeric_limits<float>::infinity();
  for (auto &rect : vrect){
    if (rect.x1 < minX1){
      minX1 = rect.x1;
    }
    if (rect.x2 > maxX2){
      maxX2 = rect.x2;
    }
    if (rect.y1 < minY1){
      minY1 = rect.y1;
    }
    if (rect.y2 > maxY2){
      maxY2 = rect.y2;
    }
  }
  RectContainer out;
  out.leftX = minX1;
  out.rightX = maxX2;
  out.bottomY = minY1;
  out.topY = maxY2;
  return out;
}

float Rectangle::areaIncrease(Rectangle &src) {
  RectContainer mbr = findMBR(*this, src);
  float rectArea = (this->x2 - this->x1) * (this->y2 - this->y1);
  float incToArea = (mbr.rightX - mbr.leftX) * (mbr.topY - mbr.bottomY);

  return incToArea - rectArea;
}

bool Rectangle::intersect(Rectangle &otherRect) {
    return !((this->x1 > otherRect.x2) or
             (this->y1 > otherRect.y2) or
             (otherRect.x1 > this->x2) or
             (otherRect.y1 > this->y2));
}

Rectangle Rectangle::deriveParent(int childaddr) {
  return Rectangle(x1, x2, y1, y2, childaddr, false);
}

void Rectangle::enlargeToContain(Rectangle &src) {
  RectContainer mbr = findMBR(*this, src);
  x1 = mbr.leftX;
  x2 = mbr.rightX;
  y1 = mbr.bottomY;
  x1 = mbr.topY;
}
