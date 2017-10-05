//
// Created by Cristobal M on 9/26/17.
//

#include <limits>
#include "RTree.h"
#include "IOControl.h"


RTree::RTree(int inputFilenameIndex) {
    this->inputFilenameIndex = inputFilenameIndex;
}


const int RTree::getInputFilenameIndex() const {
    return inputFilenameIndex;
}

bool RTree::isLeaf() const {
    return leaf;
}

RTree::RTree(vRect &node, int inputFilenameIndex, bool leaf, int parentFilenameIndex,
             int parentRectangleIndex) : RTree(inputFilenameIndex), leaf(leaf), parentFilenameIndex(parentFilenameIndex) {
}
