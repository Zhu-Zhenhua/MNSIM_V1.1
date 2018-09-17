#include"function.h"
double xbar_area,techwl,ad_area,da_area,adder_area,pulse_area,decoder_area,read_area,write_area,Sub_area,area_u;
void unit_area_c(Technology technology,int celltype,int xbarsize,int adposition,int adderposition,int pulseposition,int sig_bit,int application,double rramtech,int read_seperate){
	Cal_Adder Cal_Adder_temp(technology,sig_bit);
	Cal_Decoder Cal_Adder_Decoder(technology,celltype,xbarsize);
	if (read_seperate == 0){
		if (celltype == 0)
			xbar_area = xbarsize*xbarsize* 4 * rramtech*rramtech;
		else{
			techwl=calWL(tech);
			xbar_area = xbarsize*xbarsize * (3 * techwl +1) * rramtech*rramtech;
		}
		ad_area = adposition * (adsize(technology.featureSizeInNano,sig_bit)) * xbarsize;
		da_area = adposition * (dasize(technology.featureSizeInNano,sig_bit)) * xbarsize;
		adder_area = adderposition * Cal_Adder_temp.Adder_Area() * xbarsize;
		pulse_area = pulseposition * pulsesize(technology.featureSizeInNano);
		//if (celltype == 0)
			//decoder_area = bl_decoder_size(technology.featureSizeInNano,celltype,xbarsize) + sl_decoder_size(technology.featureSizeInNano,celltype,xbarsize);
		//else
			//decoder_area = bl_decoder_size(technology.featureSizeInNano,celltype,xbarsize) + sl_decoder_size(technology.featureSizeInNano,celltype,xbarsize) + wl_decoder_size(technology.featureSizeInNano,celltype,xbarsize);
		decoder_area =  Cal_Adder_Decoder.Decoder_Area(Cal_Adder_Decoder.num_in);

		//
		read_area = readsize(technology.featureSizeInNano) * xbarsize;
		write_area = writesize(technology.featureSizeInNano,celltype);
		

		//what does flag mean??
		if (application ==0){
			Sub_area =  Cal_Adder_temp.Adder_Area() * xbarsize;
			area_u = xbar_area*2 + ad_area*2 + da_area + adder_area + pulse_area + decoder_area +read_area + write_area + Sub_area;
			flags[0]=xbar_area*2;flags[1]=ad_area*2;flags[2]=da_area+read_area;flags[3]=adder_area+Sub_area+pulse_area+decoder_area+write_area;
			//    flags = 1;
		}
		else{
			area_u = xbar_area + ad_area + adder_area + pulse_area + decoder_area +read_area + write_area;//adda_area not defined, change to ad_area
			flags[0] = 1;
		}
	}
	else{		// seperate
		////// what the differences between seperate and non_seperate
		if (celltype == 0)
			xbar_area = xbarsize*xbarsize * 4 * rramtech*rramtech;
		else{
			techwl=calWL(technology.featureSizeInNano);
			xbar_area = xbarsize*xbarsize * (3 * techwl +1) * rramtech*rramtech;
		}
		ad_area = adposition * (adsize(technology.featureSizeInNano,sig_bit)) *read_seperate;
		da_area = adposition * (dasize(technology.featureSizeInNano,sig_bit)) * xbarsize;
		adder_area = adderposition *  Cal_Adder_temp.Adder_Area() *read_seperate;
		pulse_area = pulseposition * pulsesize(technology.featureSizeInNano);
		//if (celltype == 0)
		//	decoder_area = bl_decoder_size(technology.featureSizeInNano,celltype,xbarsize) + sl_decoder_size(technology.featureSizeInNano,celltype,xbarsize);
		//else
		//	decoder_area = bl_decoder_size(technology.featureSizeInNano,celltype,xbarsize) + sl_decoder_size(technology.featureSizeInNano,celltype,xbarsize) + wl_decoder_size(technology.featureSizeInNano,celltype,xbarsize);
		decoder_area =  Cal_Adder_Decoder.Decoder_Area(Cal_Adder_Decoder.num_in);
		read_area = readsize(technology.featureSizeInNano) *read_seperate;
		write_area = writesize(technology.featureSizeInNano,celltype);
    
		if (application ==0){
			Sub_area =  Cal_Adder_temp.Adder_Area()*read_seperate ;
			area_u = xbar_area*2 + ad_area*2 + da_area + adder_area + pulse_area + decoder_area +read_area + write_area + Sub_area;
			flags[0]=xbar_area*2;flags[1]=ad_area*2;flags[2]=da_area+read_area;flags[3]=adder_area+Sub_area+pulse_area+decoder_area+write_area;
		}
		else{
			area_u = xbar_area + ad_area + adder_area + pulse_area + decoder_area +read_area + write_area;
			flags[0] = 1;
		}
	}
	//return area_u;
}
