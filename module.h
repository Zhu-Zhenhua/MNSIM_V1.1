#include<iostream>
#ifndef FORMULA_H_
#define FORMULA_H_

#include"global.h"
#include<math.h>
#include"CalAdder.h"
#include"CalDecoder.h"

#define max(a,b) (((a)> (b))?(a):(b))
#define min(a,b) (((a)< (b))?(a):(b))

void determin_sig(int xbarsize,int adderposition,int sig_bit,int cell_bit,int adposition);
void determin_net(int xbarsize,int rowsize,int columnsize,int signalsize);
double calWL(int tech);
double adsize(int tech,int sig_bit);
double dasize(int tech,int sig_bit);
double pulsesize(int tech);
double bl_decoder_size(int tech,int celltype,int xbarsize);
double sl_decoder_size(int tech,int celltype,int xbarsize);
double wl_decoder_size(int tech,int celltype,int xbarsize);
double readsize(int tech);
double writesize(int tech,int celltype);
double cal_xbar_l(int tech,int celltype,int xbarsize,int action_type);
double cal_ad_l(int tech,int sig_bit);
double cal_da_l(int tech,int sig_bit);
//double cal_adder_l(Technology technology,int sig_bit);
double cal_decoder_l(int tech,int xbarsize,int celltype,int action_type);
double cal_read_l(int tech,int xbarsize,int action_type);
double cal_xbar_p(int tech,int celltype,int xbarsize,double resis_range,int action_type);
//void cal_adder_p(Technology technology,int sig_bit);
double cal_ad_p(int tech,int sig_bit);
double cal_da_p(int tech,int sig_bit);
double cal_decoder_p(int tech,int celltype,int xbarsize,int action_type);
void periphery_area(Technology technology,int xbarsize,int netrow,int netcolumn,int adderposition,int pulseposition,int sig_bit,int application);
double neuronsize(int tech,int sig_bit,int application);
void periphery_latency_c(Technology technology,int netrow,int adderposition,int pulseposition,int sig_bit,int application);//Íâ²¿ÑÓÊ±
double cal_neuron_l(int tech,int sig_bit,int application);
void periphery_power_c(Technology tech,int xbarsize,int netrow,int netcolumn, int adderposition,int pulseposition,int sig_bit,int application,double adders_latency,double neuron_latency,double pulse_latency);
double cal_neuron_p(int tech,int sig_bit,int application);

#endif