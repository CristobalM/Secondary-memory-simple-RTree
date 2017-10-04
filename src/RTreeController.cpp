//
// Created by Cristobal M on 10/3/17.
//

#include <cstdlib>
#include "RTreeController.h"
#include "IOControl.h"



std::vector<int> RTreeController::search(RTree &rtree, Rectangle &rectangle) {
  std::vector<int> found;
  Rsearch(rtree, rectangle, found);
  return found;
}

void RTreeController::Rsearch(RTree &rtree, Rectangle &rectangle, std::vector<int> &found) {
  if (rtree.isLeaf())
  {
    for (auto &node_rect : rtree.node) {
      if (node_rect.intersect(rectangle)) {
        found.push_back(atoi(node_rect.address));
      }
    }
  } else {
    for (auto &node_rect : rtree.node) {
      if (node_rect.intersect(rectangle)) {
        std::string current_name = rtree.getInputFilename(); //"rtree" + std::to_string(save_number) + ".txt";
        std::string next_name = node_rect.address;
        IOControl::saveRTree(rtree, current_name);
        //save_number++;
        rtree = IOControl::getRTree(next_name);
        Rsearch(rtree, rectangle, found);
        rtree = IOControl::getRTree(current_name);
      }
    }
  }
}

void RTreeController::insert(Rectangle &rectangle) {
    if (currentNode.leaf){
        /*if (this->node.length()== M){
         *  llamar a la heuristica
         *}*/
      currentNode.node.push_back(rectangle);
    } else {
        Rectangle min_rectangle;
        float req_gr = std::numeric_limits::max();
        float area = std::numeric_limits::max();
        for (auto &node_rect : currentNode.node) {
            float new_req_gr = node_rect.areaIncrease(rectangle);
            float new_area = Rectangle::getArea(node_rect);
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
        std::string next_name = min_rectangle.address;
        IOControl::saveRTree(currentNode, currentNode.getInputFilename());
        currentNode = IOControl::getRTree(next_name);
        insert(rectangle);
    }

}


RTreeController::RTreeController(std::string rootFilename) : RTreeController(rootFilename, DEFAULT_MEMORY_SIZE){}

RTreeController::RTreeController(std::string rootFilename, int memorySize) : rootFilename(rootFilename),
                                                                            currentNode(IOControl::getRTree(rootFilename)),
                                                                            memorySize(memorySize) {}
