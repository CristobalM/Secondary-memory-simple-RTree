#include <iostream>
#include <vector>
#include <fstream>
#include "Rectangle.h"
#include "SplitHeuristic.h"
#include "LinearSplit.h"
#include "RandomRectangleGenerator.h"
#include "IOControl.h"
#include "RTreeController.h"
#include "GreeneSplit.h"
#include "Experiments.h"
#include "FilenameGenerator.h"


void writeToFile(std::string uuid, std::string file_name, std::string fileheader, std::vector<std::string> contents){
    std::ofstream ofs;
    ofs.open(uuid+file_name);
    ofs << fileheader;
    ofs << "\n";
    for(std::string &s : contents){
        ofs << s;
        ofs << "\n";
    }
    ofs.close();
}

int main() {

    SplitHeuristic *heuristics[2] = {new LinearSplit(), new GreeneSplit()};

    std::vector<std::string> buildTimeOutput;
    std::vector<std::string> occupiedSpaceOutput;
    std::vector<std::string> pageDiskPercentageOutput;
    std::vector<std::string> searchTimeOutput;


    for (int i = 9; i <= 25; i++){
        std::string input = "generated2e" + std::to_string(i)  + ".txt";
        const int inputSize = 1 << i; // (int)std::pow(2, i);
        std::cout << "input size:" << inputSize << std::endl;
        RandomRectangleGenerator::generateDataFile(inputSize, input);
        vRect randomVRect = RandomRectangleGenerator::generateVRect(1000);
        for(int j = 0; j <= 1; j++) {
            //construction
            std::cout << heuristics[j]->heuristicName() << std::endl;
            Experiments::startExperiment("Build Rtree");
            RTreeController controller = IOControl::processInput(input, heuristics[j]);
            ExperimentData &experiment = Experiments::stopExperiment();

            std::string buildTimeStr, spaceOutputStr, percentageOutputStr, searchOutputStr;

            long buildTime =experiment.retrieveTimeElapsedNanoSeconds();
            buildTimeStr = std::to_string(inputSize)+","+
                heuristics[j]->heuristicName()+","+
                std::to_string(buildTime);


            //search
            long spaceOutput = IOControl::spaceOccupied(controller.getControllerPrefix());
            spaceOutputStr =  std::to_string(inputSize)+","+
                heuristics[j]->heuristicName()+","+
                std::to_string(spaceOutput);

            float percentageOutput = (float)Experiments::averageRectanglesPerNode(controller) / (float)DEFAULT_MAX_NODE_SIZE;
            percentageOutputStr = std::to_string(inputSize)+","+
                heuristics[j]->heuristicName()+","+
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
                heuristics[j]->heuristicName()+","+
                std::to_string(averageDuration);


            buildTimeOutput.push_back(buildTimeStr);
            occupiedSpaceOutput.push_back(spaceOutputStr);
            pageDiskPercentageOutput.push_back(percentageOutputStr);
            searchTimeOutput.push_back(searchOutputStr);

            std::cout << "Build Time = ";
            std::cout << buildTime << std::endl;
            std::cout << "Occupied space = ";
            std::cout << spaceOutput << std::endl;
            std::cout << "Page disk percentage = ";
            std::cout << percentageOutput << std::endl;
            std::cout << "Search time = ";
            std::cout << averageDuration << std::endl << std::endl;
            controller.Cached.clear();
            IOControl::checkCache(controller.getControllerPrefix(), true, true);
        }
        std::cout << std::endl << std::endl;
    }

    std::string anUuid = FilenameGenerator::makeUuid();
    writeToFile(anUuid, "experiment_build", "inputsize,heuristic,timeelapsed", buildTimeOutput);
    writeToFile(anUuid, "experiment_occupiedspace", "inputsize,heuristic,space", occupiedSpaceOutput);
    writeToFile(anUuid, "experiment_pagediskpercentage", "inputsize,heuristic,percentage", pageDiskPercentageOutput);
    writeToFile(anUuid, "experiment_searchtime", "inputsize,heuristic,timeelapsed", searchTimeOutput);

    delete heuristics[0];
    delete heuristics[1];
    return 0;
}
