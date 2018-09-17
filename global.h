#include<iostream>
#ifndef GLOBAL_H
#define GLOBAL_H

extern int control;
extern double input_sig;
extern double output_neighbor;
extern double output_sig;
extern double signalsize;
extern int netcolumn;
extern int netrow,count;
extern double bandwidth;
extern double flags[4];
extern double xbar_area,techwl,ad_area,da_area,adder_area,pulse_area,decoder_area,read_area,write_area,Sub_area,area_u;
extern double xbar_latency,adda_latency,adder_latency,decoder_latency,write_latency,read_latency,latency_u;
extern double xbar_power,adder_power,adder_act,adder_leak,ad_power,da_power,decoder_power,read_power,pulse_power,write_power,Sub_power,power_u;
extern double area_l,power_l,latency_l;
extern double adders_area,neuron_area,area_p;
extern double adders_latency,neuron_latency,pulse_latency,latency_p;
extern double adders_power,neuron_power,power_p;
extern double accuracy,d1,area,area_flags,energy,latency,latency_multi,power_multi,power_flags,area_multi,power,energy,application,action_type;
extern int target;
extern double tech,pulseposition,cell_bit,lantency_multi;

#endif
