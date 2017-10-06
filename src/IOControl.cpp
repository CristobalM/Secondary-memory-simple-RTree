//
// Created by cristobal on 28-09-17.
//

#include <fstream>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <sstream>
#include "IOControl.h"
#include "RTree.h"
#include "RTreeController.h"
#include "FilenameGenerator.h"
#include <iostream>

int IOControl::estimatedCachedSize = 0;

std::streampos fileSize( const char* filePath ){

    std::streampos fsize = 0;
    std::ifstream file( filePath, std::ios::binary );

    fsize = file.tellg();
    file.seekg( 0, std::ios::end );
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}

void IOControl::saveRTree(RTree rtree, std::string fname) {
    std::ofstream ofs(fname);



    boost::archive::binary_oarchive oa(ofs);
    oa << rtree;
    Cached[fname] = rtree;
    estimatedCachedSize += rtree.node.size();
    checkCache();
}

RTree IOControl::getRTree(std::string fname) {
    if(Cached.find(fname) != Cached.end()){
        return Cached[fname];
    }
    RTree out = RTree();
    std::ifstream ifs(fname);
    if(!ifs) {
        return out;
    }

    boost::archive::binary_iarchive ia(ifs);
    ia >> out;

    Cached[fname] = out;
    checkCache();
    return out;
}


RTreeController IOControl::processInput(std::string fname, SplitHeuristic *heuristic) {
    std::ifstream infile(fname);
    RTreeController controller(FilenameGenerator::generateNewIndex(), heuristic);
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
        Rectangle mbr(minX, maxX, minY, maxY, index, true);
        controller.insert(mbr);
        index++;
    }
    if (!infile.eof()) {
        std::cerr << "Error during input file processing\n";
    }
    return controller;
}

void IOControl::checkCache() {
    if(estimatedCachedSize > DEFAULT_MAX_MEM_SIZE){
        Cached.clear();
        estimatedCachedSize = 0;
    }
}




