//
// Created by Cristobal M on 9/26/17.
//

#ifndef tarea1_logaritmos_LINEARSPLIT_H
#define tarea1_logaritmos_LINEARSPLIT_H


#include "SplitHeuristic.h"

class LinearSplit : SplitHeuristic {
    std::pair<vRect, vRect> split(vRect &, std::string, int) override ;
};



#endif //tarea1_logaritmos_LINEARSPLIT_H
