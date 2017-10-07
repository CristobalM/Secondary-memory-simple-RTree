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
  std::string controllerPrefix;

  void insertRec(Rectangle &rectangle);
  void Rsearch(std::shared_ptr<RTree> rtree, Rectangle &rectangle, std::vector<int> &found);

public:
  std::shared_ptr<RTree> currentNode;

  CachingRTree Cached;


  explicit RTreeController(int rootFilenameIndex, SplitHeuristic *heuristic);
  RTreeController(int rootFilenameIndex, int memorySize, SplitHeuristic *);

  void insert(Rectangle &rectangle);

  std::vector<int> search(Rectangle &rectangle);

  int getRootFilenameIndex() const;
  std::string getControllerPrefix();

  void beginAtRoot();

  vRect extractDataMBRS();
  void extractDataMBRSRec(vRect &partial);

};


#endif //LOGARITMOS_TAREA1_RTREECONTROLLER_H
