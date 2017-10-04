//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_RTREE_H
#define tarea1_logaritmos_RTREE_H


#include <vector>
#include "Rectangle.h"
#include "SplitHeuristic.h"
#include "commontypes.h"

const int defaultMemorySize = 1000000;

class RTree {
private:
  vRect node;
  bool isLeaf = true;
  SplitHeuristic *splitHeuristic;
  std::string rootFilename;
  std::string parentFilename;
  int parentRectangleIndex;

  void Rsearch(Rectangle &rectangle, std::vector<int> &found);

  template<class Archive>
  friend void boost::serialization::serialize(Archive &, RTree &, const unsigned int);

  int M;
public:
  RTree(SplitHeuristic *splitHeuristic, std::string rootFilename, std::string parentFilename, int parentRectangleIndex,
        int memorySize);

  RTree(SplitHeuristic *splitHeuristic, std::string rootFilename, int memorySize);

  RTree(SplitHeuristic *splitHeuristic, std::string rootFilename);

  std::vector<int> search(Rectangle &rectangle);

  void insert(Rectangle &rectangle);
};


namespace boost{
  namespace serialization{
    template<class Archive>
    void serialize(Archive &ar, RTree &rTree, const unsigned int version) {
      ar & rTree.node;
      ar & rTree.rootFilename;
      ar & rTree.isLeaf;
      ar & rTree.parentFilename;
      ar & rTree.parentRectangleIndex;
    }
  }
}







#endif //tarea1_logaritmos_RTREE_H
