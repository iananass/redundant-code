/* 
 * File:   main.cpp
 * Author: matyzhonok
 *
 * Created on May 29, 2013, 12:19 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string.h>
#include <string>
#include <iomanip>
#include "Combination.h"
// generator = {10001000000100001};

const char* strToGenerator(const char* str) {
    char* generator = new char[strlen(str)];
    u_int64_t i = 0;
    while (*str) {
        if (*str != '0')
            generator[i] = 1;
        else
            generator[i] = 0;
        ++i;
        ++str;
    }
    return generator;
}

u_int64_t factorial(u_int64_t n) {
    u_int64_t fact = 1;
    for (u_int64_t i = 1; i <= n; ++i)
        fact *= i;
    return fact;
}

u_int64_t combinationsNumber(u_int64_t selection_size, u_int64_t total_count) {
    if (selection_size > (total_count - selection_size))
        selection_size = (total_count - selection_size);
    
    u_int64_t numerator = 1;
    for (int i = 0; i < selection_size; ++i) {
        numerator *= total_count;
        --total_count;
    }
    return (numerator / factorial(selection_size));
}

int main(int argc, char** argv) {
    u_int64_t Combination_len;
    u_int64_t Generator_len;
    const char* generator;

    if (argc == 3) {
        Combination_len = atoi(argv[1]);
        Generator_len = strlen(argv[2]);
        generator = strToGenerator(argv[2]);
    } else {
        std::cout << "Please enter total code length:    ";
        std::cin >> Combination_len;
        std::string raw_generator;
        std::cout << "Please enter generator polynomial: ";
        std::cin >> raw_generator;
        Generator_len = raw_generator.size();
        generator = strToGenerator(raw_generator.c_str());
    }

    u_int64_t Information_len = Combination_len - Generator_len + 1;
    u_int64_t Combinations_num = 1 << (Information_len);

    Combination base[Information_len];

    for (u_int64_t i = 0; i < Information_len; ++i) {
        base[i] = MakeBaseCombination(Information_len - i - 1, Combination_len, generator, Generator_len);
        //std::cout << "base[" << i + 1 << "] = " << base[i] << std::endl;
    }


    u_int64_t combinationWeightCounter[Combination_len];
    for (int i = 0; i < Combination_len; ++i)
        combinationWeightCounter[i] = 0;

    for (u_int64_t i = 0; i < Combinations_num; ++i)
        ++combinationWeightCounter[GenerateComplexCombination(i, base).Count1() - 1];


    std::cout << std::setw(30) << "errCount" << std::setw(30) << "Undetected Errors Count" << std::setw(30) << "Total Errors Count" << std::setw(50) << "Ptobability" << std::endl;

    for (u_int64_t i = 1; i <= Combination_len; ++i) {
        u_int64_t undetected_errors = combinationWeightCounter[i -1];
        u_int64_t total_possibly_errors = combinationsNumber(i, Combination_len);
        std::cout << std::sнеetw(30) << i << std::setw(30) << undetected_errors << std::setw(30) << total_possibly_errors << std::setw(50) << float(undetected_errors) / total_possibly_errors  << std::endl;
    }

    return 0;
}
