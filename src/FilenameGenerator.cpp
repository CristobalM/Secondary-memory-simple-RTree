//
// Created by Cristobal M on 10/4/17.
//

#include <string>
#include "FilenameGenerator.h"
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

int FilenameGenerator::index = -1;
boost::uuids::random_generator FilenameGenerator::uuidgenerator;

int FilenameGenerator::generateNewIndex() {
  FilenameGenerator::index++;
  return FilenameGenerator::index;
}

/*
std::string FilenameGenerator::getStringFromIndex(int index) {
  return "rtree" + std::to_string(index) + ".txt";
}
 */


std::string FilenameGenerator::getStringFromIndex(int index, std::string prefix) {
  return prefix + "_rtree" + std::to_string(index) + ".txt";
}

std::string FilenameGenerator::makeUuid() {
  return boost::uuids::to_string(uuidgenerator());
}


