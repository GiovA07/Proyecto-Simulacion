#include "train.h"
void train::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
kt1 = KT1;
kt2 = KT2;
state = "FAR";
sigma = numeric_limits<double>::max();
dist = new DistUniform(SEEDTRAIN);
}
double train::ta(double t) {
//This function returns a double.
return sigma;
}
void train::dint(double t) {
if (state == "FAR") {
	state = "NEAR";
	sigma = dist->genUniform(kt1,kt2);
	printLog("TRAIN: pase a un estado %s, con un sigma = %f\n", state.c_str(), sigma);
}else if (state == "NEAR" && sigma > kt1 && sigma < kt2) {
	state = "INSIDE";
	sigma = dist->genUniform(0,kt2-sigma);
	printLog("TRAIN: pase a un estado %s, con un sigma = %f\n", state.c_str(), sigma);
} else {
	state = "FAR";
	sigma = numeric_limits<double>::max();
	printLog("TRAIN: volvi al estado %s \n", state.c_str());
}
}
void train::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
double *aux;
aux = (double*) x.value;
if (state == "FAR") {
	sigma = 0;
	printLog("TRAIN: me llego un tren?= %d\n", (aux[0] >= 0 && aux[0] <= 3));

}
}
Event train::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)

if (state == "FAR") {
	out = APPROACH;
	printLog("TRAIN: manda un APROACH a Controller En tiempo de simulacion = %f\n", t);
	return Event(&out,0);
}else if(state == "NEAR"){
	out = IN;
	printLog("TRAIN: manda un IN En tiempo de simulacion = %f\n", t);
	return Event(&out,0);
}else if (state == "INSIDE") {
	out = EXIT;
	printLog("TRAIN: manda un EXIT a Controller y el Generador En tiempo de simulacion = %f\n", t);
	return Event(&out,0);
}
return Event();
}
void train::exit() {
//Code executed at the end of the simulation.

}
