//
// Created by Cristobal M on 9/26/17.
//

#include "RTree.h"
#include "IOControl.h"

bool intersect(Rectangle &r1, Rectangle&r2){
    return !((r1.x1 > r2.x2) or
        (r1.y1 > r2.y2) or
        (r2.x1 > r1.x2) or
        (r2.y1 > r1.y2));
}

RTree::RTree(SplitHeuristic *splitHeuristic, std::string rootFilename, std::string parentFilename,
             int parentRectangleIndex, int memorySize) :  splitHeuristic(splitHeuristic),
                                                          rootFilename(rootFilename),
                                                          parentFilename(parentFilename),
                                                          parentRectangleIndex(parentRectangleIndex),
                                                          M(memorySize) {

}
RTree::RTree(SplitHeuristic *splitHeuristic, std::string rootFilename, int memorySize) :
  RTree(splitHeuristic, rootFilename, nullptr, -1, memorySize)
{}


RTree::RTree(SplitHeuristic *splitHeuristic, std::string rootFilename) : RTree(splitHeuristic, rootFilename, defaultMemorySize) {
}




std::vector<int> RTree::search(Rectangle &rectangle) {
    std::vector<int> found;
    this->Rsearch(rectangle, found);
    return found;
}

void insert(Rectangle &rectangle) {
    if (this->isLeaf){
        /*if (this->node.length()== M){
         *  llamar a la heuristica
         *}*/
        this->node.push_back(rectangle);
    } else {
        Rectangle min_rectangle = null;
        float req_gr = std::numeric_limits<float>::max();
        float area = std::numeric_limits<float>::max();
        for (auto &node_rect : this->node) {
            float new_req_gr = required_growth(node_rect, rectangle);
            float new_area = node_rect.area();
                if (new_req_gr < req_gr){
                    area = new_area;
                    req_gr = new_req_gr;
                    min_rectangle = node_rect;
                } else if (new_req_gr == req_gr) {
                    if (area < new_area) {
                        area = new_area;
                        req_gr = new_req_gr;
                        min_rectangle = node_rect;
                    } else if (area == new_area){
                        if (rand() % 2 == 1) {
                            area = new_area;
                            req_gr = new_req_gr;
                            min_rectangle = node_rect;
                        }
                    }
                }
        }
        std::string current_name = "rtree" + std::to_string(save_number) + ".txt";
        std::string next_name = min_rectangle.address;
        IOControl::saveRTree(*this, current_name);
        save_number++;
        RTree next_rtree = IOControl::getRTree(next_name);
        next_rtree.insert(rectangle);
    }

}

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
