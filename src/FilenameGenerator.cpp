//
// Created by Cristobal M on 10/4/17.
//

#include <string>
#include "FilenameGenerator.h"

std::string FilenameGenerator::generateNewFilename() {
  return "rtree" + std::to_string(index++) + ".txt";
}

std::string FilenameGenerator::getStringFromIndex(int index) {
  return "rtree" + std::to_string(index) + ".txt";
}

