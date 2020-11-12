#include <iostream>
#include <fstream>
#include "henger.hpp"
#include <vector>
#include "how_deep.hpp"




int main() {
    std::ifstream  _infile;
    std::vector<coordinat> c;
    float x,y,z;
    float xcam = 0, ycam = 0, zcam =0;
    _infile.open("../keppont.txt");
//
//
//
//

if(!(_infile.good())){
    std::cout<< "Unable to open keppont.txt"<< std::endl;
    return 0;
}
    while(_infile.good()){
        _infile >> x >> y >> z;
        c.push_back(henger(x,y,z,xcam,ycam,zcam));
}
_infile.close();
    /*
     *
     *
     *
     */
how_deep *proba  = new how_deep(c,60,300,0,10);
proba->divide();



delete proba;
    return 0;
}