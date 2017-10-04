//
// Created by Cristobal M on 10/4/17.
//

#ifndef LOGARITMOS_TAREA1_FILENAMEGENERATOR_H
#define LOGARITMOS_TAREA1_FILENAMEGENERATOR_H

#include <string>

class FilenameGenerator {
private:
  static int index = 0;
public:
  static std::string generateNewFilename();
  static std::string getStringFromIndex(int index);

};

#endif //LOGARITMOS_TAREA1_FILENAMEGENERATOR_H
