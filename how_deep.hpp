//
// Created by Szamosi Andris on 2019. 11. 12..
//

#ifndef INC_3_NAGYHF_HOW_DEEP_HPP
#define INC_3_NAGYHF_HOW_DEEP_HPP

#include <vector>


struct coordinat{
    float    _phi,_theta,r;
};


class how_deep {
private:
int high, length,sen_pos, pixel_neigh;
    std::vector<coordinat> &c;
    int** _tomb;

public:
     how_deep(std::vector<coordinat> &_c, int _high, int _length, int _sen_pos, int _pixel_neigh);
     ~how_deep();
    void divide();
    void  interpolar();

};



#endif //INC_3_NAGYHF_HOW_DEEP_HPP
