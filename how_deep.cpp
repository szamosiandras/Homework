//
// Created by Szamosi Andris on 2019. 11. 12..
//

#include "how_deep.hpp"
#include <iostream>
#include <cmath>
#include <fstream>
how_deep::how_deep(std::vector<coordinat> &_c,int _high, int _length, int _sen_pos, int _pixel_neigh): c(_c), high(_high), length(_length), sen_pos(_sen_pos), pixel_neigh(_pixel_neigh){
    _tomb = new int*[high];
    for (int i = 0; i <high ; ++i) {
        _tomb[i] = new int[length];
    }

    for(int i = 0; i < high; i++) {
        for (int j = 0; j < length; ++j) {
            _tomb[i][j] = 0;
        }
    }
}

void how_deep::divide() {
    float _num = 0, _hi = 0, _le = 0, _min_le = 360, _min_hi = 360;

                                                                    //
    for(unsigned int i = 0; i < c.size(); i++){                     // Átskálázások az adott tartományba,
    c[i].r = abs((int)(c[i].r - sen_pos));                      // és legnagyobb értékek megkeresése
        if(_num < c[i].r){                                          //
        _num = c[i].r;
    }

    if(_hi < c[i]._theta){
        _hi = c[i]._theta;
    }else  if(_min_hi > c[i]._theta){
        _min_hi = c[i]._theta;
    }

    c[i]._phi = c[i]._phi * 180/ M_PI;
    if(c[i]._phi < 0){
        c[i]._phi = 360 +  c[i]._phi;
    }

    if(_le < c[i]._phi){
        _le = c[i]._phi;
    }else if(_min_le > c[i]._phi){
        _min_le = c[i]._phi;
    }


}

    _min_hi = _min_hi *   180/ M_PI;
    _hi = _hi *   180/ M_PI;

    for(int i = 0; i < c.size(); i++){
            c[i].r = round( c[i].r /_num * 255);
           c[i]._theta = round(((c[i]._theta * 180/ M_PI - _min_hi)/(_hi-_min_hi+1)*high))+1;
           c[i]._phi = round(c[i]._phi/_le*length) ;
    }
/*
 *
 *
 *
 * _tömb feltöltése a mélységek értékeivel (0-255)
 *
 *
 *
 */

    for (unsigned int i = 0; i < c.size() ; ++i) {
        if(_tomb[(int)c[i]._theta-1][(int)c[i]._phi-1] == 0){
            _tomb[(int)c[i]._theta-1][(int)c[i]._phi-1] =255- c[i].r;
        } else{
            if(_tomb[(int)c[i]._theta-1][(int)c[i]._phi-1] > c[i].r){
                _tomb[(int)c[i]._theta-1][(int)c[i]._phi-1] =255 - c[i].r;
            }
        }

    }
    /*
     *
     * aredmények kiírás fileba (x,y)és hozzájuk tartozó érték (results.txt)
     * képmegjelenítés (original_result.pmg)
     *
     */
    std::ofstream _outfile, proba;
    _outfile.open("../original_result.pgm");
    proba.open("../results.txt");
    for(unsigned int i = 0; i < c.size(); i++){
        proba << c[i].r <<"  "<<c[i]._phi<< "  "<< c[i]._theta<<std::endl;
    }

    _outfile<< "P2"<<std::endl << length<< ' '<<high<<std::endl<<"255"<<std::endl;
    for(int i = 0; i < high; i++){
        for (int j = 0; j < length ; ++j) {
            _outfile << _tomb[i][j]<< " ";
        }
        _outfile<< std::endl;
    }

    _outfile.close();
    proba.close();



interpolar();


}



