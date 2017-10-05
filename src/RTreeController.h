//
// Created by Cristobal M on 10/3/17.
//

#ifndef LOGARITMOS_TAREA1_RTREECONTROLLER_H
#define LOGARITMOS_TAREA1_RTREECONTROLLER_H


#include "RTree.h"
#include "SplitHeuristic.h"

class RTreeController {
  int rootFilenameIndex;
  int memorySize;
  SplitHeuristic *splitHeuristic;
public:
  RTree currentNode;


  explicit RTreeController(int rootFilenameIndex, SplitHeuristic *heuristic);
  RTreeController(int rootFilenameIndex, int memorySize, SplitHeuristic *);

  void insert(Rectangle &rectangle);

  std::vector<int> search(RTree &rtree, Rectangle &rectangle);
  void Rsearch(RTree &rtree, Rectangle &rectangle, std::vector<int> &found);

  int getRootFilenameIndex() const;


};


#endif //LOGARITMOS_TAREA1_RTREECONTROLLER_H
