//
// Created by Cristobal M on 9/26/17.
//

#include "RTree.h"

std::vector<int> RTree::search(Rectangle &rectangle) {
    return std::vector<int>();
}

std::vector<int> RTree::insert(Rectangle &rectangle) {
    return std::vector<int>();
}

const vRect &RTree::getNode() const {
    return node;
}

RTree::RTree(SplitHeuristic *splitHeuristic, std::string inputFilename) {
    this->splitHeuristic = splitHeuristic;
    this->inputFilename = inputFilename;
}
