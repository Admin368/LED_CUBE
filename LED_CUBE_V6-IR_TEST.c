#include<reg52.h>
#include "IR_API\infraredRemConApi.c"
#include "paulobetaX.h"
#define uchar unsigned char
uchar button;//variable that stores value of button
void buttonCheck();//action to be done based on button
void displayNumber(){
	xled(button);
	if(button<10){
		xsegment(1);
		xdigit(button);
	}
	else if(button>10){
		xsegment(1);
		xdigit(button/10);
		xdelay(1);
		xsegment(2);
		xdigit(button%10);
	}
}
void main()
{
	initInfraredRemCon();
	button = 0;
	while(1)
	{
		buttonCheck();
		displayNumber();
	}
}

void buttonCheck(){
		button = irCodeDecoder();
		switch(button)
		{
			case 0://CH-

				break;
			case 1://CH
				break; 
			case 2://CH+
				break;
			case 3://PREV     
				break;; 
			case 4://NEXT

				break;
			case 5://PLAY/PAUSE

				break; 
			case 6://VOL-

				break;  
			case 7://VOL+

				break;  
			case 8://EQ [DONT WORK WELL]  

				break;
			case 9://0
				break; 
			case 10://100+ [DONT WORK WELL]  
				break;
			case 11://200+ [DONT WORK WELL]     
				break;; 
			case 12: //1

				break;
			case 13://2

				break; 
			case 14://3

				break;  
			case 15://4

				break;
			case 16://5

				break;
			case 17://6
				break; 
			case 18://7
				break;
			case 19://8   
				break;
			case 20://9
				break;           
			default: 
				break;       
		}	
}

