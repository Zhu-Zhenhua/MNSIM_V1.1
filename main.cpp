#include<iostream>
#include<fstream>
#include<iomanip>
#include<math.h>
#include<time.h>
#include<string>
#include"InputParameter.h"
#include"module.h"
#include"formula.h"
#include"global.h"
#include"function.h"
#include"Technology.h"

using namespace std;

InputParameter *inputParameter;
int count_my = 1;
double area,area_flags,latency,latency_multi,power_multi,power_flags,area_multi,power,energy,application,action_type;
int target;
double pulseposition = 0;
double cell_bit = 8;

double ** AAestrslt;
double ** AAAestrslt;
int row, row2;
//[17000][19];AAAestrslt[1100][19];
int mincount = 0;
double tech;
int err_count;
Technology *technology;

int main(int argc, char *argv[]) {
	clock_t tic,toc;
	tic=clock();
	inputParameter = new InputParameter();

	string inputFileName;
	string outputFileName;

	if (argc == 1) {   //read configuration file
		inputFileName = "SimConfig.txt";
		outputFileName = "result.txt";
		cout << "Default sim-config file (SimConfig.txt) is loaded" << endl;
		cout << "Use default output results file (result.txt)" << endl;
	} 
	else if (argc == 2) {
		inputFileName = argv[1];
		cout << "User-defined sim-config file (" << inputFileName << ") is loaded" << endl;
		cout << "Use default output results file (result.txt)" << endl;
	} 
	else if (argc == 3) {
		inputFileName = argv[1];
		outputFileName = argv[2];
		cout << "User-defined sim-config file (" << inputFileName << ") is loaded" << endl;
		cout << "Print output to result file (" << outputFileName << ")" << endl;
	} 
	else {
		cout << "Error: Please use the correct format as follows" << endl;
		cout << "  Use the default configuration: " << argv[0] << endl;
		cout << "  Use the customized configuration: " << argv[0] << " <.txt file>"  << endl;
		exit(-1);
	}
	cout << endl;

	//read configs  &  init configs
	inputParameter->ReadInputParameterFromFile(inputFileName);
	if (inputParameter->Application[0] == 'a' ||inputParameter->Application[0] == 'A')
        application = 0;
    else
        application = 1;
	if (inputParameter->Action_type[0] == 'c' || inputParameter->Action_type[0] == 'C') //calculate phase
    	action_type = 2;
    else
    	action_type = 0;

	//Behavior level estimation
    //Unused part
	switch (inputParameter->Target_Output[0]) {
		case 'a':
				target = 1;break;
		case 'A':
				target = 1;break;
		case 'e':
				target = 2;break;
		case 'E':
				target = 2;break;
		case 'l':
				target = 3;break;
		case 'L':
				target = 3;break;
		case 'p':
				target = 4;break;
		case 'P':
				target = 4;break;
	}

	technology = new Technology();
	technology->Initialize(inputParameter->TranTech, HP/*inputParameter->deviceRoadmap*/);

	Technology techHigh;
	double alpha = 0;
	if (inputParameter->TranTech > 200){  //choose the technology node and calculate the parameters
		// TO-DO: technology node > 200 nm
	} 
	else if (inputParameter->TranTech > 120) { // 120 nm < technology node <= 200 nm
		techHigh.Initialize(200, HP/*inputParameter->deviceRoadmap*/);
		alpha = (inputParameter->TranTech - 120.0) / 60;
	} 
	else if (inputParameter->TranTech > 90) { // 90 nm < technology node <= 120 nm
		techHigh.Initialize(120, HP/*inputParameter->deviceRoadmap*/);
		alpha = (inputParameter->TranTech - 90.0) / 30;
	} 
	else if (inputParameter->TranTech > 65) { // 65 nm < technology node <= 90 nm
		techHigh.Initialize(90, HP/*inputParameter->deviceRoadmap*/);
		alpha = (inputParameter->TranTech - 65.0) / 25;
	} 
	else if (inputParameter->TranTech > 45) { // 45 nm < technology node <= 65 nm
		techHigh.Initialize(65, HP/*inputParameter->deviceRoadmap*/);
		alpha = (inputParameter->TranTech - 45.0) / 20;
	} 
	else if (inputParameter->TranTech >= 32) { // 32 nm < technology node <= 45 nm
		techHigh.Initialize(45, HP/*inputParameter->deviceRoadmap*/);
		alpha = (inputParameter->TranTech - 32.0) / 13;
	} 
	else if (inputParameter->TranTech >= 22) { // 22 nm < technology node <= 32 nm
		techHigh.Initialize(32, HP/*inputParameter->deviceRoadmap*/);
		alpha = (inputParameter->TranTech - 22.0) / 10;
	} 
	else {
		//TO-DO: technology node < 22 nm
	}

	technology->InterpolateWith(techHigh, alpha);  //

	//  load tech
	int tech = inputParameter->TranTech;
    double minarea = 8e10;
    double minenergy = 8e10;
    double minpower = 8e10;
    double minlatency = 8e10;
    double minerr = 8e10;
	//double mintarget[8]={0,0,minarea,minenergy,minlatency,minerr,minpower};
    double mintarget[4]={minarea,minenergy,minlatency,minpower};
	double input_err[200]={0};
    row = (min(1,inputParameter->maxAdPos)-max(0,inputParameter->minAdPos)+1)*(min(16,inputParameter->maxBtLv)-max(0,inputParameter->minBtLv)+1)*(min(1,inputParameter->maxAdder)-max(0,inputParameter->minAdder)+1)*(log(inputParameter->maxXbarSize)/log(2)-log(inputParameter->minXbarSize)/log(2)+1)*128*inputParameter->AppScale+1;//*6 Decide by the size of crossbar
	AAestrslt = new double* [row];
	for(int i =0; i < row; i++)
		AAestrslt[i] = new double [19];
    for (double adposition=max(0,inputParameter->minAdPos);adposition<=min(1,inputParameter->maxAdPos);adposition++) {
        for (double bit_level = max(0,inputParameter->minBtLv);(bit_level<=min(16,inputParameter->maxBtLv));bit_level++) {
            for (double adderposition = max(0,inputParameter->minAdder);adderposition<=min(1,inputParameter->maxAdder);adderposition++) {
                for (double linetech = 90;linetech<=90;linetech++) {//[18,22,28,36,45,65,90];
                    for (double celltype = 1;celltype<=1;celltype++) {
                        //pulseposition = 0;
                        for (double xbarsize = inputParameter->minXbarSize;xbarsize<=inputParameter->maxXbarSize;xbarsize*=2) {//[4,8,16,32,64,128,256]%,512,1024]
                            for (double read_sep = 1;read_sep<=128;read_sep++) {//xbarsize/128 : xbarsize/128 : xbarsize%8:8:xbarsize
                                if (xbarsize<inputParameter->minXbarSize || xbarsize > inputParameter->maxXbarSize)
                                    cout<<"error:xbarsize over the limit"<<endl;
                                else
									for (double netlevel = 1;netlevel<=inputParameter->AppScale;netlevel++) { //-1
										if (bit_level != 0)
											cell_bit = bit_level;
										//calculate bandwidth
										determin_sig(xbarsize,adderposition,inputParameter->sig_bit,cell_bit,adposition);
										determin_net(xbarsize,inputParameter->NetScale[2*(int)netlevel-1-1],inputParameter->NetScale[2*(int)netlevel-1],signalsize);
											
										unit_area_c(*technology,celltype,xbarsize,adposition,adderposition,pulseposition,inputParameter->sig_bit,application,inputParameter->rramtech,read_sep);
											
										unit_latency_c(*technology,celltype,xbarsize,adposition,adderposition,pulseposition,action_type,inputParameter->sig_bit,read_sep);
											
										unit_power_c(*technology,celltype,xbarsize,adposition,adderposition,pulseposition,action_type,inputParameter->sig_bit,application,inputParameter->maxRRang,netrow,xbar_latency,adda_latency,adder_latency,decoder_latency,write_latency,read_latency,read_sep);
											
										periphery_area(*technology,xbarsize, netrow, netcolumn, adderposition,pulseposition,inputParameter->sig_bit,application);
											
										periphery_latency_c( *technology,netrow, adderposition,pulseposition,inputParameter->sig_bit,application);
										    
										periphery_power_c(*technology,xbarsize, netrow, netcolumn, adderposition,pulseposition,inputParameter->sig_bit,application,adders_latency,neuron_latency,pulse_latency);
											

										accuracy_c(xbarsize,linetech,inputParameter->sig_bit,cell_bit,inputParameter->maxRRang,input_err[(int)netlevel-1]);
											
										input_err[(int)netlevel] = accuracy;
											
										area = area_u * netrow * netcolumn + area_l + area_p ;//+ area_r + area_w;
										//area_flags = area_flags * netrow * netcolumn;
										if (adderposition == 0) {
											energy = power_u * latency_u * netrow * netcolumn + power_l * latency_l + power_p * latency_p;// + power_r + power_w;
											latency = latency_u + latency_l + latency_p;
											latency_multi = latency_u;
										}
										else {
											energy = power_u * latency_u * netrow * netcolumn + power_l * latency_l + power_p * latency_p;
											latency = latency_u * netrow + latency_l + latency_p;
											latency_multi = latency_u * netrow;
										}
										power_multi = power_u * netrow * netcolumn;
										//power_flags = power_flags * netrow * netcolumn;
										area_multi = area_u * netrow * netcolumn;
										power = power_u  * netrow * netcolumn + power_l  + power_p ;
										energy = power * latency;
											
										equal(netlevel,area,energy,latency,power,accuracy,area_multi,power_multi,latency_multi,read_sep,adposition,bit_level,adderposition,pulseposition,linetech,celltype,xbarsize);

										if (accuracy < minerr) {
											minerr = accuracy;
											err_count = count_my;
										}
										count_my = count_my + 1;
									}				
							}
            			}
        			}
    			}
    		}
		}
	}



    double design_space = count_my/inputParameter->AppScale;

    //row2 = design_space*inputParameter->AppScale+1;
    AAAestrslt = new double* [int(design_space)+1];
	for(int i =0; i <= design_space; i++)
		AAAestrslt[i] = new double [19];
	for (int temp_count = 1;temp_count<=design_space;temp_count++) {
		for(int netlevel_temp=1;netlevel_temp<=inputParameter->AppScale;netlevel_temp++) {
			AAAestrslt[temp_count][0] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][0];
			AAAestrslt[temp_count][1] = AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][1];
			AAAestrslt[temp_count][2] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][2];
			AAAestrslt[temp_count][3] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][3]*(inputParameter->Computation_Time[netlevel_temp-1]);
			if(inputParameter->Pipeline == 0) //not pipelined
				AAAestrslt[temp_count][4] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][4]*(inputParameter->Computation_Time[netlevel_temp-1]);
			else if (netlevel_temp == 1)
				AAAestrslt[temp_count][4] = AAestrslt[((temp_count-1) * inputParameter->AppScale + 1)][4]*(inputParameter->Computation_Time[0]);
			else
				AAAestrslt[temp_count][4] = (AAAestrslt[temp_count][4] > AAestrslt[((temp_count-1) * inputParameter->AppScale + netlevel_temp)][4]*(inputParameter->Computation_Time[netlevel_temp-1]))? AAAestrslt[temp_count][4] : AAestrslt[((temp_count-1) * inputParameter->AppScale + netlevel_temp)][4]*(inputParameter->Computation_Time[netlevel_temp-1]);
			AAAestrslt[temp_count][5] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][5];
			AAAestrslt[temp_count][6] = 0; //will update later
			AAAestrslt[temp_count][7] = AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][7];
			AAAestrslt[temp_count][8] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][8];
			AAAestrslt[temp_count][9] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][9];
			AAAestrslt[temp_count][10] += AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][10]*(inputParameter->Computation_Time[netlevel_temp-1]);
			for(int i = 11;i<19;i++)
				AAAestrslt[temp_count][i] = AAestrslt[((temp_count-1) * inputParameter->AppScale +netlevel_temp)][i];
		}
                                        
		//AAAestrslt(temp_count,3) =AAestrslt(((temp_count-1) * AppScale +1),3)*layer_computation_times(1);
		//AAAestrslt[temp_count][4] = AAAestrslt[temp_count][4]/(double)inputParameter->AppScale;
		//AAAestrslt[temp_count][6] = AAAestrslt[temp_count][6]/(double)inputParameter->AppScale;
		//AAAestrslt[temp_count][7] = AAAestrslt[temp_count][7]/(double)inputParameter->AppScale;
		//for(int i=10;i<=18;i++)
		//	AAAestrslt[temp_count][i] = AAAestrslt[temp_count][i]/(double)inputParameter->AppScale;

		//AAAestrslt[temp_count][4] = max1(((temp_count-1) * inputParameter->AppScale+1),((temp_count-1) * inputParameter->AppScale+inputParameter->AppScale),4);
		if (AAAestrslt[temp_count][target+1] < mintarget[target-1]){
			mintarget[target-1] = AAAestrslt[temp_count][target+1];
			mincount = temp_count;
		}
		/*
		for (int target_tt=2;target_tt<=6;target_tt++)
            if (AAAestrslt[temp_count][6]>1)
                break;
            else if (AAAestrslt[temp_count][target_tt] < mintarget[target_tt]) {
                mintarget[target_tt] = AAAestrslt[temp_count][target_tt];
                mincount[target_tt] = temp_count;
			}*/
	}

	double optresult[17];
	optresult[0] = AAAestrslt[mincount][0];
	for (int i=1;i<6;i++)
		optresult[i] = AAAestrslt[mincount][i+1];
	for (int i=6;i<17;i++)
		optresult[i] = AAAestrslt[mincount][i+2];


	/*double optresult[10][18];
	if (count_my>2) {
		for(int i=2;i<=6;i++)
			for(int j=2;j<=18;j++)
				optresult[i-1][j-1] = AAAestrslt[mincount[i]][j];
		for(int i=1;i<=5;i++)
			for(int j=1;j<=3;j++)
				optresult[i][j] = optresult[i][j]*1e6;*/	
		//unit: nm
		//the data in the optresult[1,2,...] are area,energy,latency,power,accuracy,area_multi,power_multi,latency_multi,read_sep,adposition,bit_level,adderposition,pulseposition,linetech,celltype,xbarsize
	

	ofstream fout;
	fout.open(outputFileName,ios::out);
	if(!fout.is_open())
		cout<<"result.txt cannot be found!"<<endl;
	else {
		fout<<"xbarnumber:"<<optresult[0]<<endl;
		fout<<"area:"<<optresult[1]<<endl;
		fout<<"energy:"<<optresult[2]<<endl;
		fout<<"latency:"<<optresult[3]<<endl;
		fout<<"power:"<<optresult[4]<<endl;
		fout<<"accuracy:"<<optresult[5]<<endl;
		fout<<"area_multi:"<<optresult[6]<<endl;
		fout<<"power_multi:"<<optresult[7]<<endl;
		fout<<"latency_multi:"<<optresult[8]<<endl;
		fout<<"read_sep:"<<optresult[9]<<endl;
		fout<<"adposition:"<<optresult[10]<<endl;
		fout<<"bit_level:"<<optresult[11]<<endl;
		fout<<"adderposition:"<<optresult[12]<<endl;
		fout<<"pulseposition:"<<optresult[13]<<endl;
		fout<<"linetech:"<<optresult[14]<<endl;
		fout<<"celltype:"<<optresult[15]<<endl;
		fout<<"xbarsize:"<<optresult[16]<<endl;

	}
	

	toc=clock();
    cout<<"Run time: "<<(double)(toc-tic)/CLOCKS_PER_SEC<<"S"<<endl;
	delete inputParameter;
	delete AAestrslt;
	delete AAAestrslt;
	delete technology;
	return 0;
}

