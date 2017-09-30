//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_RTREE_H
#define tarea1_logaritmos_RTREE_H


#include <vector>
#include "Rectangle.h"
#include "SplitHeuristic.h"
#include "commontypes.h"

class SplitHeuristic;
class RTree{
private:
  vRect node;
  std::string inputFilename;
  SplitHeuristic *splitHeuristic;
  std::string rootFilename;
public:

  RTree(SplitHeuristic * splitHeuristic, std::string inputFilename);

  std::vector<int> search(Rectangle &rectangle);

  std::vector<int> insert(Rectangle &rectangle);


  const vRect &getNode() const;
};

#endif //tarea1_logaritmos_RTREE_H
