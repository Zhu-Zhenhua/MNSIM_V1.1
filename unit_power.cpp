#include"global.h"
#include"function.h"
#include"module.h" 
double xbar_power,adder_power,adder_act,adder_leak,ad_power,da_power,decoder_power,read_power,pulse_power,write_power,Sub_power,power_u;
double area_l=0,power_l=0,latency_l=0;
void unit_power_c(Technology technology,int celltype,int xbarsize,int adposition,int adderposition,int pulseposition,int action_type,int sig_bit,int application,int resis_range,int netrow,double xbar_latency,double adda_latency,double adder_latency,double decoder_latency,double write_latency,double read_latency,double read_seperate){
 
	Cal_Adder Cal_Adder_temp(technology,sig_bit);
	Cal_Decoder Cal_Adder_Decoder(technology,celltype,xbarsize);
	if (read_seperate == 0){
		xbar_power = cal_xbar_p(tech,celltype,xbarsize,resis_range,action_type);
		if (action_type == 2){
			///cal_adder_p(technology,sig_bit);
	//         adder_avg_p = (adder_act * (netrow-1) + adder_leak * ((netrow-1)*netrow+netrow))/(netrow^2);

			//////////////adder_act == 0?????

			adder_power = adderposition * adder_act * xbarsize;
		}
		else
			adder_power = 0;
		ad_power = adposition * cal_ad_p(tech,sig_bit) * xbarsize;
		da_power = adposition * cal_da_p(tech,sig_bit) * xbarsize;
		//decoder_power = cal_decoder_p(tech,celltype,xbarsize,action_type);
		decoder_power = Cal_Adder_Decoder.Decoder_Power_Dynamic(Cal_Adder_Decoder.num_in);
		read_power = 4.528e-3/50 * xbarsize;
		pulse_power = pulseposition * 11.6e-3;
		write_power = pulse_power + 0;
    
		if (application ==0){
			Sub_power = adder_act * xbarsize;
			power_u = xbar_power*2 + adder_power + ad_power*2 + da_power + decoder_power + read_power + write_power + Sub_power;
			flags[0]=xbar_power*2;flags[1]=da_power;flags[2]=ad_power*2+read_power;flags[3]=adder_power+decoder_power+write_power+Sub_power;
	//       power_u = xbar_power*2 *xbar_latency + adder_power*adder_latency + (ad_power*2 + da_power)*adda_latency + decoder_power*decoder_latency + Sub_power*adder_latency + read_power*read_latency + write_power*write_latency;
		}
		else{
			power_u = xbar_power + adder_power + ad_power + da_power + decoder_power + read_power + write_power;
	//         power_u = xbar_power *xbar_latency + adder_power*adder_latency + (ad_power + da_power)*adda_latency + decoder_power*decoder_latency  + read_power*read_latency + write_power*write_latency;
		}
	 }
	else{
		xbar_power = cal_xbar_p(tech,celltype,xbarsize,resis_range,action_type)/xbarsize;
		if (action_type == 2){
			///cal_adder_p(technology,sig_bit);
	//         adder_avg_p = (adder_act * (netrow-1) + adder_leak * ((netrow-1)*netrow+netrow))/(netrow^2);
			adder_power = adderposition * Cal_Adder_temp.Adder_Power_Dynamic() * xbarsize;
		}
		else 
			adder_power = 0;
		ad_power = adposition * (cal_ad_p(tech,sig_bit));   
		da_power = adposition *cal_da_p(tech,sig_bit)* xbarsize;
		//decoder_power = cal_decoder_p(tech,celltype,xbarsize,action_type);
		decoder_power = Cal_Adder_Decoder.Decoder_Power_Dynamic(Cal_Adder_Decoder.num_in);
		read_power = 4.528e-3/50 * read_seperate;
		pulse_power = pulseposition * 11.6e-3;
		write_power = pulse_power + 0;

		if (application ==0){
			Sub_power = adder_act ;
			power_u = xbar_power*2 + adder_power + ad_power*2 + da_power + decoder_power + read_power + write_power + Sub_power;
			flags[0]=xbar_power*2;flags[1]=da_power;flags[2]=ad_power*2+read_power;flags[3]=adder_power+decoder_power+write_power+Sub_power;
	//         power_u = xbar_power*2 *xbar_latency + adder_power*adder_latency + (ad_power*2 + da_power)*adda_latency + decoder_power*decoder_latency + Sub_power*adder_latency + read_power*read_latency + write_power*write_latency;
		}
		else
			power_u = xbar_power + adder_power + ad_power + da_power + decoder_power + read_power + write_power;
	//         power_u = xbar_power *xbar_latency + adder_power*adder_latency + (ad_power + da_power)*adda_latency + decoder_power*decoder_latency  + read_power*read_latency + write_power*write_latency;
		}
 }