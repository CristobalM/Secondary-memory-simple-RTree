//
// Created by cristobal on 06-10-17.
//

#ifndef LOGARITMOS_TAREA1_EXPERIMENTDATA_H
#define LOGARITMOS_TAREA1_EXPERIMENTDATA_H

#include <string>
#include <chrono>
#include <iostream>

typedef std::chrono::high_resolution_clock hires;

struct ExperimentData{
  std::string experimentName;
  std::chrono::time_point<hires> startTime, endTime;

  static long castNanoSeconds( std::chrono::duration<long> &which){
      return std::chrono::duration_cast<std::chrono::nanoseconds>(which).count();
  }
  long retrieveTimeElapsedNanoSeconds(){
      return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime -startTime).count();
  }
};


#endif //LOGARITMOS_TAREA1_EXPERIMENTDATA_H
