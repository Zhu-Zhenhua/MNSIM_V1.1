#include "CalculateGate.h"

CalGate::CalGate(int gatetype, int type_npmos, int numinput, double widthnmos, double widthpmos, double width, double heighttransistorregion, double temperature, Technology tech) {
	GateType = gatetype;
	Type_NPMOS = type_npmos;
	NumInput = numinput;
	WidthNMOS = widthnmos;
	WidthPMOS = widthpmos;
	Width = width;
	HeightTransistorRegion = heighttransistorregion;
	Temperature = temperature;
	Tech = tech;
}

CalGate::~CalGate(){
	// TODO Auto-generated destructor
}

//height & width actually unused
double CalGate::Area(){
	double height, width;
	return CalculateGateArea(GateType, NumInput, WidthNMOS, WidthPMOS, HeightTransistorRegion, Tech, &height, &width);
}

double CalGate::Latency(){
	double r, c, cin, cout, gm, beta, t_pre, rampoutput;
	r = CalculateOnResistance(Width, Type_NPMOS, Temperature, Tech);
	gm = CalculateTransconductance(Width, Type_NPMOS, Tech);
	CalculateGateCapacitance(GateType, NumInput, WidthNMOS, WidthPMOS, HeightTransistorRegion, Tech, &cin, &cout);
	c = cout;	/* we don't consider cin of the device at the first stage */
	
	beta = 1 / (r * gm);	/* beta = 0 for comparator */
	t_pre = 1e50;			/* t_pre = infinity to ignore its effect */
	return horowitz(r*c, beta, t_pre, &rampoutput);
}

double CalGate::Power_Leakage(){
	return Tech.vdd * CalculateGateLeakage(GateType, NumInput, WidthNMOS, WidthPMOS, Temperature, Tech);
}

double CalGate::Power_Dynamic(){
	double c, cin, cout;
	CalculateGateCapacitance(GateType, NumInput, WidthNMOS, WidthPMOS, HeightTransistorRegion, Tech, &cin, &cout);
	c = cout;	/* we don't consider cin of the device at the first stage */
	return c * Tech.vdd * Tech.vdd;
}