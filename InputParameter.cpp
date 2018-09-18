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
    int filelength = 0;						
	int j = 0;
	string temp;
    fin.open(filename,ios::in);
	if(!fin.is_open())
		cout<<"SimConfig.txt cannot be found!"<<endl;
    while(fin.good() && !fin.eof()){
        getline(fin,temp);
        filelength++;
    }
    cfgtxt = new string[filelength];
    fin.clear();
    fin.seekg(0,ios::beg);
    for (i=0;i<filelength;i++)
    {
    	getline(fin,temp);
    	cfgtxt[i] = temp;
    }
    int config_begin,config_end;
    bool flag = true;
    i = 0;
    while(flag){
    	if(cfgtxt[i].find("config")!=string::npos){
    		config_begin = i;
            j = i;
    		while(1){
                if (cfgtxt[j].find("}")!=string::npos){
    				config_end = j;
                    break;
                }
                else j++;
    		}
            flag = false;
    	}
        i++;
    }

	for (i=config_begin;i<=config_end;i++){
		if(cfgtxt[i].find("Simulation_Level")!=string::npos)      
            SimLv.assign(cfgtxt[i],sizeof("Simulation_Level"),cfgtxt[i].length()-sizeof("Simulation_Level"));   
        else if(cfgtxt[i].find("Target_Outputs")!=string::npos)
            Target_Output.assign(cfgtxt[i],sizeof("Target_Outputs"),cfgtxt[i].length()-sizeof("Target_Outputs"));
        else if(cfgtxt[i].find("Application ")!=string::npos)
            Application.assign(cfgtxt[i],sizeof("Application"),cfgtxt[i].length()-sizeof("Application"));
       	else if(cfgtxt[i].find("Application_Scale")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Application_Scale"),temp.length()-sizeof("Application_Scale")); 
			AppScale = std::stoi (temp,nullptr,0);
		}
		else if(cfgtxt[i].find("Weight_Polarity")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Weight_Polarity"),temp.length()-sizeof("Weight_Polarity")); 
			WeightPolar = std::stoi (temp,nullptr,0);
		}
		else if(cfgtxt[i].find("Cell_Type")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Cell_Type"),temp.length()-sizeof("Cell_Type"));
			stringstream stream(temp);
			stream>>minCell;
			maxCell=minCell;
		}
		else if(cfgtxt[i].find("RRAM_Model")!=string::npos)
            RRAMModel.assign(cfgtxt[i],sizeof("RRAM_Model"),cfgtxt[i].length()-sizeof("RRAM_Model"));
        else if(cfgtxt[i].find("RRAM_Bit_Levels")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("RRAM_Bit_Levels"),temp.length()-sizeof("RRAM_Bit_Levels")); 
			minBtLv = std::stoi (temp,nullptr,0);
			maxBtLv=minBtLv;
		}
		else if(cfgtxt[i].find("Transistor_Tech(nm)")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Transistor_Tech(nm)"),temp.length()-sizeof("Transistor_Tech(nm)")); 
			TranTech = std::stoi(temp,nullptr,0);
		}
		else if(cfgtxt[i].find("Min_Crossbar_Size")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Min_Crossbar_Size"),temp.length()-sizeof("Min_Crossbar_Size")); 
			minXbarSize = std::stoi(temp,nullptr,0);
		}
		else if(cfgtxt[i].find("Max_Crossbar_Size")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Max_Crossbar_Size"),temp.length()-sizeof("Max_Crossbar_Size")); 
			maxXbarSize = std::stoi(temp,nullptr,0);
		}
		else if(cfgtxt[i].find("Write_Method")!=string::npos)
            WriteMth.assign(cfgtxt[i],sizeof("Write_Method"),cfgtxt[i].length()-sizeof("Write_Method"));
        else if(cfgtxt[i].find("Line_Tech")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Line_Tech"),temp.length()-sizeof("Line_Tech")); 
			minLine = std::stoi(temp,nullptr,0);
			maxLine = std::stoi(temp,nullptr,0);
		}
		else if(cfgtxt[i].find("Action_Type ")!=string::npos)
            Action_type.assign(cfgtxt[i],sizeof("Action_Type"),cfgtxt[i].length()-sizeof("Action_Type"));
        else if(cfgtxt[i].find("Pipeline")!=string::npos){
            temp.assign(cfgtxt[i],sizeof("Pipeline"),temp.length()-sizeof("Pipeline"));
            Pipeline = std::stoi(temp,nullptr,0);
        }
	}

	ComputationTime = new int[AppScale];
	OutputChannel = new int [AppScale];
	InputLength = new int [AppScale];
	int temp_inputsize = 0;
	int temp_outputsize = 0;
	int temp_kernelsize = 0;
	int temp_inputchannel = 0;
	int temp_outputchannel = 0;
	int temp_inputlength = 0;
	int temp_outputlength = 0;
	int layer_type = 0;
	int layer_begin = config_end;//begin to search from the end of the config
	int layer_end = config_end;
	for (i=0;i<AppScale;i++){
		flag = true;
		j = layer_end;
		while(flag){
			if(cfgtxt[j].find("Layer"+to_string(i+1))!=string::npos){
				layer_begin = j;
				while(1){
                	if (cfgtxt[j].find("}")!=string::npos){
    					layer_end = j;
                    	break;
                	}
                	else j++;
    			}
    			flag = false;
			}
			else
				j++;
		}
		layer_type = 0;
		for(j=layer_begin;j<layer_end;j++){
            //cout<<"layer"<<i<<"FC"<<cfgtxt[j].find("FC")<<endl;
            //cout<<"layer"<<i<<"Conv"<<cfgtxt[j].find("Conv")<<endl;
            //cout<<endl;
			if(cfgtxt[j].find("Conv")!=string::npos){//this layer is a conv layer
				layer_type = 1;
				break;
			}
			else if(cfgtxt[j].find("FC")!=string::npos){
				layer_type = 2;
				break;
			}

		}
		if(layer_type == 1){
			for(j=layer_begin;j<=layer_end;j++){
				if(cfgtxt[j].find("Outputsize")!=string::npos){
					temp.assign(cfgtxt[j],sizeof("Outputsize"),temp.length()-sizeof("Outputsize")); 
					temp_outputsize = std::stoi(temp,nullptr,0);
				}
				else if(cfgtxt[j].find("Kernelsize")!=string::npos){
					temp.assign(cfgtxt[j],sizeof("Kernelsize"),temp.length()-sizeof("Kernelsize")); 
					temp_kernelsize = std::stoi(temp,nullptr,0);
				}
				else if(cfgtxt[j].find("Inputchannel")!=string::npos){
					temp.assign(cfgtxt[j],sizeof("Inputchannel"),temp.length()-sizeof("Inputchannel")); 
					temp_inputchannel = std::stoi(temp,nullptr,0);
				}
				else if(cfgtxt[j].find("Outputchannel")!=string::npos){
					temp.assign(cfgtxt[j],sizeof("Outputchannel"),temp.length()-sizeof("Outputchannel")); 
					temp_outputchannel = std::stoi(temp,nullptr,0);
				}
			}
			ComputationTime[i] = temp_outputsize*temp_outputsize;
			OutputChannel[i] = temp_outputchannel;
			InputLength[i] = temp_kernelsize*temp_kernelsize*temp_inputchannel;
		}
		else if(layer_type == 2){
			for(j=layer_begin;j<=layer_end;j++){
				if(cfgtxt[j].find("Inputlength")!=string::npos){
					temp.assign(cfgtxt[j],sizeof("Inputlength"),temp.length()-sizeof("Inputlength")); 
					temp_inputlength = std::stoi(temp,nullptr,0);
				}
				else if(cfgtxt[j].find("Outputlength")!=string::npos){
					temp.assign(cfgtxt[j],sizeof("Outputlength"),temp.length()-sizeof("Outputlength")); 
					temp_outputlength = std::stoi(temp,nullptr,0);
				}
			}
			ComputationTime[i] = 1;
			OutputChannel[i] = temp_outputlength;
			InputLength[i] = temp_inputlength;
		}
		else
			;
	}
    int hhhhhh=1;
    cout<<hhhhhh<<endl;
	/*
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
            j = 0;
            for (int ii=sizeof("Application_Scale");ii!=cfgtxt[i].length();ii++)

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
           ComputationTime=new int[AppScale];
           for(int ii=0;ii<AppScale;ii++)
               ComputationTime[ii]=0;
           for (int ii = sizeof("Computation_Time"); ii != cfgtxt[i].length(); ++ii)
               if (cfgtxt[i].at(ii)>='0' && cfgtxt[i].at(ii)<='9')
                   ComputationTime[j] =cfgtxt[i].at(ii)-'0'+ComputationTime[j]*10;
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
	}*/
}


