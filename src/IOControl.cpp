//
// Created by cristobal on 28-09-17.
//

#include <fstream>
#include <boost/serialization/vector.hpp>
#include <sstream>
#include "IOControl.h"
#include "RTree.h"
#include "RTreeController.h"
#include "FilenameGenerator.h"

void IOControl::saveVRect(vRect vrect, std::string fname) {
    std::ofstream ofs(fname);

    boost::archive::text_oarchive oa(ofs);
    oa << vrect;
}

vRect IOControl::getVRect(std::string fname) {
    vRect out;
    std::ifstream ifs(fname);

    boost::archive::text_iarchive ia(ifs);
    ia >> out;

    return out;
}

void IOControl::saveRTree(RTree rtree, std::string fname) {
    std::ofstream ofs(fname);

    boost::archive::text_oarchive oa(ofs);
    oa << rtree;
}

RTree IOControl::getRTree(std::string fname) {
    RTree out;
    std::ifstream ifs(fname);
    if(!ifs) {
        saveRTree(out, fname);
        ifs = std::ifstream(fname);
    }

    boost::archive::text_iarchive ia(ifs);
    ia >> out;

    return out;
}


template <class Heuristic>
int IOControl::processInput(std::string fname) {
    std::ifstream infile(fname);
    RTreeController controller(FilenameGenerator::generateNewIndex());
    int index = 0;
    while (infile) {
        std::string s;
        if (!getline(infile, s)) break;
        std::istringstream ss(s);
        std::vector <std::string> record;
        int count = 0;
        float minX, maxX, minY, maxY;
        minX, minY = std::numeric_limits<float>::infinity();
        maxX, maxY = -std::numeric_limits<float>::infinity();
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
        Rectangle mbr(minX, maxX, minY, maxY, index, true);
        controller.insert<Heuristic>(mbr);
        index++;
    }
    if (!infile.eof()) {
        std::cerr << "Error during input file processing\n";
    }
    return controller.getRootFilenameIndex();
}




