#include "initGen.h"
void initGen::init(double t,...) {
//The 'parameters' variable contains the parameters transferred from the editor.
va_list parameters;
va_start(parameters,t);
//To get a parameter: %Name% = va_arg(parameters,%Type%)
//where:
//      %Name% is the parameter name
//	%Type% is the parameter type

stor = new StochasticLib1(SEEDGEN);
sigma = 0;
printLog("GENERADOR: genero el primer TREN. En sigma = %f.\n", sigma);

printLog("CONSTANTES: \n -- TRAIN -- \n KT1 = %f, KT2 = %f \n", KT1, KT2);
printLog("-- CONTROLLER -- \n KC1 = %f, KC2 = %f \n", KC1, KC2);
printLog("-- GATE -- \n KG1 = %f, KG2 = %f, KG3 = %f \n", KG1, KG2, KG3);
printLog("-- GENERADOR -- \n MEDIA = %f, SD = %f\n", MEAN, SD);

}
double initGen::ta(double t) {
//This function returns a double.
return sigma;
}
void initGen::dint(double t) {
sigma = numeric_limits<double>::max();
}
void initGen::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition
double *aux;
aux = (double*) x.value;
if(aux[0] == 3) {
	double aux = stor->Normal(MEAN, SD);
	sigma = fabs(aux);
	printLog("GENERADOR: me llego un exit? y Genero otro tren. En sigma = %f.\n", sigma);
}
}
Event initGen::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)
printLog("GENERADOR: Genero el TREN.\n");
out = sigma;
return Event(&out,0);
}
void initGen::exit() {
//Code executed at the end of the simulation.

}

