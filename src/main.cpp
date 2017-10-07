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

#include <sys/resource.h>
#include <boost/filesystem/operations.hpp>


void writeToFile(std::string uuid, std::string file_name, std::string fileheader, std::vector<std::string> contents){
    std::string output_folder = "output_folder";
    if(!boost::filesystem::exists(output_folder)){
        boost::filesystem::create_directory(output_folder);
    }

    std::ofstream ofs;
    ofs.open(output_folder+"/"+uuid+file_name);
    ofs << fileheader;
    ofs << "\n";
    for(std::string &s : contents){
        ofs << s;
        ofs << "\n";
    }
    ofs.close();
}

void make_experiments(){

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
        vRect randomVRect = RandomRectangleGenerator::generateVRect(inputSize/10);
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


            IOControl::checkCache(controller.getControllerPrefix(), controller.Cached, true, true);

            long spaceOutput = IOControl::spaceOccupied(controller.getControllerPrefix());
            spaceOutputStr =  std::to_string(inputSize)+","+
                              heuristics[j]->heuristicName()+","+
                              std::to_string(spaceOutput);


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
            IOControl::cleanControllerData(controller.getControllerPrefix());
            controller.Cached.clear();

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
}

void increaseStackSize(){
    const rlim_t kStackSize = 2000 * 1024 * 1024;   // min stack size = 100 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

}

int main() {
    increaseStackSize();
    make_experiments();

    return 0;
}