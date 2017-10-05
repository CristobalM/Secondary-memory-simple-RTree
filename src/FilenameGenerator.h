//
// Created by Cristobal M on 10/4/17.
//

#ifndef LOGARITMOS_TAREA1_FILENAMEGENERATOR_H
#define LOGARITMOS_TAREA1_FILENAMEGENERATOR_H

#include <string>

class FilenameGenerator {
private:
  static int index;
public:
  static std::string generateNewFilename();
  static std::string getStringFromIndex(int index);

};

int FilenameGenerator::index = 0;

#endif //LOGARITMOS_TAREA1_FILENAMEGENERATOR_H
