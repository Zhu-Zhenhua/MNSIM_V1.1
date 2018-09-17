#ifndef CALADDER_H_
#define CALADDER_H_

#include "CalculateGate.h"
#include "Technology.h"
#include <stdlib.h>
#include "constant.h"

class Cal_Adder {
	public:
		int Adder_InputNum;//bit of input
		CalGate INV_1IN,NAND_2IN,NAND_3IN,NAND_4IN;
		
		Cal_Adder(Technology tech,int addinputnum);//tech 确定widthnoms，widthpmos
		virtual ~Cal_Adder(); 
		double Adder_Area();
		double Adder_Latency();
		double Adder_Power_Leakage();
		double Adder_Power_Dynamic();
};

#endif
		