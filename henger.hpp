//
// Created by Szamosi Andris on 2019. 11. 12..
//

#ifndef INC_3_NAGYHF_HENGER_HPP
#define INC_3_NAGYHF_HENGER_HPP

#include <cmath>
#include "how_deep.hpp"
/*
 *
 *  igazából gömbi koordináta
 *
 */
coordinat henger(float &x,float &y,float &z,float &xcam,float &ycam,float &zcam){
    coordinat _co;
    _co.r = sqrt((x +xcam)*(x +xcam) + (y + ycam)*(y + ycam) + (z +zcam)*(z +zcam));

     if(x > 0) {
       _co._phi = atan((y + ycam) / (x +xcam));
   }
   else if((x +xcam) < 0){
       _co._phi = atan((y + ycam) / (x +xcam)) + M_PI;

   }else if((y + ycam) > 0){
        _co._phi = M_PI / 2;

    }else  {
        _co._phi = -1 * M_PI / 2;

    }
    _co._theta = acos((z +zcam)/_co.r);

    return _co;
}


#endif //INC_3_NAGYHF_HENGER_HPP
