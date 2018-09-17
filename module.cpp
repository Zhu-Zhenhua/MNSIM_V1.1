#include"module.h"

int control;
double input_sig;
double output_neighbor;
double output_sig;
double signalsize;
int netcolumn;
int netrow;
double bandwidth;
double flags[4];
double adders_area,neuron_area,area_p;
double adders_latency,neuron_latency,pulse_latency,latency_p;
double adders_power,neuron_power,power_p;

///////////bandwith calculation (determin_sig and determin_net) //////////////
void determin_sig(int xbarsize,int adderposition,int sig_bit,int cell_bit,int adposition){
	control = 2 ; //if adders are inside, arch needs two additional column signals (input and output)
    input_sig = 2*(log((double)xbarsize)/log(2.0)) + sig_bit*xbarsize + control+ adderposition * (sig_bit+cell_bit);
    flags[0] = 1;
    output_neighbor = (sig_bit+cell_bit)*adposition;
    output_sig = cell_bit + (sig_bit+cell_bit) * (1-adposition) + flags[0];//output to neighbour block+output to external+output flag
    signalsize = input_sig + output_sig + output_neighbor;
}

void determin_net(int xbarsize,int rowsize,int columnsize,int signalsize){
	netcolumn = ceil((double)columnsize/xbarsize);
    netrow = ceil((double)rowsize/xbarsize);
    bandwidth = signalsize * netrow;
}
///////////////////////////////////////////////////////////////////////////////////////////


double calWL(int tech){    //////////will update later
	switch(tech){
	case 130:
            return 6; break;
	case 90:
            return 6; break;
    default:
            return 6; break;
	}
}

double adsize(int tech,int sig_bit){
	if (tech<0)
        return (abs(tech) * 1e-9)*(abs(tech) * 1e-9) *18   * sig_bit * 20;
    else 
        return (abs(tech) * 1e-9)*(abs(tech) * 1e-9) *6   * 2800 * sig_bit/8;
}

double dasize(int tech,int sig_bit){
	if (tech<0 )
        return (abs(tech)*1e-9)*(abs(tech)*1e-9)*18*sig_bit*20;
    else
        return (abs(tech)*1e-9)*(abs(tech)*1e-9)*6*3096/8*sig_bit/8;
}

double pulsesize(int tech){
	if(tech<0)
        return (tech * 1e-9)*(tech * 1e-9) * 18 * 20;
    else
        return 182e-6 * 65e-6 * ((double)tech/130)*((double)tech/130);
}

/*double bl_decoder_size(int tech,int celltype,int xbarsize){
	double L; 
	int m,p,k;
	if (tech<0){
		if (celltype == 1)
			return(tech *1e-9)*(tech *1e-9) * 18 *25 * xbarsize;
	}
	else{
	//	    if celltype == 1
			L = tech * 1e-9;
			m = ceil(log((double)xbarsize)/log(2.0));
			switch (m) {
				case 2:
					k = 0;
					p = 2; 
					break;
				case 3:
					k = 0;
					p = 3;
					break;
				case 4:
					k = 0;
					p = 4;
					break;
				case 5:
					k = 2;
					p = 3;
					break;
				case 6:
					k = 3;
					p = 3;
					break;
				case 7:
					k = 3;
					p = 4;
					break;
				case 8:
					k = 4;
					p = 4;
					break;
				case 9:
					k = 4;
					p = 5;
					break;
				case 10:
					k = 5;
					p = 5;
					break;
				default:
					;
			}
			return(1+1+2+2+2+1+1+1+8+8+2+1+60+30+10)*L*L*m+(1+2+4+8+16+32)*L*L*k+(2*k+k*k*k+1+2+4+8+16+32) *L*L*k+(1+2+4+8+16+32)*L*L*p + (2*p+p*p*p+1+2+4+8+16+32) *L*L*p;
	}
}
double sl_decoder_size(int tech,int celltype,int xbarsize){
	return 0;
}
double wl_decoder_size(int tech,int celltype,int xbarsize){
	return bl_decoder_size(tech,celltype,xbarsize);
}*/
double readsize(int tech){
	if(tech<0)
        return (tech * 1e-9)*(tech * 1e-9) * 18  * 20;
    else
        return (tech * 1e-9)*(tech * 1e-9) * 200;
}
double writesize(int tech,int celltype){
	return (tech * 1e-9)*(tech * 1e-9) *18 *2;
}