void how_deep::  interpolar(){
    std::ofstream _outfile_;
    int p_n = pixel_neigh;

    _outfile_.open("../interpolar_result.pgm");
    int teszt_i  =0;
    _outfile_<< "P2"<<std::endl << length<< ' '<<high <<std::endl<<"255"<<std::endl;
    for (int i =  0; i < high ; ++i) {
        int teszt_j = 0;
        for (int j = 0; j < length ; ++j) {
            int _index = 0, _summ = 0;

            if (((i  >=  p_n && j   >= p_n) && (high - p_n > i + p_n && length - p_n > j + p_n)) &&
                _tomb[i][j] == 0) {
                for (int q = i-p_n; q <= i + p_n; q++) {
                    for (int w = j - p_n; w <= j + p_n; w++) {
                        if (q != i || w != j) {
                            _summ += _tomb[q][w];
                            _index += 1;
                        }
                    }

                }
                teszt_j ++;
                if(_index == 0){
                    _outfile_<<"0 ";
                }else
                    _outfile_ << (int) round(_summ / _index) << " ";
            } else if (!((i  >=  p_n && j   >= p_n) && (high - p_n > i + p_n && length - p_n > j + p_n)) &&
                       _tomb[i][j] == 0){

                if(i + p_n >= i && 0 + p_n >= j && high - p_n > i + p_n && length - p_n > j + p_n)  { //balfelsösarok
                    for (int q = 0; q < i + p_n+1; q++) {
                        for (int w = 0; w < j+  p_n; w++) {
                            if (q != i || w != j) {
                                _summ += _tomb[q][w];
                                _index += 1;
                            }
                        }
                    }
                    teszt_j ++;
                    if(_index == 0){
                        _outfile_<<"0 ";
                    }else
                        _outfile_ << (int) round(_summ / _index) << " ";
                }else if(i + p_n + p_n < i && 0 + p_n >= j && high - p_n > i + p_n && length - p_n > j + p_n)  { //balszél
                    for (int q = i + p_n + p_n; q < i  + p_n+1; q++) {
                        for (int w = 0; w < j + p_n; w++) {
                            if (q != i || w != j) {
                                _summ += _tomb[q][w];
                                _index += 1;
                            }
                        }
                    }
                    teszt_j ++;
                    if(_index == 0){
                        _outfile_<<"0 ";
                    }else
                        _outfile_ << (int) round(_summ / _index) << " ";
                }else if(i + p_n >= i && 0 + p_n < j && high - p_n > i + p_n && length - p_n > j + p_n){ //felsöszél
                    for (int q = 0; q < i + p_n; q++) {
                        for (int w = j - p_n; w < j + p_n; w++) {
                            if (q != i || w != j) {
                                _summ += _tomb[q][w];
                                _index += 1;
                            }
                        }
                    }
                    teszt_j ++;
                    if(_index == 0){
                        _outfile_<<"0 ";
                    }else
                        _outfile_ << (int) round(_summ / _index) << " ";
                }else if((i  >=  p_n && j   <= p_n) && (high - p_n <= i + p_n && length - p_n > j + p_n))  { // balalsosarok
                    for (int q = i - p_n; q < i ; q++) {
                        for (int w = 0; w < j +p_n; w++) {
                            if (q != i || w != j) {
                                _summ += _tomb[q][w];
                                _index += 1;
                            }
                        }
                    }
                    teszt_j ++;
                    if(_index == 0){
                        _outfile_<<"0 ";
                    }else
                        _outfile_ << (int) round(_summ / _index) << " ";
                }else if((i  >=  p_n && j   >= p_n) && (high - p_n <= i + p_n && length - p_n <= j + p_n))  { //jobbalsosarok
                    for (int q = i - p_n; q < i; q++) {
                        for (int w = j - p_n; w < j ; w++) {
                            if (q != i || w != j) {
                                _summ += _tomb[q][w];
                                _index += 1;
                            }
                        }
                    }
                    teszt_j ++;
                    if(_index == 0){
                        _outfile_<<"0 ";
                    }else
                        _outfile_ << (int) round(_summ / _index) << " ";
                }else if((i  >=  p_n && j   >= p_n) && (high - p_n <= i + p_n && length - p_n > j + p_n)){ //alsoszél
                    for (int q = i - p_n ; q < i ; q++) {
                        for (int w = j - p_n; w < j + p_n; w++) {
                            if (q != i || w != j) {
                                _summ += _tomb[q][w];
                                _index += 1;
                            }
                        }
                    }
                    teszt_j ++;
                    if(_index == 0){
                        _outfile_<<"0 ";
                    }else
                        _outfile_ << (int) round(_summ / _index) << " ";

                }else if( i + p_n < i && 0 + p_n < j && high - p_n > i + p_n && length - p_n <= j + p_n){ //jobbszél
                    for (int q = i - p_n; q < i + p_n; q++) {
                        for (int w = j - p_n; w < j ; w++) {
                            if (q != i || w != j) {
                                _summ += _tomb[q][w];
                                _index += 1;
                            }
                        }
                    }
                    teszt_j ++;
                    if(_index == 0){
                        _outfile_<<"0 ";
                    }else
                        _outfile_ << (int) round(_summ / _index) << " ";
                }else if( i + p_n >= i && 0 + p_n < j && high - p_n > i + p_n && length - p_n <= j + p_n){ //jobbfelsösarok
                    for (int q = 0; q < i + p_n; q++) {
                        for (int w = j - p_n; w < j ; w++) {
                            if (q != i || w != j) {
                                _summ += _tomb[q][w];
                                _index += 1;
                            }
                        }
                    }
                    teszt_j ++;
                    if(_index == 0){
                        _outfile_<<"0 ";
                    }else
                        _outfile_ << (int) round(_summ / _index) << " ";
                }
                else{
                    _outfile_<< "0"<< " ";
                }
            }else{
                teszt_j ++;
                _outfile_<< _tomb[i][j] << " ";
            }
        }
        if(teszt_j != length){
        }

        teszt_i ++;

        _outfile_<< std::endl;

    }

    _outfile_.close();

}

how_deep::~how_deep() {
    delete[] _tomb[0];
    _tomb[0] = nullptr;
    delete[] _tomb;
    _tomb = nullptr;

}


