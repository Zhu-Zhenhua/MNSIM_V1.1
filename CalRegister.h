#include <stdlib.h>
#ifndef CALREGISTER_H_
#define CALREGISTER_H_

#include "CalculateGate.h"
#include "Technology.h"
#include "constant.h"


class Cal_Register {
public:
	int Inputnum;
	CalGate INV_1IN,NOR_2IN,NOR_3IN;

	Cal_Register(Technology tech,int addinputnum);//tech to determine widthnoms£¬widthpmos
	virtual ~Cal_Register (); 
	double Register_Area();
	double Register_Latency();
	//double Adder_Power_Leakage();
	double Register_Power_Dynamic();
};

#endif