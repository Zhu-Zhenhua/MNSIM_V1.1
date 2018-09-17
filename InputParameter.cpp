#include "InputParameter.h"
#include<fstream>
#include<string>
#include <sstream>
#include<unistd.h>

InputParameter::InputParameter() {
	// TODO Auto-generated constructor stub
	AppScale = 0;
	rs = 3000;   
	cell_bit = 8;
	sig_bit = 8;
	rramtech = 32e-9;
	minXbarSize = 4;
	maxXbarSize = 1024;
	minCell = 1;
	maxCell = 1;
	minAdPos = 1;
	maxAdPos = 1;
	minBtLv = 0;
	maxBtLv = 16;
	minRRang = 1000;
	maxRRang = 1000000;
	minAdder = 0;
	maxAdder = 0;
	minLine = 22;
	maxLine = 90;
}
InputParameter::~InputParameter() {
	// TODO Auto-generated destructor stub
}
void InputParameter::ReadInputParameterFromFile(string filename){
    ifstream fin;
    int i = 0;						
	int j = 0;
	string temp;
    fin.open(filename,ios::in);
	if(!fin.is_open())
		cout<<"SimConfig.txt cannot be found!"<<endl;
    while(fin.good() && i < 24){           
		if(i<6)								//do not read the first 4 rows
			getline(fin,temp);
        else{
			getline(fin,temp);
			if(temp=="")					//do not read void row
				continue;
			cfgtxt[i-6]=temp;
			}
		i++;
	}
	for(i=0;i<18;i++){						
        if(cfgtxt[i].find("Simulation_Level")!=string::npos)      
            SimLv.assign(cfgtxt[i],sizeof("Simulation_Level"),cfgtxt[i].length()-sizeof("Simulation_Level"));   

        else if(cfgtxt[i].find("Target_Outputs")!=string::npos)
            Target_Output.assign(cfgtxt[i],sizeof("Target_Outputs"),cfgtxt[i].length()-sizeof("Target_Outputs"));

        else if(cfgtxt[i].find("Application ")!=string::npos){
            Application.assign(cfgtxt[i],sizeof("Application"),cfgtxt[i].length()-sizeof("Application"));
        }

        else if(cfgtxt[i].find("Action_Type ")!=string::npos){
            Action_type.assign(cfgtxt[i],sizeof("Action_Type"),cfgtxt[i].length()-sizeof("Action_Type"));
        }

        else if(cfgtxt[i].find("Application_Scale")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Application_Scale"),temp.length()-sizeof("Application_Scale")); 
			stringstream stream(temp);					
			stream>>AppScale;
		}
        else if(cfgtxt[i].find("Network_Scale")!=string::npos){
			NetScale=new int[AppScale*2];
			j = 0;
			for(int ii=0;ii<AppScale*2;ii++)
				NetScale[ii]=0;
			for (int ii = sizeof("Network_Scale"); ii != cfgtxt[i].length(); ++ii)
				if (cfgtxt[i].at(ii)>='0' && cfgtxt[i].at(ii)<='9')
					NetScale[j] =cfgtxt[i].at(ii)-'0'+NetScale[j]*10;
				else
					j++;
			}
		else if(cfgtxt[i].find("Computation_Time")!=string::npos){
			j = 0;
			Computation_Time=new int[AppScale];
			for(int ii=0;ii<AppScale;ii++)
				Computation_Time[ii]=0;
			for (int ii = sizeof("Computation_Time"); ii != cfgtxt[i].length(); ++ii)
				if (cfgtxt[i].at(ii)>='0' && cfgtxt[i].at(ii)<='9')
					Computation_Time[j] =cfgtxt[i].at(ii)-'0'+Computation_Time[j]*10;
				else
					j++;
			}
        else if(cfgtxt[i].find("Weight_Polarity")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Weight_Polarity"),temp.length()-sizeof("Weight_Polarity")); 
			stringstream stream(temp);
			stream>>WeightPolar;
		}
		else if(cfgtxt[i].find("Cell_Type")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Cell_Type"),temp.length()-sizeof("Cell_Type"));
			stringstream stream(temp);
			stream>>minCell;
			maxCell=minCell;
		}
		else if(cfgtxt[i].find("RRAM_Model")!=string::npos){
            RRAMModel.assign(cfgtxt[i],sizeof("RRAM_Model"),cfgtxt[i].length()-sizeof("RRAM_Model"));
		}

		else if(cfgtxt[i].find("RRAM_Bit_Levels")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("RRAM_Bit_Levels"),temp.length()-sizeof("RRAM_Bit_Levels")); 
			stringstream stream(temp);
			stream>>minBtLv;
			maxBtLv=minBtLv;
		}
		else if(cfgtxt[i].find("Transistor_Tech(nm)")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Transistor_Tech(nm)"),temp.length()-sizeof("Transistor_Tech(nm)")); 
			stringstream stream(temp);
			stream>>TranTech;
		}
		else if(cfgtxt[i].find("Line_Tech")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Line_Tech"),temp.length()-sizeof("Line_Tech")); 
			stringstream stream(temp);
			stream>>minLine;
			stream>>maxLine;
		}
		else if(cfgtxt[i].find("Min_Crossbar_Size")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Min_Crossbar_Size"),temp.length()-sizeof("Min_Crossbar_Size")); 
			stringstream stream(temp);
			stream>>minXbarSize;
		}
		else if(cfgtxt[i].find("Max_Crossbar_Size")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Max_Crossbar_Size"),temp.length()-sizeof("Max_Crossbar_Size")); 
			stringstream stream(temp);
			stream>>maxXbarSize;
		}
        else if(cfgtxt[i].find("Write_Method")!=string::npos)
            WriteMth.assign(cfgtxt[i],sizeof("Write_Method"),cfgtxt[i].length()-sizeof("Write_Method"));

        else if(cfgtxt[i].find("Pipeline")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Pipeline"),temp.length()-sizeof("Pipeline"));
            stringstream stream(temp);
			stream>>Pipeline;
        }
	}
}


