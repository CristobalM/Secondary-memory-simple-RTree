//
// Created by Cristobal M on 10/3/17.
//

#ifndef LOGARITMOS_TAREA1_SPLITHEURISTIC_H
#define LOGARITMOS_TAREA1_SPLITHEURISTIC_H


#include "commontypes.h"

class SplitHeuristic {
protected:
  virtual std::pair<vRect, vRect> split(vRect &) = 0;
  std::pair<int, int> mostDistantPair(vRect &);
  std::vector<long> fisherYatesVariation(long result_size, long choice_set_size);
  float areaIncrease(Rectangle &dst, Rectangle &src);
};



#endif //LOGARITMOS_TAREA1_SPLITHEURISTIC_H
