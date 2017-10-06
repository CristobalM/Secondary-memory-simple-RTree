//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_RECTANGLE_H
#define tarea1_logaritmos_RECTANGLE_H

#include <string>
#include <vector>
#include <boost/serialization/access.hpp>

struct RectContainer{
  float leftX, rightX, bottomY, topY;
};
class Rectangle{
public:
  float x1, x2, y1, y2;
  int address;
  Rectangle();
  Rectangle(float x1, float x2, float y1, float y2, int address);

  Rectangle(float x1, float x2, float y1, float y2);


  Rectangle deriveParent();

  static float getArea(Rectangle &rectangle);

  bool intersect(Rectangle &otherRect);

  float areaIncrease(Rectangle &src);
  void enlargeToContain(Rectangle &src);

  static Rectangle findMBR(std::vector<Rectangle> &vrect);

  RectContainer findMBR(Rectangle &rect1, Rectangle &rect2);
};



namespace boost{
  namespace serialization{
    template<class Archive>
    void serialize(Archive &ar, Rectangle rectangle, const unsigned int version) {
      ar & rectangle.x1;
      ar & rectangle.x2;
      ar & rectangle.y1;
      ar & rectangle.y2;
      ar & rectangle.address;
    }
  }
}



#endif //tarea1_logaritmos_RECTANGLE_H
