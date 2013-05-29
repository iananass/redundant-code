/* 
 * File:   Combination.h
 * Author: matyzhonok
 *
 * Created on May 29, 2013, 12:19 AM
 */

#ifndef COMBINATION_H
#define	COMBINATION_H

#include <string>
#include <sstream>

template <int LEN>
class Combination {
public:
    Combination();
    Combination(const Combination&);
    Combination(char cmb[LEN]);
    const Combination operator=(const Combination&);
    const Combination operator+(const Combination&) const;

    std::string Print() const;
    char Count1() const;

private:
    char m_cmb[LEN];
};

template <int LEN>
Combination<LEN>::Combination() {
    for (int i = 0; i < LEN; ++i)
        m_cmb[i] = 0;
}

template <int LEN>
Combination<LEN>::Combination(const Combination& c) {
    for (int i = 0; i < LEN; ++i)
        m_cmb[i] = c.m_cmb[i];
}

template <int LEN>
Combination<LEN>::Combination(char cmb[LEN]) {
    for (int i = 0; i < LEN; ++i)
        m_cmb[i] = cmb[i];
}

template <int LEN>
        const Combination<LEN> Combination<LEN>::operator=(const Combination& c) {
    for (int i = 0; i < LEN; ++i)
        m_cmb[i] = c.m_cmb[i];
    return *this;
}

template <int LEN>
const Combination<LEN> Combination<LEN>::operator+(const Combination& c) const {
    Combination<LEN> tmp;
    for (int i = 0; i < LEN; ++i)
        tmp.m_cmb[i] = c.m_cmb[i] ^ m_cmb[i];
    return tmp;
}

template <int LEN>
std::string Combination<LEN>::Print() const {
    std::stringstream strm;
    for (int i = 0; i < LEN; ++i)
        strm << (int) m_cmb[i] << "  ";
    return strm.str();
}

template <int LEN>
Combination<LEN> Gen(int index, const Combination<LEN> base[]) {
    int i = 1;
    Combination<LEN> tmp;
    while (index && index < (1 << LEN)) {
     //   std::cout << "i  = " << i << std::endl;
        if (index & 1) {
            tmp = tmp + base[i];
    //        std::cout << base[i].Print() << "        " << tmp.Print() << std::endl;
        }
        ++i;
        index >>= 1;
    }
    return tmp;
}

template <int LEN>
char Combination<LEN>::Count1() const {
    char cnt = 0;
    for (int i = 0; i < LEN; ++i) {
        if (m_cmb[i] == 1)
            cnt += 1;
    }
    return cnt;
}
#endif	/* COMBINATION_H */