/*
header files by https://github.com/Admin368
This Code can be used and modified given freely
No responsibility is taken for any damage or error cause
Read, study , modify the code to own usage
#note: some were written in my earlier day of 8051, so code my had some
- bad memory management
- bad codinng practices
#Hope it makes your life easier as it to do me while learning 8051
*/
//VARAIBLE_SELECT>>START
#include <intrins.h>
#define uchar unsigned char
uchar xx,k,dt,pla;
sbit seglock = P2^7;
sbit diglock = P2^6;
sbit soundbeep = P2^0;
sbit buzzer = P2^0;
segdelay = 10;
digdelay = 10;
levelsdelay= 600;
sbit digdef = P2^6;
sbit segdef = P2^7;
segnone = 0xff;
seg1 = 0xfe;
seg2 = 0xfd;
seg3 = 0xfb;
seg4 = 0xf7;
seg5 = 0xef;
seg6 = 0xdf;
segall = 0x00;
dig1 = 0x06;
dig2 = 0x5b;
dig3 = 0x4f;
dig4 = 0x66;
dig5 = 0x6d;
dig6 = 0x7d;
dig7 = 0x07;
dig8 = 0x7f;
dig9 = 0x6f;
dig0 = 0x3f;
led1 = 0xfe;
led2 = 0xfd;
led3 = 0xfb;
led4 = 0xf7;
led5 = 0xef;
led6 = 0xdf;
led7 = 0xbf;
led8 = 0x7f;
ledallon = 0x00;
ledalloff = 0xff;
halfon1 = 0x0f;
halfon2 = 0xf0;
level8 = 0x00;
level7 = 0x01;
level6 = 0x03;
level5 = 0x07;
level4 = 0x0f;
level3 = 0x1f;
level2 = 0x3f;
level1 = 0x7f;
level0 = 0xff;
red = 0xfc;
green = 0xf3;
yellow = 0xcf;
white = 0x3f;
//VARAIBLE_SELECT>>END

//FUNCTION_CLAIM>>START
void levels(uchar lvl);
void levelauto();
void levelsauto();
void led(uchar ld);
void segment(uchar k);
void segment0();
void segment1();
void segment2();
void segment3();
void segment4();
void segment5();
void segment6();
void digit(uchar dt);
void digit1();
void digit2();
void digit3();
void digit4();
void digit5();
void digit6();
void digit7();
void digit8();
void digit9();
void digit0();
void seconds(uchar mm);
void delayms();
void delay(uchar xx);
void beep();
//FUNCTION_CLAIM>>END

//FUNCTIONS_MAIN>>START

void led(uchar ld)
{   
        if (ld == 1){P1 = led1;}
        if (ld == 2){P1 = led2;}
        if (ld == 3){P1 = led3;}
        if (ld == 4){P1 = led4;}
        if (ld == 5){P1 = led5;}
        if (ld == 6){P1 = led6;}
        if (ld == 7){P1 = led7;}
        if (ld == 8){P1 = led8;}
        if (ld == 11){P1 = ledallon;}
        if (ld == 0){P1 = ledalloff;}
        if (ld == 00){P1 = ledalloff;}
        if (ld == 21){P1 = halfon1;}
        if (ld == 22){P1 = halfon2;}
}
void segment(uchar k)
{   
        if (k == 0){segment0();}
        if (k == 1){segment1();}
        if (k == 2){segment2();}
        if (k == 3){segment3();}
        if (k == 4){segment4();}
        if (k == 5){segment5();}
        if (k == 6){segment6();}

}
void digit(uchar dt)
{   
        if (dt == 1){digit1();}
        if (dt == 2){digit2();}
        if (dt == 3){digit3();}
        if (dt == 4){digit4();}
        if (dt == 5){digit5();}
        if (dt == 6){digit6();}
        if (dt == 7){digit7();}
        if (dt == 8){digit8();}
        if (dt == 9){digit9();}
        if (dt == 0){digit0();}
}

void segment0(){
    P0 = segnone;
    segdef = 1;
	segdef = 0;
    delay(segdelay);
}

void segment1(){
    P0 = seg1;
    segdef = 1;
	segdef = 0;
    delay(segdelay);
}
void segment2(){
    P0 = seg2;
    segdef = 1;
	segdef = 0;
    delay(segdelay);
}
void segment3(){
    P0 = seg3;
    segdef = 1;
	segdef = 0;
    delay(segdelay);
}
void segment4(){
    P0 = seg4;
    segdef = 1;
	segdef = 0;
    delay(segdelay);
}
void segment5(){
    P0 = seg5;
    segdef = 1;
	segdef = 0;
    delay(segdelay);
}
void segment6(){
    P0 = seg6;
    segdef = 1;
	segdef = 0;
    delay(segdelay);
}


void digit1(){
    P0 = dig1;
    digdef = 1;
    digdef = 0;
    delay(digdelay);
}
void digit2(){
    digdef = 1;
    P0 = dig2;
    digdef = 0;
    delay(digdelay);
}

void digit3(){
    digdef = 1;
    P0 = dig3;
    digdef = 0;
    delay(digdelay);
}
void digit4(){
    digdef = 1;
    P0 = dig4;
    digdef = 0;
    delay(digdelay);
}
void digit5(){
    digdef = 1;
    P0 = dig5;
    digdef = 0;
    delay(digdelay);
}
void digit6(){
    digdef = 1;
    P0 = dig6;
    digdef = 0;
    delay(digdelay);
}
void digit7(){
    digdef = 1;
    P0 = dig7;
    digdef = 0;
    delay(digdelay);
}
void digit8(){
    digdef = 1;
    P0 = dig8;
    digdef = 0;
    delay(digdelay);
}
void digit9(){
    digdef = 1;
    P0 = dig9;
    digdef = 0;
    delay(digdelay);
}
void digit0(){
    digdef = 1;
    P0 = dig0;
    digdef = 0;
    delay(digdelay);
}
void seconds(uchar mm)
{
  unsigned char mmm;
	for (mmm=0;mmm<mm+1;mmm++)
	{
			delayms();
	}
}
void delayms()
{
	unsigned char ii, jj, kk;

	_nop_();
	_nop_();
	ii = 5;
	jj = 52;
	kk = 195;
	do
	{
		do
		{
			while (--kk);
		} while (--jj);
	} while (--ii);
}
void beep(){
    buzzer = 1; // on
    delay(400);
    buzzer = 0;
}
void delay(uchar xx){
    unsigned char zx,xz;
    for (xz=0;xz<xx;xz++){
        for (zx=0;zx<120;zx++){}
    }
}
//FUNCTIONS_MAIN>>END

