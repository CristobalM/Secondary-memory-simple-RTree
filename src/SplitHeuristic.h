//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_SPLITHEURISTIC_H
#define tarea1_logaritmos_SPLITHEURISTIC_H


#include "RTree.h"

class SplitHeuristic {
public:
    virtual void split(RTree &rTree) = 0;
};


#endif //tarea1_logaritmos_SPLITHEURISTIC_H
