//
// Created by cristobal on 28-09-17.
//

#ifndef LOGARITMOS_TAREA1_IOCONTROL_H
#define LOGARITMOS_TAREA1_IOCONTROL_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "commontypes.h"
#include "RTree.h"
#include "SplitHeuristic.h"


class IOControl {
private:
    IOControl() = default;
public:


  static RTree getRTree(std::string fname);
  static void saveRTree(RTree rtree, std::string fname);

  static int processInput(std::string fname, SplitHeuristic *heuristic);

    //static void deleteFilename(std::string fname);


};


#endif //LOGARITMOS_TAREA1_IOCONTROL_H
