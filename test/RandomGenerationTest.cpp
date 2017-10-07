//
// Created by Cristobal M on 10/5/17.
//

#include "../src/GreeneSplit.h"
#include "../src/LinearSplit.h"

#include <gtest/gtest.h>
#include "../src/RandomRectangleGenerator.h"
#include "../src/IOControl.h"
#include "../src/RTreeController.h"
#include "../src/Experiments.h"

/*
TEST(RandomGenerationTest, CanRead) {
    SplitHeuristic *heuristic = new LinearSplit();
    std::string input = "canread.txt";
    RandomRectangleGenerator::generateDataFile(15000, input);
    RTreeController controller = IOControl::processInput(input, heuristic);
    IOControl::checkCache(controller.getControllerPrefix(), controller.Cached, true, true);

    delete heuristic;
}
 */


TEST(BigTest, Test1) {
    std::string input = "generated2e" + std::to_string(22)  + ".txt";
    const int inputSize = 1 << 23; // (int)std::pow(2, i);
    std::cout << "input size:" << inputSize << std::endl;
    RandomRectangleGenerator::generateDataFile(inputSize, input);
    vRect randomVRect = RandomRectangleGenerator::generateVRect(1000);

    LinearSplit linearSplit;
    std::cout << linearSplit.heuristicName() << std::endl;
    Experiments::startExperiment("Build Rtree");
    RTreeController controller = IOControl::processInput(input, &linearSplit);
    ExperimentData &experiment = Experiments::stopExperiment();

    std::string buildTimeStr, spaceOutputStr, percentageOutputStr, searchOutputStr;

    long buildTime =experiment.retrieveTimeElapsedNanoSeconds();
    buildTimeStr = std::to_string(inputSize)+","+
        linearSplit.heuristicName()+","+
        std::to_string(buildTime);


    //search


    float percentageOutput = (float)Experiments::averageRectanglesPerNode(controller) / (float)DEFAULT_MAX_NODE_SIZE;
    percentageOutputStr = std::to_string(inputSize)+","+
        linearSplit.heuristicName()+","+
        std::to_string(percentageOutput);

    long sumElapsedSearch = 0;
    for(Rectangle &randomRectangle : randomVRect){
        Experiments::startExperiment("search");
        controller.search(randomRectangle);
        ExperimentData &searchExperiment = Experiments::stopExperiment();
        sumElapsedSearch += searchExperiment.retrieveTimeElapsedNanoSeconds();
    }
    long averageDuration = sumElapsedSearch / randomVRect.size();

    searchOutputStr = std::to_string(inputSize)+","+
                      linearSplit.heuristicName()+","+
                      std::to_string(averageDuration);


    IOControl::checkCache(controller.getControllerPrefix(), controller.Cached, true, true);

    long spaceOutput = IOControl::spaceOccupied(controller.getControllerPrefix());
    spaceOutputStr =  std::to_string(inputSize)+","+
                      linearSplit.heuristicName()+","+
                      std::to_string(spaceOutput);


    std::cout << "Build Time = ";
    std::cout << buildTime << std::endl;
    std::cout << "Occupied space = ";
    std::cout << spaceOutput << std::endl;
    std::cout << "Page disk percentage = ";
    std::cout << percentageOutput << std::endl;
    std::cout << "Search time = ";
    std::cout << averageDuration << std::endl << std::endl;
    IOControl::cleanControllerData(controller.getControllerPrefix());
    controller.Cached.clear();
}
