#include "distUniform.h"

DistUniform::DistUniform(int seed) {
    generator.seed(seed);
}

double DistUniform::genUniform(double min, double max) {
    uniform_real_distribution<double> distUnif(min, max);
    return distUnif(generator);
}
