//
// Created by Cristobal M on 10/4/17.
//

#ifndef LOGARITMOS_TAREA1_FILENAMEGENERATOR_H
#define LOGARITMOS_TAREA1_FILENAMEGENERATOR_H

#include <string>
#include <boost/uuid/random_generator.hpp>

class FilenameGenerator {
private:
  static int index;
  static boost::uuids::random_generator uuidgenerator;

public:
  static int generateNewIndex();
  //static std::string getStringFromIndex(int index);
  static std::string makeUuid();

  static std::string getStringFromIndex(int index, std::string prefix);
};


#endif //LOGARITMOS_TAREA1_FILENAMEGENERATOR_H
