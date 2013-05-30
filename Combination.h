/* 
 * File:   Combination.h
 * Author: matyzhonok
 *
 * Created on May 29, 2013, 12:19 AM
 */

#ifndef COMBINATION_H
#define	COMBINATION_H

#include <ostream>
#include <stdexcept>

class Combination
{
public:
    Combination();
    Combination(const Combination&);
    Combination(int len);
    Combination(const char cmb[], int len);
    ~Combination();
    const Combination operator=(const Combination&);
    const Combination operator+(const Combination&) const;

    int Len() const;
    char Count1() const;

    friend std::ostream& operator<<(std::ostream& os, const Combination& cmb);
    int m_len;
private:
    char *m_cmb;
};

Combination GenerateComplexCombination(int index, const Combination base[]);
Combination MakeBaseCombination(int index, int len_full, const char generator[], int len_gen);
#endif	/* COMBINATION_H */