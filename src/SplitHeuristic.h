//
// Created by Cristobal M on 10/3/17.
//

#ifndef LOGARITMOS_TAREA1_SPLITHEURISTIC_H
#define LOGARITMOS_TAREA1_SPLITHEURISTIC_H



#include "commontypes.h"
#include "RTree.h"

struct splittedNode{
  vRect left, right;
  Rectangle leftParent, rightParent;
};

class SplitHeuristic {
public:
  virtual ~SplitHeuristic() = default;
  virtual splittedNode split(vRect &vrect) = 0;
  virtual std::string heuristicName() = 0;
  std::pair<int, int> mostDistantPair(vRect &);
  std::vector<long> fisherYatesVariation(long result_size, long choice_set_size);

  void splitNode(std::shared_ptr<RTree> rtree, std::string controllerPrefix, CachingRTree &Cached);
};

#endif //LOGARITMOS_TAREA1_SPLITHEURISTIC_H