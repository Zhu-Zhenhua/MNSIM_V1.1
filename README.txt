                              MNSIM version1.1 ReadMe

=========================================================================================

---------------------------------Update Information--------------------------------------
1. Update the input parameters settings.
2. Fix several bugs.

----------------------------------Running MNSIM------------------------------------------
1. Windows / MacOS:
        Create a project with all of the source files, set simulation configuration file 
        (sim-config) and output results file address in argv[];
    Linux:
        Build the project with $ make. If no sim-config and result files are specified, 
        MNSIM will load the default (SimConfig.txt and result.txt), run MNSIM with $ ./MNSIM. 
        If users specify their own configurations / result file by passing the ".txt" 
        argument:$ ./MNSIM <simconfig>.txt <result>.txt

2. Input Parameters Setting (MNSIM version 1.1):
*****************************************************************************************

Config part:

    Simulation_Level: Estimation													   	
    Target_Outputs: Area/Latency/Power/Energy (Optimization Targets)				   
    Application: CNN or BNN

    Application_Scale: Number of Layers (conv + fully-connected)					   											   	
    Weight_Polarity: 2															   	
    Cell_Type: 1T1R																   	
    RRAM_Model: ideal															       	
    RRAM_Bit_Levels: 8															   	
    Transistor_Tech(nm): 130														   	
    Min_Crossbar_Size & Max_Crossbar_Size: 2^k, MNSIM will find the optimal design   
    Max_Crossbar_Size 1024														   		
    Write_Method: ideal															   		
    Line_Tech:[18,22,28,36,45,65,90]												   	
    Action_Type: Calculation														   	
    Pipeline: 0-not pipelined, 1-pipelined	

Network part:

    #: Layer number, from 1 to Application_Scale	
    
    Convolutional Layer:
    Layer# {
        Name Conv
        Inputsize: input feature map size
        Outputsize: output feature map size
        Kernelsize
        Stride
        Inputchannel
        Outputchannel
    }			
    Fully-connected Layer:
    Layer# {
        Name FC
        Inputlength
        Outputlength
    }				   	
*****************************************************************************************
3. Unit of the outputs:
	area: m^2,
	energy: J,
	power: W,
	latency: s.


----------------------------------Future Work and Update---------------------------------
1. Support for different cell types: 0T1R and 1T1R	
2. Support for different bit levels of RRAM
3. Add accuracy simulation of matrix-vector multiplications and CNN

=========================================================================================

MNSIM version1.1 is only a test version. If you have any questions and suggestions about
MNSIM please contact us via email.

Lixue Xia: xialx13@tsinghua.org.cn
Zhenhua Zhu: zhuzhenh18@mails.tsinghua.edu.cn


