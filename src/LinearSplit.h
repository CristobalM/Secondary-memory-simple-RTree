//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_LINEARSPLIT_H
#define tarea1_logaritmos_LINEARSPLIT_H


#include "SplitHeuristic.h"

class LinearSplit : SplitHeuristic {
    splittedNode split(vRect &vrect, std::string parentFilename, int parentRectangleIndex) override ;
};



#endif //tarea1_logaritmos_LINEARSPLIT_H
