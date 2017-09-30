  //
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_LINEARSPLIT_H
#define tarea1_logaritmos_LINEARSPLIT_H

#include "SplitHeuristic.h"

class LinearSplit : SplitHeuristic {
private:
  std::vector<std::vector<float>> separation;
public:
  void split(RTree &rTree) override;
};



#endif //tarea1_logaritmos_LINEARSPLIT_H
