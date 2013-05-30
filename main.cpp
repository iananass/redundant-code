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
#include "Combination.h"
// generator = {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

const char* strToGenerator(const char* str)
{
    char* generator = new char[strlen(str)];
    int i = 0;
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

int GetUndetectedErrorsNumber(const std::vector<Combination>& all_combinations, int repetition)
{
    int errors_number = 0;
    for (int i = 0; i < all_combinations.size(); ++i)
        for (int j = i + 1; j < all_combinations.size(); ++j)
            if ((all_combinations[i] + all_combinations[j]).Count1() == repetition) {
                ++errors_number;
              //  std::cout << repetition << ":  " << i << "+" << j << "= [ " << (all_combinations[i] + all_combinations[j]) << "]" << std::endl;
            }
    return errors_number;
}

long factorial(int n)
{
    long fact = 1;
    for (int i = 1; i <= n; ++i)
        fact *= i;
    return fact;
}

int combinationsNumber(int selection_size, int total_count)
{
    return factorial(total_count) / (factorial(selection_size) * factorial(total_count - selection_size));
}

int main(int argc, char** argv)
{
    int Combination_len;
    int Generator_len;
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

    int Information_len = Combination_len - Generator_len + 1;
    int Combinations_num = 1 << (Information_len);

    Combination base[Information_len];

    for (int i = 0; i < Information_len; ++i) {
        base[i] = MakeBaseCombination(Information_len - i - 1, Combination_len, generator, Generator_len);
        std::cout << "base[" << i + 1 << "] = " << base[i] << std::endl;
    }

    std::vector <Combination> all_combinations;
    all_combinations.reserve(Combinations_num + 1);
    for (int i = 0; i < Combinations_num; ++i)
        all_combinations.push_back(GenerateComplexCombination(i, base));
    
    
    for (int i = 1; i <= Combination_len; ++i) {
        int undetected_errors = GetUndetectedErrorsNumber(all_combinations, i);
        std::cout << undetected_errors << std::endl;
    }
    
    return 0;
}
