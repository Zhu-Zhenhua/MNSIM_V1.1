#include"global.h"
#include"function.h"
#include"formula.h"
#include<math.h>
double accuracy, d1;
void accuracy_c(int xbarsize,int linetech,int sig_bit,int cell_bit,int resis_range,double input_err){
	double cc[4] = {-0.005376,1.278,8.957,1.451e-6};
	double rline[5] = {0,12.681000000000000,6.607000000000000,3.928000000000000,2.177000000000000};
	double a =      -1.113  ;
	double b =   -0.004209  ;
	double c =       24.74  ;
	double d =        83.3  ;
	double e =       83.07  ;
	double f =   1.427e-06  ;
	double g =       1.395  ;
	double h =       10.62  ;
	double r_line;
    switch (linetech){
        case 0:
            r_line = 0;break;
		case 18:
            r_line = rline[1];break;
		case 22:
            r_line = rline[2];break;
		case 28:
            r_line = rline[3];break;
		case 36:
            r_line = rline[4];break;
        default:
            r_line = 54.21/(-13.73+linetech);break;
	}
	double y0;
    y0 = (b*r_line*xbarsize+a)*xbarsize/(c+d*r_line*xbarsize+e*xbarsize)+ f*r_line*xbarsize*xbarsize+g/(h+xbarsize);
    accuracy = (1+y0)*(1+input_err)-1;
    //a = 0:2^sig_bit-1;
    //d1 = sum(floor(a*accuracy+0.5))/2^sig_bit/(2^sig_bit-1);  another accuracy precision
	double temp1=1;
	for(int i=0;i<sig_bit;i++)
		temp1=temp1*2;
	double sum=0;
	for(double i=0;i<=temp1-1;i++){
		sum=sum+floor(i*accuracy+0.5);
	}
	d1=sum/(temp1)/(temp1-1);
    
//     c(1)+c(2)./(c(3)+xbarsize) + c(4)*xbarsize^2 .*r_line;
//    flags = 1;
}