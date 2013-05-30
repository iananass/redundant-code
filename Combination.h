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

class Combination {
public:
    Combination();
    Combination(const Combination&);
    Combination(int len);
    Combination(char cmb[], int len);
    const Combination operator=(const Combination&);
    const Combination operator+(const Combination&) const;

    int Len() const;
    char Count1() const;

    friend std::ostream& operator<< (std::ostream& os, const Combination& cmb);int m_len;
private:
    char *m_cmb;
    
};

Combination::Combination()
: m_cmb(0)
, m_len(0) {
}

Combination::Combination(const Combination& c)
: m_cmb(new char[c.m_len])
, m_len(c.m_len) {
    for (int i = 0; i < m_len; ++i)
        m_cmb[i] = c.m_cmb[i];
}

Combination::Combination(int len)
: m_cmb(new char[len])
, m_len(len) {
    for (int i = 0; i < m_len; ++i)
        m_cmb[i] = 0;
}

Combination::Combination(char cmb[], int len)
: m_cmb(new char[len])
, m_len(len) {
    for (int i = 0; i < m_len; ++i)
        m_cmb[i] = cmb[i];
}

const Combination Combination::operator=(const Combination& c) {
    char* tmp = new char[c.m_len];
    m_len = c.m_len;
    delete m_cmb;
    m_cmb = tmp;
    for (int i = 0; i < m_len; ++i)
        m_cmb[i] = c.m_cmb[i];
    return *this;
}

const Combination Combination::operator+(const Combination& c) const {
    if (m_len != c.m_len)
        std::runtime_error("Combination::operator+.  Arguments dimentions are not equal");
    Combination tmp(c);
    for (int i = 0; i < m_len; ++i)
        tmp.m_cmb[i] ^= m_cmb[i];
    return tmp;
}

int Combination::Len() const {
    return m_len;
}

Combination Gen(int index, const Combination base[]) {
    int i = 0;
    Combination tmp(base[0].Len());
    while (index && index < (1 << base[0].Len())) {
        if (index & 1)
            tmp = tmp + base[i];
        ++i;
        index >>= 1;
    }
    return tmp;
}

char Combination::Count1() const {
    char cnt = 0;
    for (int i = 0; i < m_len; ++i) {
        if (m_cmb[i] == 1)
            cnt += 1;
    }
    return cnt;
}

std::ostream& operator<< (std::ostream& os, const Combination& cmb)
{
    for (int i = 0; i < cmb.m_len; ++i)
        os << (int) cmb.m_cmb[i] << "  ";
    return os;
}

void mod(char a[], int len_full, char b[], int len_gen, char c[]) {
    char tmp[len_full];
    for (int i = 0; i < len_full; ++i)
        tmp[i] = a[i];
    int i = 0;
    while (i < len_full - len_gen + 1) {
        if (tmp[i] == 1) {
            for (int j = 0; j < len_gen; ++j) {
                tmp[i + j] ^= b[j];
            }
        }
        ++i;
    }
    for (int j = 0; j < (len_gen - 1); ++j)
        c[j] = tmp[i + j];
}

Combination MakeCombinations(int index, int len_full, char generator[], int len_gen) {
    char tmp[len_full];
    for (int i = 0; i < len_full; ++i)
        tmp[i] = 0;
    tmp[index] = 1;
    char c[len_gen - 1];

    mod(tmp, len_full, generator, len_gen, c);

    for (int i = 0; i < (len_gen - 1); ++i)
        tmp[len_full - len_gen + 1 + i] = c[i];

    return Combination (tmp, len_full);
}
#endif	/* COMBINATION_H */