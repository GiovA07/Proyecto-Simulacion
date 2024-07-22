//CPP:Ssim/initGen.cpp
//CPP:Ssim/Resources/distUniform.cpp
//CPP:/random/lib/stocc.cpp
//CPP:/random/lib/randomc.cpp
//CPP:random/normal_gen.cpp
#if !defined initGen_h
#define initGen_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include <cmath>
#include "limits"
#include "random/lib/stocc.h"
#include "Resources/constants.h"

using namespace std;

class initGen: public Simulator {
// Declare the state,
// output variables
// and parameters
double sigma;

double out;

StochasticLib1 *stor;

public:
	initGen(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
