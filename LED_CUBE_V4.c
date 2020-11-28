/*
ADD
- numbers
- add infa red
- ckeck for usb serial to pc
*/
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned char
int modes;
int mode1;
int modeSet;
int modeMax=12;// number of modes
int newRow;
int newCol;
int nextColor;

int l;//led
int c;//color
int seed1;//random value 1
int seed2;//random value 2

code int circle[]={1,2,3,4,8,12,16,15,14,13,9,5,1,17,18,19,20,24,28,32,31,30,29,25,21,17,33,34,35,36,40,44,48,47,46,45,41,37,33,49,50,51,52,56,60,64,63,62,61,57,53,49};
xdata int circleIndex = 0;
xdata int circleMax = 52;
xdata int cVar = 1; //circle random variable

uchar ledOut;
uchar delay1;
uchar row;
uchar col;
uchar shiftDirection;

uchar isAutoModeOn; // if 1 is on , 0 if off 

int var1=0;
int var2=0;
int var3=0;
int var4=0;
sbit buzzer = P3^0;
sbit button1 = P3^4;
sbit button2 = P3^5;
sbit button3 = P3^6;
sbit button4 = P3^7;

int test1 = 0;
void Delay1ms()//@11.0592MHz
{unsigned char i, j;_nop_();
_nop_();_nop_();
i = 11;j = 190;
do{while (--j);}
while (--i);}
void delay(uchar max_dly){
	uchar dly;
	//if(max_dly<0){max_dly=0;}//dont let delay go below 0
	for(dly=0;dly<max_dly;dly++){
		Delay1ms();
	}
}
void delayX(unsigned char delayIn){
	unsigned char i,j,k,y;
	for(k=0;k<delayIn;k++){
		for(i=0;i>120;i++){
			for(j=0;j<120;j++){
				for(y=0;y<120;y++){}
			}
		}
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
		if(nextColor<0){nextColor = 2;}
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
		case 1:
			shiftDirection = 1;
			break;
		case 2://go down
			shiftDirection = -1;
			break;
		case 4:
			setCol(3);
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
	if(count%20==0){//IF 1 SECOND////
		flag=~flag;
		last_seconds=seconds;
		seconds++;
		//count=0;
		modes++;
		if(seconds>200){seconds=0;}
	}
	if(count>210){count=0;}
    if(seconds>60){seconds=0;}
}
/////////////////////////////////////////////////////////////////////
void init(){
		l=1;//variable used as led#
		c=1;//variable used as color (0-3)
		P0=0;
		P1=0;
        P3=1;//set all buttons to high, they turn 0 when presses
        isAutoModeOn = 1; //if 1 = on , if 0 = off;
		modes=0;
		seed1=0;//random varriable that counts from 0-64
		seed2=64;//random varriable that counts from 0-64
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
	int colorIndex = colorIn;
	if(colorIndex<1){colorIndex=1;}
	if(colorIndex>3){colorIndex=3;}
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
    switch(colorIndex)
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
void resetVariable(){
	seed1++;if(seed1>64){seed1=0;}
	if(seed1<0){seed1=64;}
	seed2--;if(seed1<0){seed1=64;}
	if(seed1>64){seed1=0;}
    l++;if(l>64){l=1;c++;if(c>3){c=1;}}
}

void action(int modeIn);//declaring it, code at bottom
void autoMode(){
	action(modes);
	if(modes>modeMax){modes=0;}
}
void allLights(int colorIn){
    for(seed1=1;seed1<5;seed1++){
            changeColor(colorIn);
            setRow(seed1);
            //P2 = 0x00;
            P2 = row;
            delayX(30);
        }
}
int main(){
	init();
    modeSet = 0;
    button1 = 1;
    button2 = 1;
    button3 = 1;
    buzzer = 0;
	while(1 ){
		//led(c,56);
        if(isAutoModeOn==1){autoMode();}
        else if(isAutoModeOn==0){action(modeSet);}

        if(button1==0){//prev mode button
            delay(1);
                while(button1==0){//verifying button press
                    if(isAutoModeOn==1){modeSet=modes;}//copies value of current mode while in auto
                    isAutoModeOn=0;//disables automode
                    buzzer =1;//BUZZER SOUND
                    action(modeSet);
                }
                buzzer = 0;
                modeSet--;
                if(modeSet<0){modeSet=modeMax;}
        }
        if(button2==0){//next mode button
            delay(1);
                while(button2==0){//verifying button press
                    if(isAutoModeOn==1){modeSet=modes;}//copies value of current mode while in auto
                    isAutoModeOn=0;//disables automode
                    buzzer =1;
                    action(modeSet);
                }
                buzzer = 0;
                modeSet++;
                if(modeSet>modeMax){modeSet=0;}
        }
		resetVariable();
        if(button3==0){//AUTO MODE ON
            delay(1);
                while(button3==0){
                    if(isAutoModeOn==0){modes=modeSet;}
                    isAutoModeOn =1;
                    action(10);
                    //autoMode();
                    //allLights(2);
                    buzzer = 1;
                }
                buzzer = 0;
        }
	}
}
/*
0.
i=100;c=1;led(c,54);delayX(i);led(c,55);delayX(i);led(c,58);delayX(i);
led(c,59);delayX(i);led(c,38);delayX(i);led(c,39);delayX(i);led(c,42);
delayX(i);led(c,43);delayX(i);led(c,22);delayX(i);led(c,23);delayX(i);
led(c,26);delayX(i);led(c,27);delayX(i);

1.
i=100;c=1;led(c,54);delayX(i);led(c,58);delayX(i);led(c,38);delayX(i);
led(c,42);delayX(i);led(c,22);delayX(i);led(c,26);delayX(i);

2.

*/
void action(int modeIn){
	//seed is random value you can use
	int i;
	int ij;
	int ii;
	int delayi;
	switch (modeIn)
	{
	case 0:
        
		break;
	case 1:
		led(c,l);
        delay(1);
		break;
	case 2:
		led(c,l);
        delay(10);
		led(c,64-l);
        delay(10);
		break;
	case 3: // row no shift
		//changeColor(1);
		setNextColor();
		changeMode(0);
		P2 = row;
		delay(seed1);
		row=shift(row);
		//if(count%100==0){setNextColor();}
		break;
	case 4: //row shift upwards
		setNextColor();
		changeMode(1);
		P2 = row;
		delay(seed1);
		row=shift(row);
		//row=shift(row); //or u can use this
		break;
	case 5: //row shift downwards
		setNextColor();
		changeMode(2);
		P2 = row;
		delay(seed1);
		row=shift(row);
		//row=shift(row); //or you can use
		break;
	case 6:
		setNextColor();
		changeMode(1);
		P2 = row;
		delay(seed1%5);
		row=shift(row);
		break;	
	case 7:
		if(seed1>40){seed1=0;}
		if(seed2>3){seed2=1;}
		led((c),l);
        delay(seed1);
		led((c+1),64-l);
        delay(seed1);
		break;
	case 8:
		if(seed1>10){seed1=0;}
		if(seed2>3){seed2=1;}
		if(l>52){l=0;}
		led((c),l);
        delay(seed1);
		led((c+1),13+l);
        delay(seed1);
		led((c+1),27+l);
        delay(seed1);
		led((c+1),33+l);
        delay(seed1);
		led((c+1),11+l);
        delay(seed1);
		led((c+1),19-l);
        delay(seed1);
		led((c+1),39-l);
        delay(seed1);
		break;
	case 9:
        i = seed1*seed2;
        led(c,(i%64));
        delay(1);
		break;	
	case 10:
        allLights(seconds%3);
		break;
	case 11:
        setNextColor();
        i = (nextColor*l*c);
        led(c,i);
        delay(7);
        led(c+0,i%16);
        delay(7);
        led(c+1,i%24);
        delay(7);
        led(c+2,i%32);
        delay(7);
        led(c+3,i%48);
        delay(7);
        //delay(1);
		break;
    case 12:
        if(var1<1){var1=1;}//var1 used for color
        circleIndex=circleIndex+cVar;
        if(circleIndex>42){
            //circleIndex=0;
            //setNextColor();
            var1++;//used for color
            if(var1>3){var1=1;}
            cVar = -1;
        }
        if(circleIndex<3){cVar=1;}
        led(var1,circle[circleIndex]);
        delay(c);
        led(var1+1,circle[circleIndex+4]);
        delay(c);
        led(var1+2,circle[circleIndex+8]);
        delay(c);
        break;
	default:
		break;
	}
}