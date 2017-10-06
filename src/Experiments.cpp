//
// Created by cristobal on 06-10-17.
//

#include "Experiments.h"
#include "FilenameGenerator.h"
#include "IOControl.h"
ExperimentData Experiments::lastExperiment;

void Experiments::startExperiment(std::string name) {
    ExperimentData newExperiment;
    newExperiment.experimentName = name;
    newExperiment.startTime = std::chrono::high_resolution_clock::now();
    lastExperiment = newExperiment;
}

// returns delta time
ExperimentData& Experiments::stopExperiment() {
    ExperimentData &currentExperiment = lastExperiment;
    currentExperiment.endTime = std::chrono::high_resolution_clock::now();
    return currentExperiment;
}

long Experiments::averageRectanglesPerNode(RTreeController &controller) {
    controller.beginAtRoot();
    int node_quantity = 0;
    long result = node_quantity > 0 ? averageRectanglesPerNodeRec(controller, &node_quantity)/node_quantity : 0;
    controller.beginAtRoot();
    return result;
}

long Experiments::averageRectanglesPerNodeRec(RTreeController &controller, int *quantity_ptr) {
    long currentNodeQuantity = controller.currentNode.node.size();
    (*quantity_ptr)++;
    if(controller.currentNode.isLeaf()){
        return currentNodeQuantity;
    }
    else{
        long childrenSum = 0;
        int parentIndex = controller.currentNode.inputFilenameIndex;

        for(Rectangle &rect : controller.currentNode.node){
            controller.currentNode = IOControl::getRTree(rect.address, controller.getControllerPrefix());
            childrenSum += averageRectanglesPerNodeRec(controller, quantity_ptr);
            controller.currentNode = IOControl::getRTree(parentIndex, controller.getControllerPrefix());
        }
        return childrenSum + currentNodeQuantity;
    }
}

