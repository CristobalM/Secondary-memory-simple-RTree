//
// Created by Cristobal M on 10/3/17.
//

#ifndef LOGARITMOS_TAREA1_RTREECONTROLLER_H
#define LOGARITMOS_TAREA1_RTREECONTROLLER_H


#include "RTree.h"
#include "SplitHeuristic.h"

template <class Heuristic>
class RTreeController {
  RTree currentNode;
  std::string rootFilename;
  //SplitHeuristic *splitHeuristic;

public:

  //RTreeController(SplitHeuristic *splitHeuristic, std::string rootFilename);
  RTreeController(std::string rootFilename);

  void insert(Rectangle &rectangle);

  std::vector<int> search(RTree &rtree, Rectangle &rectangle);
  void Rsearch(RTree &rtree, Rectangle &rectangle, std::vector<int> &found);

};


#endif //LOGARITMOS_TAREA1_RTREECONTROLLER_H
