//
// Created by Cristobal M on 10/3/17.
//

#include <cstdlib>
#include "RTreeController.h"
#include "IOControl.h"
#include "FilenameGenerator.h"
#include "SplitHeuristic.h"


std::vector<int> RTreeController::search(Rectangle &rectangle) {
    std::vector<int> found;
    beginAtRoot();
    Rsearch(currentNode, rectangle, found);
    return found;
}

void RTreeController::Rsearch(RTree &rtree, Rectangle &rectangle, std::vector<int> &found) {
  if (rtree.isLeaf()) {
    for (auto &node_rect : rtree.node) {
      if (node_rect.intersect(rectangle)) {
        found.push_back(node_rect.address);
      }
    }
  }
  else {
    for (auto &node_rect : rtree.node) {
      if (node_rect.intersect(rectangle)) {
        int current_index = rtree.getInputFilenameIndex();
        IOControl::saveRTree(rtree, current_index, controllerPrefix);
        rtree = IOControl::getRTree(node_rect.address, controllerPrefix);
        Rsearch(rtree, rectangle, found);
        rtree = IOControl::getRTree(current_index, controllerPrefix);
      }
    }
  }
}


void RTreeController::insert(Rectangle &rectangle) {
    beginAtRoot();
    insertRec(rectangle);
}

void RTreeController::insertRec(Rectangle &rectangle) {
    if (currentNode.leaf){
        currentNode.node.push_back(rectangle);
        splitHeuristic->splitNode(currentNode, controllerPrefix);
        IOControl::saveRTree(currentNode,
                             currentNode.getInputFilenameIndex(),
                             controllerPrefix);
    } else {
        Rectangle min_rectangle;
        float req_gr = std::numeric_limits<float>::max();
        float area = std::numeric_limits<float>::max();
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
        //std::string next_name = FilenameGenerator::getStringFromIndex(min_rectangle.address, controllerPrefix);
        IOControl::saveRTree(currentNode,
                             currentNode.getInputFilenameIndex(),
                             controllerPrefix);
        currentNode = IOControl::getRTree(min_rectangle.address, controllerPrefix);
        insertRec(rectangle);
    }
}


RTreeController::RTreeController(int rootFilenameIndex, SplitHeuristic *heuristic) :
    RTreeController(rootFilenameIndex, DEFAULT_MAX_NODE_SIZE, heuristic){}

RTreeController::RTreeController(int rootFilenameIndex, int memorySize, SplitHeuristic *heuristic) :
    rootFilenameIndex(rootFilenameIndex),
    controllerPrefix(FilenameGenerator::makeUuid()),
    memorySize(memorySize),
    splitHeuristic(heuristic) {
    currentNode = IOControl::getRTree(rootFilenameIndex, controllerPrefix);
}

int RTreeController::getRootFilenameIndex() const {
    return rootFilenameIndex;
}

std::string RTreeController::getControllerPrefix() {
    return  controllerPrefix;
}

void RTreeController::beginAtRoot() {
    currentNode = IOControl::getRTree(rootFilenameIndex, controllerPrefix);
}


//inefficient, only for debug
vRect RTreeController::extractDataMBRS() {
    beginAtRoot();
    vRect out;
    extractDataMBRSRec(out);
    beginAtRoot();
    return out;
}

void RTreeController::extractDataMBRSRec(vRect &partial) {
    long sz = partial.size();
    if(currentNode.isLeaf()){
        partial.insert(partial.end(), currentNode.node.begin(), currentNode.node.end());
    }
    else {
        int parentIndex = currentNode.inputFilenameIndex;
        for (int i = 0; i < currentNode.node.size(); i++) {
            Rectangle &rect = currentNode.node[i];
            currentNode = IOControl::getRTree(rect.address, controllerPrefix);
            extractDataMBRSRec(partial);
            currentNode = IOControl::getRTree(parentIndex, controllerPrefix);
        }
    }
}

