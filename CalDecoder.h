#ifndef CALDECODER_H_
#define CALDECODER_H_

#include "CalculateGate.h"
#include "Technology.h"
#include <stdlib.h>
#include <math.h>
#include "constant.h"

class Cal_Decoder {
	public:
		int num_in;//bit of input
		int num_out;//bit of output
		int temp1,temp2;
		int function_type;
		CalGate INV_1IN,NAND_2IN,NAND_3IN,NAND_4IN;

		Cal_Decoder(Technology tech,int function_type,int xbarnum);//tech determines widthnoms£¬widthpmos
		virtual ~Cal_Decoder(); 
		double Decoder_Area(int temp);
		double Decoder_Latency(int temp);
//		double Decoder_Power_Leakage();
		double Decoder_Power_Dynamic(int temp);
};

#endif
