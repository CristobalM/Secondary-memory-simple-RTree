//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_GREENESPLIT_H
#define tarea1_logaritmos_GREENESPLIT_H


#include "SplitHeuristic.h"

class GreeneSplit : SplitHeuristic {
  std::pair<vRect, vRect> split(vRect &) override ;

  std::pair<vRect, vRect> split(vRect &vRect, std::string parentFilename, int parentRectangleIndex);
};


#endif //tarea1_logaritmos_GREENESPLIT_H
