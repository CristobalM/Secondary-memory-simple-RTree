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
private:
  vRect node;
  bool leaf = true;
public:
  bool isLeaf() const;

private:
  std::string inputFilename;
  std::string parentFilename;
  int parentRectangleIndex;

  template<class Archive>
  friend void boost::serialization::serialize(Archive &, RTree &, const unsigned int);

public:

  const std::string &getInputFilename() const;


  RTree(std::string inputFilename);

  //void insert(Rectangle &rectangle);

  //float required_growth(Rectangle &rectangle1, Rectangle &rectangle2);
};

namespace boost{
  namespace serialization{
    template<class Archive>
    void serialize(Archive &ar, RTree &rTree, const unsigned int version) {
      ar & rTree.node;
      ar & rTree.leaf;
      ar & rTree.parentFilename;
      ar & rTree.parentRectangleIndex;
    }


  }
}

#endif //tarea1_logaritmos_RTREE_H
