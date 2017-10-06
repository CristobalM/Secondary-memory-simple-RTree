//
// Created by Cristobal M on 9/26/17.
//

#include "RTree.h"

RTree::RTree(int inputFilenameIndex) {
    this->inputFilenameIndex = inputFilenameIndex;
    this->parentFilenameIndex = -1;
}

bool RTree::isLeaf() const {
    return leaf;
}

RTree::RTree(vRect &node, int inputFilenameIndex, bool leaf, int parentFilenameIndex,
             int parentRectangleIndex){
    this->node = node;
    this->leaf = leaf;
    this->inputFilenameIndex = inputFilenameIndex;
    this->parentFilenameIndex = parentFilenameIndex;
    this->parentRectangleIndex = parentRectangleIndex;
}

int RTree::getInputFilenameIndex() {
    return inputFilenameIndex;
}

RTree::RTree() {

}

void RTree::setParentRectangleIndex(int newIndex){
    parentRectangleIndex = newIndex;
}

void RTree::setParentFilenameIndex(int newIndex) {
    parentFilenameIndex = newIndex;
}

