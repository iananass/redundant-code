/* 
 * File:   main.cpp
 * Author: matyzhonok
 *
 * Created on May 29, 2013, 12:19 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Combination.h"


/*
 * 
 */
const int Combination_len = 28;
const int Information_len = 12;
const int Combinations_num = 1 << (Information_len);

int main(int argc, char** argv) {

    char baseLines[Information_len + 1][Combination_len] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1}
    };


    Combination<Combination_len> base[Information_len + 1];

    for (int i = 0; i < Information_len + 1; ++i) {
        base[i] = Combination<Combination_len > (baseLines[i]);
    }


//    std::cout << Gen(2048, base).Print();
//    return 0;

    std::vector <Combination<Combination_len> > all_combinations;
    all_combinations.reserve(Combinations_num);
    for (int i = 0; i < Combinations_num; ++i) {
        Combination<Combination_len> tmp(Gen(i, base));
        all_combinations.push_back(tmp);
   //     std::cout << i << "= " << tmp.Print() << std::endl;
    }

    for (int i = 1; i < Combinations_num; ++i)
        for (int j = i + 1; j < Combinations_num; ++j)
            if ((all_combinations[i] + all_combinations[j]).Count1() == 4) {
                std::cout << i << "+" << j << "=" << (all_combinations[i] + all_combinations[j]).Print() << std::endl;
//                std::cout << all_combinations[i].Print() << std::endl;
//                std::cout << all_combinations[j].Print() << std::endl;
                break;
            }


    return 0;
}

