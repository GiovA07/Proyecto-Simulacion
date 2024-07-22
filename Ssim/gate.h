//CPP:Ssim/gate.cpp
//CPP:Ssim/Resources/distUniform.cpp

#if !defined gate_h
#define gate_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"


#include "Resources/distUniform.h"
#include "Resources/constants.h"
#include "limits"
#include "string"

using namespace std;


class gate: public Simulator {
// Declare the state,
// output variables
// and parameters
double sigma;

string state;

double out;

double kg1;
double kg2;
double kg3;

DistUniform *dist;


public:
	gate(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
