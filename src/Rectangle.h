//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_RECTANGLE_H
#define tarea1_logaritmos_RECTANGLE_H

#include <string>
#include <boost/serialization/access.hpp>

class Rectangle{
public:
  float x1, x2, y1, y2;
  std::string address;
  bool isLeaf;
  Rectangle();
  Rectangle(float x1, float x2, float y1, float y2, std::string &address, bool isLeaf);
};


namespace boost{
  namespace serialization{
    template<class Archive>
    void serialize(Archive &ar, Rectangle rectangle, const unsigned int version) {
      ar & rectangle.x1;
      ar & rectangle.x2;
      ar & rectangle.y1;
      ar & rectangle.y1;
      ar & rectangle.address;
      ar & rectangle.isLeaf;
    }
  }
}



#endif //tarea1_logaritmos_RECTANGLE_H