///////// update: latency should be dependent on xbarsize
double cal_xbar_l(int tech,int celltype,int xbarsize,int action_type){
	return 100e-9;
}
double cal_ad_l(int tech,int sig_bit){
	return 0.667e-9;
}
double cal_da_l(int tech,int sig_bit){
	return 1/(960e6);
}
/*double cal_adder_l(int tech,int sig_bit){
	return 1e-9;
}*/
/*double cal_decoder_l(int tech,int xbarsize,int celltype,int action_type){
	return 1e-8;
}*/
double cal_read_l(int tech,int xbarsize,int action_type){
	return 168.96e-9;
}
double cal_xbar_p(int tech,int celltype,int xbarsize,double resis_range,int action_type){
	double voltage = 0.1;
	/// may be wrong??? 10e3???
    double cell_r_p = voltage*voltage /10e3;		//		(2/(1/resis_range(1) + 1/resis_range(2)));
//     0.1*0.1/(500+2.9732*64+1.3*90/130*Rn/0.9+1.3*90/130/0.9*Rn*Rp/(Rn+Rp))*128*128+0.0024;
    if (action_type == 2)
        return cell_r_p * xbarsize*xbarsize;
    return 0;
}
/*void cal_adder_p(int tech,int sig_bit){
	adder_power = 0.1e-3;
    adder_leak = 0;
}*/
double cal_ad_p(int tech,int sig_bit){
	return 0.26e-3;
}
double cal_da_p(int tech,int sig_bit){
	return 55e-6;
}
/*double cal_decoder_p(int tech,int celltype,int xbarsize,int action_type){
	return 0;
}*/
void periphery_area(Technology technology,int xbarsize,int netrow,int netcolumn,int adderposition,int pulseposition,int sig_bit,int application){
	
	Cal_Adder  Cal_Adder_temp(technology,sig_bit);
	if (adderposition == 0) // add out of xbar
        adders_area = Cal_Adder_temp.Adder_Area() * (netrow-1) * netcolumn *xbarsize;
    else
        adders_area = 0;
    neuron_area = neuronsize(technology.featureSizeInNano,sig_bit,application) * xbarsize * netcolumn;
    pulse_area = (1-pulseposition) * pulsesize(technology.featureSizeInNano);
    area_p = adders_area + neuron_area + pulse_area;
    flags[0]= 1;
}
double neuronsize(int tech,int sig_bit,int application){
	if(tech<0)
        return (tech * 1e-9)*(tech * 1e-9)* 18  * 20;
    else
        if (application == 0)
           return adsize(tech,sig_bit) + 15e-6 * 18e-6 * ((double)tech/130)*((double)tech/130)+ dasize(tech,sig_bit);
        else
           return (tech * 1e-9)*(tech * 1e-9) * 6 * 20+ dasize(tech,sig_bit);
}
void periphery_latency_c(Technology technology,int netrow,int adderposition,int pulseposition,int sig_bit,int application){
	
	Cal_Adder Cal_Adder_temp(technology,sig_bit);
	if (adderposition == 0) // add out of xbar
        adders_latency = Cal_Adder_temp.Adder_Latency() * ceil(log((double)netrow)/log(2.0));
    else
        adders_latency = 0;
    neuron_latency = cal_neuron_l(technology.featureSizeInNano,sig_bit,application);
    pulse_latency = (1-pulseposition) * 1.6e-9;
    latency_p = adders_latency + neuron_latency + pulse_latency;
    flags[0] = 1;
}
double cal_neuron_l(int tech,int sig_bit,int application){
	if (application == 0)
        return cal_ad_l(tech,sig_bit) + 6e-8 + cal_da_l(tech,sig_bit);
    else
        return 6e-8+ cal_da_l(tech,sig_bit);
}
void periphery_power_c(Technology tech,int xbarsize,int netrow,int netcolumn, int adderposition,int pulseposition,int sig_bit,int application,double adders_latency,double neuron_latency,double pulse_latency){
	
	Cal_Adder Cal_Adder_temp(tech,sig_bit);
	if (adderposition == 0){ // add out of xbar
        adder_act=Cal_Adder_temp.Adder_Power_Dynamic();
		adder_leak= Cal_Adder_temp.Adder_Power_Leakage();
        adders_power = (adder_act * (netrow-1) * netcolumn) ;//*adders_latency ;//+adder_leak* (netrow-1) * netcolumn*(neuron_latency+pulse_latency))/(adders_latency + neuron_latency + pulse_latency) ;
	}
	else
        adders_power = 0;
    neuron_power = cal_neuron_p(tech.featureSizeInNano ,sig_bit,application) * xbarsize * netcolumn;
//     neuron_power = neuron_power * neuron_latency/(adders_latency + neuron_latency + pulse_latency);
    pulse_power = (1-pulseposition) * 11.6e-3;// *pulse_latency/(adders_latency + neuron_latency + pulse_latency);
    power_p = adders_power + neuron_power + pulse_power;
    flags[0] = 1;
}
double cal_neuron_p(int tech,int sig_bit,int application){
	if (application == 0)
        return cal_ad_p(tech,sig_bit) + 0 + cal_da_p(tech,sig_bit);
    else
        return 1.5e-3+ cal_da_p(tech,sig_bit);
}
