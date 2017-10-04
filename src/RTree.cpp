//
// Created by Cristobal M on 9/26/17.
//

#include <limits>
#include "RTree.h"
#include "IOControl.h"


RTree::RTree(std::string inputFilename) {
    this->inputFilename = inputFilename;
}


const std::string &RTree::getInputFilename() const {
    return inputFilename;
}

bool RTree::isLeaf() const {
    return leaf;
}