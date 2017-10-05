//
// Created by Cristobal M on 10/4/17.
//

#include <string>
#include "FilenameGenerator.h"

int FilenameGenerator::generateNewIndex() {
  return index++;
}

std::string FilenameGenerator::getStringFromIndex(int index) {
  return "rtree" + std::to_string(index) + ".txt";
}

