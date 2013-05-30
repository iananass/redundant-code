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
const int Generator_len = Combination_len - Information_len + 1;
char generator[Generator_len] = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

int main(int argc, char** argv) {
    Combination base[Information_len];

    for (int i = 0; i < Information_len; ++i) {
        base[i] = MakeCombinations(Information_len - i -1, Combination_len , generator,Generator_len);
    }

    std::vector <Combination> all_combinations;
    all_combinations.reserve(Combinations_num);
    for (int i = 0; i < Combinations_num; ++i) {
        Combination tmp(Gen(i, base));
        all_combinations.push_back(tmp);
    }

    for (int i = 1; i < Combinations_num; ++i)
        for (int j = i + 1; j < Combinations_num; ++j)
            if ((all_combinations[i] + all_combinations[j]).Count1() == 6) {
                std::cout << i << "+" << j << "=" << (all_combinations[i] + all_combinations[j]) << std::endl;
            }


    return 0;
}
