//CPP:Ssim/train.cpp
//CPP:Ssim/Resources/distUniform.cpp

#if !defined train_h
#define train_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"
#include "Resources/distUniform.h"
#include "Resources/constants.h"
#include "limits"
#include "string"

using namespace std;


class train: public Simulator {
// Declare the state,
// output variables
// and parameters
double sigma;

string state;

double out;

double kt1;
double kt2;

DistUniform *dist;
public:
	train(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
