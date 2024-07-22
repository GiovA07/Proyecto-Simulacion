#include "gate.h"
void gate::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
kg1 = KG1;
kg2 = KG2;
kg3 = KG3;

state = "OPEN";
dist = new DistUniform(SEEDGATE);
sigma = numeric_limits<double>::max();

}
double gate::ta(double t) {
//This function returns a double.
return sigma;
}
void gate::dint(double t) {
if (state == "LOWERING" && sigma < kg1) {
	state = "CLOSED";
	sigma = numeric_limits<double>::max();
	printLog("GATE: pase del estado LOWERING(2) al estado CLOSED(3) En tiempo de simulacion = %f \n", t);
} else if (state == "RAISING" && sigma < kg3 && sigma > kg2) {
	state = "OPEN";
	sigma = numeric_limits<double>::max();
	printLog("GATE: pase del estado RAISING(4) al estado OPEN(1) En tiempo de simulacion = %f\n", t);
}
}
void gate::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
double *aux;
aux = (double*) x.value;

if (aux[0] == LOWER && state == "OPEN") {
	state = "LOWERING";
	sigma = dist->genUniform(0,kg1);
	printLog("GATE: RECIBI UN LOWER pase del estado OPEN(1) al estado LOWERING(2) con sigma = %f \n", sigma);

}else if (aux[0] == RAISE && state == "CLOSED") {
	state = "RAISING";
	sigma = dist->genUniform(kg2,kg3);
	printLog("GATE: RECIBI UN RAISE pase del estado CLOSED(3) al estado RAISING(4) con sigma = %f \n", sigma);
}
}
Event gate::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
if(state == "LOWERING") {
	out = DOWN;
	return Event(&out,0);
} else if(state == "RAISING") {
	out = UP;
	return Event(&out,0);
}
return Event();
}
void gate::exit() {
//Code executed at the end of the simulation.

}
