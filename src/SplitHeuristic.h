//
// Created by Cristobal M on 10/3/17.
//

#ifndef LOGARITMOS_TAREA1_SPLITHEURISTIC_H
#define LOGARITMOS_TAREA1_SPLITHEURISTIC_H


#include "commontypes.h"

class SplitHeuristic {
  virtual std::pair<vRect, vRect> split(vRect &) = 0;
};


#endif //LOGARITMOS_TAREA1_SPLITHEURISTIC_H
