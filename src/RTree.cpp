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

RTree::RTree(SplitHeuristic *splitHeuristic, std::string rootFilename) : rootFilename(rootFilename) {}

std::vector<int> RTree::search(Rectangle &rectangle) {
    std::vector<int> found;
    this->Rsearch(rectangle, found);
    return found;
}

std::vector<int> RTree::insert(Rectangle &rectangle) {
    return std::vector<int>();
}

void RTree::Rsearch(Rectangle &rectangle, std::vector<int> &found) {
    if (this->isLeaf)
    {
      for (auto &node_rect : this->node) {
        if (intersect(node_rect, rectangle)) {
          found.push_back(atoi(node_rect.address));
        }
      }
    } else {
      for (auto &node_rect : this->node) {
        if (intersect(node_rect, rectangle)) {
          std::string current_name = "rtree" + std::to_string(save_number) + ".txt";
          std::string next_name = node_rect.address;
          IOControl::saveRTree(*this, current_name);
          save_number++;
          RTree next_rtree = IOControl::getRTree(next_name);
          next_rtree.Rsearch(rectangle, found);
          *this = IOControl::getRTree(current_name);
        }
      }
    }
}
