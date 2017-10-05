//
// Created by Cristobal M on 10/3/17.
//

#ifndef LOGARITMOS_TAREA1_RTREECONTROLLER_H
#define LOGARITMOS_TAREA1_RTREECONTROLLER_H


#include "RTree.h"


class RTreeController {
  RTree currentNode;
  int rootFilenameIndex;
  int memorySize;
public:


  explicit RTreeController(int rootFilenameIndex);
  RTreeController(int rootFilenameIndex, int memorySize);

  template<class Heuristic>
  void insert(Rectangle &rectangle);

  std::vector<int> search(RTree &rtree, Rectangle &rectangle);
  void Rsearch(RTree &rtree, Rectangle &rectangle, std::vector<int> &found);

  int getRootFilenameIndex() const;


};


#endif //LOGARITMOS_TAREA1_RTREECONTROLLER_H
