#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned char
int mode1;
int newRow;
int newCol;
int nextColor;

uchar ledOut;
uchar delay1;
uchar row;
uchar col;
uchar shiftDirection;
sbit X_R0 = P1^0;
sbit X_R1 = P1^1;
sbit X_R2 = P1^2;
sbit X_R3 = P1^3;
sbit X_R4 = P1^4;
sbit X_R5 = P1^5;
sbit X_R6 = P1^6;
sbit X_R7 = P1^7;

sbit X_B0 = P0^0;
sbit X_B1 = P0^1;
sbit X_B2 = P0^2;
sbit X_B3 = P0^3;
sbit X_B4 = P0^4;
sbit X_B5 = P0^5;
sbit X_B6 = P0^6;
sbit X_B7 = P0^7;

sbit Z_A0 = P2^0;
sbit Z_A1 = P2^1;
sbit Z_A2 = P2^2;
sbit Z_A3 = P2^3;
sbit Z_B0 = P2^4;
sbit Z_B1 = P2^5;
sbit Z_B2 = P2^6;
sbit Z_B3 = P2^7;

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}

void delay(uchar max_dly){
	uchar dly;
	for(dly=0;dly<max_dly;dly++){
		Delay10ms();
	}
}
uchar shift(uchar shiftInput){
		uchar shiftedBit = _crol_(shiftInput,shiftDirection);
		return shiftedBit;
}
void setRow(int newRow){
	if(newRow<1){newRow=1;}
	if(newRow>4){newRow=4;}
	switch(newRow){
		case 1:
						row = 0xee;
						break;
		case 2:
						row = 0xdd;
						break;
		case 3:
						row = 0xbb;
						break;
		case 4:
						row = 0x77;
						break;
		default:
						break;
	}
}
void setNewRow(){
	newRow++;
	if(newRow>4){newRow = 1;}
	setRow(newRow);
}
void setCol(int newCol){
	if(newCol<1){newCol=1;}
	if(newCol>4){newCol=4;}
	switch(newCol){
		case 1:
						P1 = col = 0x88;
						break;
		case 2:
						P1 = col = 0x44;
						break;
		case 3:
						P1 = col = 0x22;
						break;
		case 4:
						P1 = col = 0x11;
						break;
		default:
						break;
	}
}
void setNewCol(){
	newCol++;
	if(newCol>4){newCol = 1;}
	setCol(newCol);
}
void changeColor(int color){
	switch(color){
		case 0://blue
			P0 = 0xff;
			P1 = 0x00;
			break;
		case 1://red
            P0 = 0x00;
			P1 = 0xff;
			break;
		case 2://purple
            P0 = 0xff;
			P1 = 0xff;
			break;
	}
}
void setNextColor(){
		nextColor++;
		if(nextColor>2){nextColor = 0;}
		changeColor(nextColor);
}

void changeMode(int mode){
	int total_modes = 6;
	if(mode<0){mode=0;}
	if(mode>total_modes){mode=total_modes;}
	switch(mode){
		case 0://stop motion
			shiftDirection = 0;
			break;
		case 1://rise up
			//newRow = 0;
			//setRow(0);
			shiftDirection = 1;
			break;
		case 2://go down
			//setRow(4);
			shiftDirection = -1;
			break;
		case 4:
			setCol(3);
			//setRow(1)
			//row = 0x01;
			break;
		case 5:
			row = 0x0e;
			break;
		case 6:
			setCol(3);
			//row = 0xf3;
			break;
	}
}
void setColumn(){
}
////////////////////INTERUPT/////////////////////////////////////////
uchar seconds = 0;
uchar count,last_seconds,last_seconds;///////////////////////
uchar flag=1;uchar flag_inverse=~1;//////////////////////////////////
void timer_reload(){TH0=(65536-46082)/256;TL0=(65536-46082)%256;}////
void init_timer(){TMOD=0x01;timer_reload();TR0=1;}///////////////////
void init_interupt(){EA=1;ET0=1;}////////////////////////////////////
////////////////////INTERUPT/////////////////////////////////////////
void timer_0_ISR() interrupt 1{
	timer_reload();
	count++;
	if(count==20){
		flag=~flag;
		last_seconds=seconds;
		seconds++;
		count=0;
		if(seconds>100){seconds=0;}
	}
}//IF 1 SECOND////
/////////////////////////////////////////////////////////////////////
void init(){
		P0 = 0;
		P1 = 0;
		//row = 0xff;
		delay1=0;
		setRow(1);
		nextColor = 0;
        changeColor(0);
        changeMode(0);
		init_timer();
		init_interupt();
}
void led(int colorIn,int ledIn){
    int index = ledIn;
    if(index<1){index=0;}//resets index if less than 0
    if(index>64){index=64;}//resets index if greater than 64
    if(index>0&&index<=8){P2=0xfe;}//row 1.1
    if(index>8&&index<=16){P2=0xef;}//row1.2
    if(index>16&&index<=24){P2=0xfd;}//row2.1
    if(index>24&&index<=32){P2=0xdf;}//row2.2
    if(index>32&&index<=40){P2=0xfb;}//row3.1
    if(index>40&&index<=48){P2=0xbf;}//row3.2
    if(index>48&&index<=56){P2=0xf7;}//row4.1
    if(index>56&&index<=64){P2=0x7f;}//row4.2
    index = index%16;//all leds are in 16 sets
    ledOut = 0x01;// resets bin to 0000 0001
    /// so that we can shift it using crol 
    /// on the 16 positions available
    switch(colorIn)
    {
    case 1://blue
        P0 = _crol_(ledOut,(index-1));
        P1 = 0;
        break;
    case 2://red
        P0 = 0;
        P1 = _crol_(ledOut,(index-1));
        break;
    case 3://purple
        P0 = _crol_(ledOut,(index-1));
        P1 = _crol_(ledOut,(index-1));
        break;
    default:
        break;
    }
}
int main(){
    int l=1;//led
    int c=1;//color
	init();
	while(2){
        P1=0x00;
        led(c,l);
        delay(1);
        l++;if(l>64){l=1;c++;if(c>3){c=1;}}
	}
}