void equal(double netlevel,double area,double energy,double latency,double power,double accuracy,double area_multi,double power_multi,double latency_multi,double read_sep,double adposition,double bit_level,double adderposition,double pulseposition,double linetech,double celltype,double xbarsize) {
	AAestrslt[count_my][0] = netrow * netcolumn;
	AAestrslt[count_my][1] = netlevel;
	AAestrslt[count_my][2] = area;
	AAestrslt[count_my][3] = energy;
	AAestrslt[count_my][4] = latency;
	AAestrslt[count_my][5] = power;
	AAestrslt[count_my][6] = accuracy;
	AAestrslt[count_my][7] = d1;
	AAestrslt[count_my][8] = area_multi;
	AAestrslt[count_my][9] = power_multi;
	AAestrslt[count_my][10] = latency_multi;
	AAestrslt[count_my][11] = read_sep;
	AAestrslt[count_my][12] = adposition;
	AAestrslt[count_my][13] = bit_level;
	AAestrslt[count_my][14] = adderposition;
	AAestrslt[count_my][15] = pulseposition;
	AAestrslt[count_my][16] = linetech;
	AAestrslt[count_my][17] = celltype;
	AAestrslt[count_my][18] = xbarsize;
}

double max1(int a,int b,int c) {
	double i;
	int j;
	i=AAestrslt[b][4];
	for(j=b;j<a;j++)
		if(AAestrslt[j][4]>i)
			i=AAestrslt[j][4];
	return i;
}

