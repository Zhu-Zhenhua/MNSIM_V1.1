#include"global.h"
#include"function.h"
#include"module.h"
double xbar_latency,adda_latency,adder_latency,decoder_latency,write_latency,read_latency,latency_u;
void unit_latency_c(Technology technology,int celltype,int xbarsize,int adposition,int adderposition,int pulseposition,int action_type,int sig_bit,int read_seperate){
	
	Cal_Adder Cal_Adder_temp(technology,sig_bit);
	Cal_Decoder Cal_Adder_Decoder(technology,celltype,xbarsize);
	xbar_latency = cal_xbar_l(technology.featureSizeInNano,celltype,xbarsize,action_type);
    adda_latency = adposition * (cal_ad_l(technology.featureSizeInNano,sig_bit)+ cal_da_l(technology.featureSizeInNano,sig_bit));
    if (action_type == 2)
        adder_latency = adderposition * Cal_Adder_temp.Adder_Latency() ;
    else
        adder_latency = 0;
    //decoder_latency = cal_decoder_l(technology.featureSizeInNano,xbarsize,celltype,action_type);
	decoder_latency = Cal_Adder_Decoder.Decoder_Latency(Cal_Adder_Decoder.num_in);
    if (action_type == 0)
        write_latency = pulseposition * 1.6e-9;
    else
        write_latency = 0;
    read_latency = cal_read_l(technology.featureSizeInNano,xbarsize,action_type);
    
    latency_u = xbar_latency + adda_latency + adder_latency + decoder_latency + write_latency + read_latency;
        
    if (read_seperate > 0)
        latency_u =  xbar_latency + cal_da_l(technology.featureSizeInNano,sig_bit) +  write_latency+(adder_latency + decoder_latency + read_latency * ceil((double)xbarsize/read_seperate));
}