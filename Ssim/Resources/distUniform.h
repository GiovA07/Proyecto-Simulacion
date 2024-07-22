#ifndef DISTUNIFORME_H
#define DISTUNIFORME_H

#include <random>
using namespace std;

class DistUniform{
private:
    mt19937 generator;
public:
    DistUniform(int seed);
    double genUniform(double min, double max);
};

#endif

