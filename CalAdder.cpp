#include "CalAdder.h"

Cal_Adder::Cal_Adder(Technology tech,int addinputnum):INV_1IN(INV,NMOS,1,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273.15,tech),NAND_2IN(NAND,NMOS,2,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273,tech),NAND_3IN(NAND,NMOS,3,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273.15,tech),NAND_4IN(NAND,NMOS,4,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273.15,tech){
	Adder_InputNum = addinputnum;
}

Cal_Adder::~Cal_Adder(){}

double Cal_Adder::Adder_Area(){
	return Adder_InputNum*(3*INV_1IN.Area()+3*NAND_2IN.Area()+5*NAND_3IN.Area());
}

double Cal_Adder::Adder_Latency(){
	return Adder_InputNum*(MAX(INV_1IN.Latency()+NAND_3IN.Latency()+NAND_4IN.Latency(),INV_1IN.Latency()+NAND_3IN.Latency()+NAND_2IN.Latency()));
}

double Cal_Adder::Adder_Power_Leakage(){
	return Adder_InputNum*(3*INV_1IN.Power_Leakage()+3*NAND_2IN.Power_Leakage()+5*NAND_3IN.Power_Leakage());
};

double Cal_Adder::Adder_Power_Dynamic(){
	return Adder_InputNum*(3*INV_1IN.Power_Dynamic()+3*NAND_2IN.Power_Dynamic()+5*NAND_3IN.Power_Dynamic());	
};