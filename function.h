#include<iostream>
#ifndef FUNCTION_H
#define FUNCTION_H

#include"module.h"
#include"global.h"

void unit_area_c(Technology technology,int celltype,int xbarsize,int adposition,int adderposition,int pulseposition,int sig_bit,int application,double rramtech,int read_seperate);
void unit_latency_c(Technology technology,int celltype,int xbarsize,int adposition,int adderposition,int pulseposition,int action_type,int sig_bit,int read_seperate);
void unit_power_c(Technology technology,int celltype,int xbarsize,int adposition,int adderposition,int pulseposition,int action_type,int sig_bit,int application,int resis_range,int netrow,double xbar_latency,double adda_latency,double adder_latency,double decoder_latency,double write_latency,double read_latency,double read_seperate);
void accuracy_c(int xbarsize,int linetech,int sig_bit,int cell_bit,int resis_range,double input_err);
void equal(double netlevel,double area,double energy,double latency,double power,double accuracy,double area_multi,double power_multi,double latency_multi,double read_sep,double adposition,double bit_level,double adderposition,double pulseposition,double linetech,double celltype,double xbarsize);
double max1(int a,int b,int c);

#endif