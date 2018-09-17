#include "CalRegister.h"

Cal_Register::Cal_Register(Technology tech,int inputnum):INV_1IN(INV,NMOS,1,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273.15,tech),NOR_2IN(NOR,NMOS,2,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273,tech),NOR_3IN(NOR,NMOS,3,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273.15,tech){
	Inputnum = inputnum;
}

Cal_Register::~Cal_Register(){}

double Cal_Register::Register_Area(){
	return Inputnum*(5*NOR_2IN.Area()+NOR_3IN.Area());
}

double Cal_Register::Register_Power_Dynamic(){
	return Inputnum*(5*NOR_2IN.Power_Dynamic()+NOR_3IN.Power_Dynamic());
}

double Cal_Register::Register_Latency(){
	return (2+2)*NOR_2IN.Latency()+NOR_3IN.Latency();
}
