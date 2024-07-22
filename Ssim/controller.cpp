#include "controller.h"
void controller::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type
kc1 = KC1;
kc2 = KC2;
sigma = numeric_limits<double>::max();
out = 0;
state = "SC1";
dist = new DistUniform(SEEDCONTROLLER);
}
double controller::ta(double t) {
//This function returns a double.
return sigma;
}
void controller::dint(double t) {
if (state == "SC2" && sigma == kc1) {
	state = "SC3";
	sigma = numeric_limits<double>::max();
	printLog("CONTROLLER: pase del estado APPSign(2) a un estado 3\n");
} else if (state == "SC4" && sigma < kc2) {
	state = "SC1";
	sigma = numeric_limits<double>::max();
	printLog("CONTROLLER: pase del estado ExitSign(4) a un estado TRAIN WAITING(1)\n");
}
}
void controller::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
double *aux;
aux = (double*) x.value;
if (aux[0] == APPROACH && state == "SC1") {
	state = "SC2";
	sigma = kc1;
	printLog("CONTROLLER: RECIBI UN APPROACH pase del estado TRAIN WAITING(1) a un estado APPSign(2) con sigma = %f En tiempo de simulacion = %f \n", sigma, t);
} else if (aux[0] == EXIT && state == "SC3") {
	state = "SC4";
	sigma = dist->genUniform(0,kc2);
	printLog("CONTROLLER: RECIBI UN EXIT pase del estado EXIT WAITING(3) al estado ExitSign(4) con sigma = %f En tiempo de simulacion = %f \n", sigma, t);
} else {
	printLog("CONTROLLER: RECIBI UN IN no hice nada\n");
}
}
Event controller::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
if (state == "SC2") {
	out = LOWER;
	printLog("CONTROLLER: MANDO UN LOWER POR SALIDA En tiempo de simulacion = %f \n", t);
	return Event(&out,0);
}else if (state == "SC4") {
	out = RAISE;
	printLog("CONTROLLER: MANDO UN RAISE POR SALIDA En tiempo de simulacion = %f \n", t);
	return Event(&out,0);
}

return Event();
}
void controller::exit() {
//Code executed at the end of the simulation.

}
