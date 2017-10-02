//
// Created by Cristobal M on 9/26/17.
//

#include "RTree.h"
#include "IOControl.h"

bool intersect(Rectangle &r1, Rectangle&r2){
    return ((r1.x1 > r2.x2) or
        (r1.y1 > r2.y2) or
        (r2.x1 > r1.x2) or
        (r2.y1 > r1.y2));
}

RTree::RTree(SplitHeuristic *splitHeuristic, std::string rootFilename) {
    this->splitHeuristic = splitHeuristic;
}

std::vector<int> RTree::search(Rectangle &rectangle) {
    std::vector<int> found;
    this->Rsearch(rectangle, found);
    return found;
}

std::vector<int> RTree::insert(Rectangle &rectangle) {
    return std::vector<int>();
}

void RTree::Rsearch(Rectangle &rectangle, std::vector<int> &found) {
    for (auto &node_rect : this->node)
    {
      if (intersect(node_rect, rectangle)){
        if (node_rect.isLeaf){
          found.push_back(atoi(node_rect.address));
        }
        else{
          std::string fname = node_rect.address;
          IOControl::saveRTree(*this, "test.txt");
          RTree next_rtree = IOControl::getRTree(fname);
          next_rtree.Rsearch(rectangle, found);
        }
      }
    }
}
