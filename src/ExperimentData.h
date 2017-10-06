//
// Created by cristobal on 06-10-17.
//

#ifndef LOGARITMOS_TAREA1_EXPERIMENTDATA_H
#define LOGARITMOS_TAREA1_EXPERIMENTDATA_H

#include <string>
#include <chrono>
#include <iostream>

struct ExperimentData{
  std::string experimentName;
  std::chrono::time_point startTime, endTime;
  std::chrono::duration timeElapsed;

  void printExperiment(){
      std::cout << "Experiment " << experimentName << "." << std::endl
                << "\tTime elapsed (nanoseconds): " << std::chrono::duration_cast<std::chrono::nanoseconds>(timeElapsed).count() << "." << std::endl;
  }
};

#endif //LOGARITMOS_TAREA1_EXPERIMENTDATA_H
