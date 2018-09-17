#include"CalDecoder.h"

Cal_Decoder::Cal_Decoder(Technology tech,int functiontype,int xbarnum):INV_1IN(INV,NMOS,1,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273.15,tech),NAND_2IN(NAND,NMOS,2,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273,tech),NAND_3IN(NAND,NMOS,3,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273.15,tech),NAND_4IN(NAND,NMOS,4,3*tech.featureSize,3*tech.featureSize,3*tech.featureSize,tech.featureSize*50,40+273.15,tech){
	num_in = ceil(log((double)xbarnum)/log(2.0));
	num_out = xbarnum;
	temp1=num_in;
	temp2=num_out;
	function_type= functiontype;
}

Cal_Decoder::~Cal_Decoder(){}

double Cal_Decoder::Decoder_Area(int temp){
	if(temp==2)
		return 2*3*INV_1IN.Area()+4*NAND_2IN.Area();
	else if(temp==3)
		return 3*3*INV_1IN.Area()+8*NAND_3IN.Area();
	else if(temp>3){
		temp1=temp/2;
		temp2=temp-temp1;
		int num_temp1=1,num_temp2=1;//temp1,temp2所对应的的2^temp1,2^temp2的端口个数
		for(int i=0;i<temp1;i++)
			num_temp1=num_temp1*2;
		for(int i=0;i<temp2;i++)
			num_temp2=num_temp2*2;
		return Decoder_Area(temp1)+Decoder_Area(temp2)+2*(num_temp1+num_temp2)*3*INV_1IN.Area()+num_out*NAND_2IN.Area();
	}
    else{ ///temp = 1
    	return 0;
    }
}

double Cal_Decoder::Decoder_Latency(int temp){
	if(temp==2)
		return 3*INV_1IN.Latency()+NAND_2IN.Latency();
	else if(temp==3)
		return 3*INV_1IN.Latency()+NAND_3IN.Latency();
	else if(temp>3){
		temp1=temp/2;
		temp2=temp-temp1;
		return MAX(Decoder_Latency(temp1),Decoder_Latency(temp2));
	}
    else{ //temp = 1
    	return 0;
    }
}

//double Cal_Decoder::Decoder_Power_Leakage(){
//};

double Cal_Decoder::Decoder_Power_Dynamic(int temp){
	if(temp==2)
		return 2*3*INV_1IN.Power_Dynamic()+4*NAND_2IN.Power_Dynamic();
	else if(temp==3)
		return 3*3*INV_1IN.Power_Dynamic()+8*NAND_3IN.Power_Dynamic();
	else if(temp>3){
		temp1=temp/2;
		temp2=temp-temp1;
		int num_temp1=1,num_temp2=1;//temp1,temp2所对应的的2^temp1,2^temp2的端口个数
		for(int i=0;i<temp1;i++)
			num_temp1=num_temp1*2;
		for(int i=0;i<temp2;i++)
			num_temp2=num_temp2*2;
		return Decoder_Power_Dynamic(temp1)+Decoder_Power_Dynamic(temp2)+2*(num_temp1+num_temp2)*3*INV_1IN.Power_Dynamic()+num_out*NAND_2IN.Power_Dynamic();
	}
	else{
    	return 0;
    }
};
