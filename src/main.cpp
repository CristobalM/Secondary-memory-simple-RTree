#include <iostream>
#include <vector>
#include "Rectangle.h"
#include "SplitHeuristic.h"
#include "LinearSplit.h"
#include "RandomRectangleGenerator.h"
#include "IOControl.h"
#include "RTreeController.h"
#include "GreeneSplit.h"
#include "Experiments.h"


int main() {

    SplitHeuristic *heuristics[2] = {new LinearSplit(), new GreeneSplit()};


    for (int i = 9; i <= 25; i++){
        for(int j = 0; j <= 1; j++) {
            std::string input = "generated2e" + std::to_string(i) + "_" + heuristics[j]->heuristicName() + ".txt";
            int inputSize = 1 << i; //(int)std::pow(2, i);
            RandomRectangleGenerator::generateDataFile(inputSize, input);
            Experiments::startExperiment("Build Rtree");
            RTreeController controller = IOControl::processInput(input, heuristics[j]);
            ExperimentData &experiment = Experiments::stopExperiment();

            std::cout << "Experiment " << heuristics[j]->heuristicName()  << ". inputSize = " << inputSize << std::endl;
            experiment.printExperiment();

        }
    }


    delete heuristics[0];
    delete heuristics[1];
    return 0;
}
