//
// Created by cristobal on 28-09-17.
//

#include <fstream>
#include <boost/serialization/vector.hpp>
#include "IOControl.h"

void IOControl::saveVRect(vRect vrect, std::string fname) {
    std::ofstream ofs(fname);

    boost::archive::text_oarchive oa(ofs);
    oa << vrect;
}

vRect IOControl::getVRect(std::string fname) {
    vRect out;
    std::ifstream ifs(fname);

    boost::archive::text_iarchive ia(ifs);
    ia >> out;

    return out;
}




