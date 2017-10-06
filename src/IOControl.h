//
// Created by cristobal on 28-09-17.
//

#ifndef LOGARITMOS_TAREA1_IOCONTROL_H
#define LOGARITMOS_TAREA1_IOCONTROL_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <unordered_map>
#include "commontypes.h"
#include "RTree.h"
#include "SplitHeuristic.h"
#include "RTreeController.h"


class IOControl {
private:
  IOControl() = default;
  static int estimatedCachedSize;
public:

  static std::unordered_map<std::string, RTree> Cached;

  static RTree getRTree(int indexRtree, std::string controllerPrefix);
  static void saveRTree(RTree rtree, int indexRtree, std::string controllerPrefix);

  static RTreeController processInput(std::string fname, SplitHeuristic *heuristic);

  static void checkCache(std::string controllerPrefix, bool forceClean = false);

  static void cleanControllerData(std::string controllerPrefix);


  static long fileSpace(std::string filename);
  static long spaceOccupied(std::string controllerPrefix);

  static void cleanCache();


};


#endif //LOGARITMOS_TAREA1_IOCONTROL_H
