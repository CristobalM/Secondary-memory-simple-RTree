//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_RTREE_H
#define tarea1_logaritmos_RTREE_H


#include <vector>
#include "Rectangle.h"
#include "SplitHeuristic.h"

class RTree{
private:
    std::vector<Rectangle> node;

    SplitHeuristic splitHeuristic;
    std::string rootFilename;

public:

    RTree(SplitHeuristic &splitHeuristic, std::string rootFilename);

    std::vector<int> search(Rectangle &rectangle);

    std::vector<int> insert(Rectangle &rectangle);
};

#endif //tarea1_logaritmos_RTREE_H
