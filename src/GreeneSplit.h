//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_GREENESPLIT_H
#define tarea1_logaritmos_GREENESPLIT_H


#include "SplitHeuristic.h"

class GreeneSplit : SplitHeuristic {
public:
  splittedNode split(vRect &vrect, std::string parentFilename, int parentRectangleIndex) override ;
  bool horMostDistantDimension(vRect &vRect);
};


#endif //tarea1_logaritmos_GREENESPLIT_H
