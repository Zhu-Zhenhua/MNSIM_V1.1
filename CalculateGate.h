#ifndef CALCULATEGATE_H_
#define CALCULATEGATE_H_

#include "formula.h"
#include <stdlib.h>
#include "Technology.h"

class CalGate {
public:
	/* Properties */
	int GateType;
	int Type_NPMOS;
	int NumInput;
	double WidthNMOS;
	double WidthPMOS;
	double Width;
	double HeightTransistorRegion;
	double Temperature;
	Technology Tech;

	/* Functions */
	CalGate(int gatetype, int type_npmos, int numinput, double widthnmos, double widthpmos, double width, double heighttransistorregion, double temperature, Technology tech);
	virtual ~CalGate();
	double Area();
	double Latency();
	double Power_Leakage();
	double Power_Dynamic();
};

#endif /* CALCULATEGATE_H_ */