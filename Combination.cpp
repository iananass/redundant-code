#include "Combination.h"
#include <iostream>

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

Combination::Combination(const char cmb[], int len)
: m_cmb(new char[len])
, m_len(len) {
    for (int i = 0; i < m_len; ++i)
        m_cmb[i] = cmb[i];
}

Combination::~Combination() {
    delete m_cmb;
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

int Combination::Count1() const {
    int cnt = 0;
    for (int i = 0; i < m_len; ++i) {
        if (m_cmb[i] == 1)
            cnt += 1;
    }
    return cnt;
}

Combination GenerateComplexCombination(long index, const Combination base[]) {
    long i = 0;
 //   std::cout << " i = " << index << std::endl;
    Combination tmp(base[0].Len());
    while (index ){
        if (index & 1) {
            tmp = tmp + base[i];
     //       std::cout << "  +  " << base[i] << std::endl;
        }
        ++i;
        index >>= 1;
    }
   // std::cout << tmp << std::endl;
    return tmp;
}

std::ostream& operator<<(std::ostream& os, const Combination& cmb) {
    for (int i = 0; i < cmb.m_len; ++i)
        os << (int) cmb.m_cmb[i] << "  ";
    return os;
}

static void mod(const char combination[], int len_full, const char generator[], int len_gen, char c[]) {
    char tmp_combination[len_full];
    for (int i = 0; i < len_full; ++i)
        tmp_combination[i] = combination[i];
    int i = 0;
    while (i < len_full - len_gen + 1) {
        if (tmp_combination[i] == 1) {
            for (int j = 0; j < len_gen; ++j) {
                tmp_combination[i + j] ^= generator[j];
            }
        }
        ++i;
    }
    for (int j = 0; j < (len_gen - 1); ++j)
        c[j] = tmp_combination[i + j];
}

Combination MakeBaseCombination(int index, int len_full, const char generator[], int len_gen) {
    char tmp[len_full];
    for (int i = 0; i < len_full; ++i)
        tmp[i] = 0;
    tmp[index] = 1;
    char c[len_gen - 1];

    mod(tmp, len_full, generator, len_gen, c);

    for (int i = 0; i < (len_gen - 1); ++i)
        tmp[len_full - len_gen + 1 + i] = c[i];

    return Combination(tmp, len_full);
}
