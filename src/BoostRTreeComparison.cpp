//
// Created by Cristobal M on 10/7/17.
//
#include <iostream>
#include <vector>
#include <fstream>
#include "Rectangle.h"
#include "SplitHeuristic.h"

#include "RandomRectangleGenerator.h"
#include "IOControl.h"

#include "Experiments.h"
#include "FilenameGenerator.h"

#include <sys/resource.h>
#include <boost/filesystem/operations.hpp>

#include <boost/geometry.hpp>
#include <boost/foreach.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;
typedef std::pair<box, unsigned> value;

void processInputBoostExperiment(std::string fname, bgi::rtree< value, bgi::quadratic<113> > rtree){
    std::ifstream infile(fname);
    int index = 0;
    while (infile) {
        std::string s;
        if (!getline(infile, s)) break;
        std::istringstream ss(s);
        std::vector <std::string> record;
        int count = 0;
        float minX, maxX, minY, maxY;
        minX = minY = std::numeric_limits<float>::infinity();
        maxX = maxY = -std::numeric_limits<float>::infinity();
        while (ss){
            std::string s2;
            if (!getline( ss, s2, ',')){
                break;
            }
            float coordinate = (float) ::atof(s2.c_str());
            if(count % 2 == 0){
                if(minX > coordinate){
                    minX = coordinate;
                }
                if(maxX < coordinate){
                    maxX = coordinate;
                }
            }
            else{
                if(minY > coordinate){
                    minY = coordinate;
                }
                if(maxY < coordinate){
                    maxY = coordinate;
                }
            }
            count++;
        }
        Rectangle mbr(minX, maxX, minY, maxY, index);
        box b(point(mbr.x1, mbr.y1), point(mbr.x2, mbr.y2));
        rtree.insert(std::make_pair(b, index));
        index++;
    }
    if (!infile.eof()) {
        std::cerr << "Error during input file processing\n";
    }

}
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

void boostRTreeExperiment(){

    namespace bg = boost::geometry;
    namespace bgi = boost::geometry::index;
    typedef bg::model::point<float, 2, bg::cs::cartesian> point;
    typedef bg::model::box<point> box;
    typedef std::pair<box, unsigned> value;

    std::vector<std::string> buildTimeOutput;
    std::vector<std::string> searchTimeOutput;

    for (int i = 9; i <= 25; i++){
        bgi::rtree< value, bgi::quadratic<113> > rtree;
        std::string input = "generated2e" + std::to_string(i)  + ".txt";
        const int inputSize = 1 << i; // (int)std::pow(2, i);
        std::cout << "input size:" << inputSize << std::endl;
        RandomRectangleGenerator::generateDataFile(inputSize, input);
        vRect randomVRect = RandomRectangleGenerator::generateVRect(inputSize/10);
        for(int j = 0; j <= 1; j++) {
            Experiments::startExperiment("Build Rtree");
            processInputBoostExperiment(input, rtree);
            ExperimentData &experiment = Experiments::stopExperiment();

            std::string buildTimeStr, searchOutputStr;

            long buildTime =experiment.retrieveTimeElapsedNanoSeconds();
            buildTimeStr = std::to_string(inputSize)+","+
                           std::to_string(buildTime);


            //search
            long sumElapsedSearch = 0;


            std::vector<box> boxes;

            for(Rectangle &randomRectangle : randomVRect){
                box query_box(point(randomRectangle.x1, randomRectangle.y1), point(randomRectangle.x2, randomRectangle.y2));
                boxes.push_back(query_box);
            }

            for(box &randomBox : boxes){
                std::vector<value> result_s;
                Experiments::startExperiment("search");
                rtree.query(bgi::intersects(randomBox), std::back_inserter(result_s));
                ExperimentData &searchExperiment = Experiments::stopExperiment();
                sumElapsedSearch += searchExperiment.retrieveTimeElapsedNanoSeconds();
            }
            long averageDuration = sumElapsedSearch / randomVRect.size();

            searchOutputStr = std::to_string(inputSize)+","+
                              std::to_string(averageDuration);

            buildTimeOutput.push_back(buildTimeStr);
            searchTimeOutput.push_back(searchOutputStr);

            std::cout << "Build Time = ";
            std::cout << buildTime << std::endl;
            std::cout << "Search time = ";
            std::cout << averageDuration << std::endl << std::endl;

        }
        std::cout << std::endl << std::endl;
    }

    std::string anUuid = FilenameGenerator::makeUuid();
    writeToFile(anUuid, "experiment_build", "inputsize,heuristic,timeelapsed", buildTimeOutput);
    writeToFile(anUuid, "experiment_searchtime", "inputsize,heuristic,timeelapsed", searchTimeOutput);
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


int main(int argc, char * argv[]){
    increaseStackSize();
    boostRTreeExperiment();
    return 0;
}