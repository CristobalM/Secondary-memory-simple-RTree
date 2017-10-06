//
// Created by cristobal on 06-10-17.
//

#ifndef LOGARITMOS_TAREA1_EXPERIMENTS_H
#define LOGARITMOS_TAREA1_EXPERIMENTS_H

#include <string>
#include <vector>
#include <chrono>
#include "ExperimentData.h"
#include "RTreeController.h"


class Experiments {
  static ExperimentData lastExperiment;
public:
  static void startExperiment(std::string name);
  static ExperimentData& stopExperiment();
  static long averageRectanglesPerNode(RTreeController &controller);
  static long averageRectanglesPerNodeRec(RTreeController &controller, int* nptr);




};


#endif //LOGARITMOS_TAREA1_EXPERIMENTS_H
