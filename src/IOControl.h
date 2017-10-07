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

  static std::shared_ptr<RTree> getRTree(int indexRtree, std::string controllerPrefix, CachingRTree &cache);
  static void saveRTree(std::shared_ptr<RTree> rtree, int indexRtree, std::string controllerPrefix, CachingRTree &cache);

  static RTreeController processInput(std::string fname, SplitHeuristic *heuristic);

  static void checkCache(std::string controllerPrefix, CachingRTree &cache, bool forceClean = false, bool saveFiles = false);

  static void cleanControllerData(std::string controllerPrefix);


  static long fileSpace(std::string filename);
  static long spaceOccupied(std::string controllerPrefix);




};


#endif //LOGARITMOS_TAREA1_IOCONTROL_H
