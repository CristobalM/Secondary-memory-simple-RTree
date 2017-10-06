//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_LINEARSPLIT_H
#define tarea1_logaritmos_LINEARSPLIT_H


#include "SplitHeuristic.h"

class LinearSplit : public SplitHeuristic {
public:
  splittedNode split(vRect &vrect) override ;
  std::string heuristicName() override ;
};



#endif //tarea1_logaritmos_LINEARSPLIT_H
