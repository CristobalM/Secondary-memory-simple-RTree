//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_RTREE_H
#define tarea1_logaritmos_RTREE_H


#include <vector>
#include "Rectangle.h"
#include "commontypes.h"

class RTree{
  friend class RTreeController;
public:
  vRect node;
  bool leaf = true;

  int inputFilenameIndex;
  int parentFilenameIndex = -1;
  int parentRectangleIndex = -1;

  template<class Archive>
  friend void boost::serialization::serialize(Archive &, RTree &, const unsigned int);

  bool isLeaf() const;

  int getInputFilenameIndex();


  RTree(vRect &node, int inputFilenameIndex, bool leaf, int parentFilenameIndex, int parentRectangleIndex);
  RTree(int inputFilenameIndex);
  RTree();

  void setParentRectangleIndex(int newIndex);
  void setParentFilenameIndex(int newIndex);

  //void insert(Rectangle &rectangle);

  //float required_growth(Rectangle &rectangle1, Rectangle &rectangle2);
};

namespace boost{
  namespace serialization{
    template<class Archive>
    void serialize(Archive &ar, RTree &rTree, const unsigned int version) {
      ar & rTree.node;
      ar & rTree.leaf;
      ar & rTree.inputFilenameIndex;
      ar & rTree.parentFilenameIndex;
      ar & rTree.parentRectangleIndex;
    }
  }
}

#endif //tarea1_logaritmos_RTREE_H
