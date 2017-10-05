//
// Created by Cristobal M on 10/4/17.
//

#ifndef LOGARITMOS_TAREA1_SPLITBUILDER_H
#define LOGARITMOS_TAREA1_SPLITBUILDER_H


#include "commontypes.h"
#include "RTree.h"

class SplitBuilder {
private:
  vRect &vrect;
  std::pair<vRect, vRect> result;
public:
  SplitBuilder(vRect &vrect);
  void putLeft();
  void putRight();
  std::pair<vRect, vRect> getPair();

  Rectangle &getBackRectangle();

  int leftSize();
  int rightSize();
};


#endif //LOGARITMOS_TAREA1_SPLITBUILDER_H
