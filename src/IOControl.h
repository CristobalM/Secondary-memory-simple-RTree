//
// Created by cristobal on 28-09-17.
//

#ifndef LOGARITMOS_TAREA1_IOCONTROL_H
#define LOGARITMOS_TAREA1_IOCONTROL_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "commontypes.h"
#include "RTree.h"

class IOControl {
private:
    IOControl() = default;
public:
    static void saveVRect(vRect vrect, std::string fname);
    static vRect getVRect(std::string fname);
    static void saveRTree(RTree vrect, std::string fname);
    static RTree getRTree(std::string fname);

};


#endif //LOGARITMOS_TAREA1_IOCONTROL_H
