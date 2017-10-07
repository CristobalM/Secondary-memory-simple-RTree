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
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string/predicate.hpp>

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

void IOControl::saveRTree(std::shared_ptr<RTree> rtree, int indexRtree ,std::string controllerPrefix, CachingRTree &Cached) {
    Cached[FilenameGenerator::getStringFromIndex(indexRtree, controllerPrefix)] = rtree;
    estimatedCachedSize += rtree->node.size();
    checkCache(controllerPrefix, Cached);
}

std::shared_ptr<RTree> IOControl::getRTree(int indexRtree, std::string controllerPrefix, CachingRTree &Cached) {
    std::string fname = FilenameGenerator::getStringFromIndex(indexRtree, controllerPrefix);
    if(Cached.find(fname) != Cached.end()){
        return Cached[fname];
    }
    std::shared_ptr<RTree> out(new RTree(indexRtree));
    std::ifstream ifs(fname);
    if(!ifs) {
        out->inputFilenameIndex = indexRtree;
        Cached[fname] = out;
        return out;
    }

    boost::archive::text_iarchive ia(ifs);
    ia >> *out;

    Cached[fname] = out;
    estimatedCachedSize += out->node.size();

    checkCache(controllerPrefix, Cached);
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
        Rectangle mbr(minX, maxX, minY, maxY, index);
        controller.insert(mbr);
        index++;
    }
    if (!infile.eof()) {
        std::cerr << "Error during input file processing\n";
    }
    saveRTree(controller.currentNode,
              controller.getRootFilenameIndex(),
              controller.getControllerPrefix(),
              controller.Cached);
    return controller;
}

void IOControl::checkCache(std::string  controllerPrefix, CachingRTree &Cached, bool forceClean, bool saveFiles) {
    unsigned int cachedMaxSize = (unsigned int) Cached.max_size();
    unsigned int maxSz = DEFAULT_MAX_MEM_SIZE > cachedMaxSize ? cachedMaxSize : DEFAULT_MAX_MEM_SIZE;
    if(estimatedCachedSize > maxSz || forceClean){
        for(auto it = Cached.begin(); it != Cached.end(); it++){
            std::shared_ptr<RTree>current;
            current = it->second;
            if(saveFiles || !forceClean) {
                std::ofstream ofs(FilenameGenerator::getStringFromIndex(current->inputFilenameIndex, controllerPrefix));
                boost::archive::text_oarchive oa(ofs);
                oa << *current;
            }
        }

        Cached.clear();
        estimatedCachedSize = 0;
    }
}



long IOControl::spaceOccupied(std::string controllerPrefix) {
    boost::filesystem::path p(".");
    boost::filesystem::directory_iterator end_itr;

    long total = 0;

    for(boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr){
        if(boost::filesystem::is_regular_file(itr->path())){
            std::string current_file = itr->path().string();
            if(boost::starts_with(current_file, "./"+controllerPrefix)){
                total += boost::filesystem::file_size(itr->path());
            }
        }
    }
    return total;
}




