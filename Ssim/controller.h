//CPP:Ssim/controller.cpp
//CPP:Ssim/Resources/distUniform.cpp

#if !defined controller_h
#define controller_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "Resources/distUniform.h"
#include "Resources/constants.h"
#include "limits"
#include "string"

using namespace std;


class controller: public Simulator {
// Declare the state,
// output variables
// and parameters
double sigma;

double out;

string state;

double kc1;
double kc2;

DistUniform *dist;


public:
	controller(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
