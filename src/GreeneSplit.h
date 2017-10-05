//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_GREENESPLIT_H
#define tarea1_logaritmos_GREENESPLIT_H


#include "SplitHeuristic.h"

class GreeneSplit : public SplitHeuristic {
public:
  splittedNode split(vRect &vrect) override ;
  bool horMostDistantDimension(vRect &vRect);

  Rectangle MBR(vRect &vector);
};


#endif //tarea1_logaritmos_GREENESPLIT_H
