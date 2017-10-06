//
// Created by cristobal on 06-10-17.
//

#include "Experiments.h"

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
    currentExperiment.timeElapsed = currentExperiment.endTime - currentExperiment.startTime;
    return currentExperiment;
}

