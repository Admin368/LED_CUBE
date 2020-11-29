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
#include <reg52.h>
#include <intrins.h> //needed for the delayms function
#define uchar unsigned char
int s,ss;
uchar xx;
sbit buzzer = P2^0;

/*
binary to hex
0000=0	1000=8
0001=1	1001=9
0010=2	1010=A
0011=3	1011=B
0100=4	1100=C
0101=5	1101=D
0110=6	1110=E
0111=7	1111=F

//traffic lights
red    // 0011 1111 > 0x3f
green  // 1100 1111 > 0xcf
yellow // 1111 0011 > 0xf3
white  //1111 1100 > 0xfc

red    // 0011 1111 > 1111 1100 >0xfc
green  // 1100 1111 > 1111 0011 >0xf3
yellow // 1111 0011 > 1100 1111 >0xcf
white  //1111 1100  > 0011 1111 >0x3f

//levels from 0 to led "on"
0000 0000 0x00 //level8
0000 0001 0x01 //level7
0000 0011 0x03 //level6
0000 0111 0x07 //level5
0000 1111 0x0f //level4
0001 1111 0x1f //level3
0011 1111 0x3f //level2
0111 1111 0x7f //level1
1111 1111 0xff //level0

1111 1110 0xfe //led1
1111 1101 0xfd //led2
1111 1011 0xfb //led3
1111 0111 0xf7 //led4
1110 1111 0xef //led5
1101 1111 0xdf //led6
1011 1111 0xbf //led7
0111 1111 0x7f //led8
0000 0000 0x00
1111 1111 0xff
*/

//Segments
sbit digdef = P2^6; //digit define "0" for open , "1" for close
sbit segdef = P2^7; //Segment define "0" for open , "1" for close
//segment_def //selected when 1
// available pins
//segment_def //selected when 0
// available pins
sbit seg1 = P0^0;
sbit seg2 = P0^1;
sbit seg3 = P0^2;
sbit seg4 = P0^3;
sbit seg5 = P0^4;
sbit seg6 = P0^5;
//segall = P0;

//digits_def //selected when 1
// order of list sig. bit "hgfedcba"
//Var    abcd efgh > hgfe dcba > binary    > hex
dig1 = 0x06; //0bc0 0000 > 0000 0cb0 > 0000 0110 > 0x06;
dig2 = 0x5b; //ab0d e0g0 > 0g0e d0ba > 0101 1011 > 0x5b;
dig3 = 0x4f; //abcd 00g0 > 0g00 dcba > 0100 1111 > 0x4f;
dig4 = 0x66; //0bc0 0fg0 > 0gf0 0cb0 > 0110 0110 > 0x66;
dig5 = 0x6d; //a0cd 0fg0 > 0gf0 dc0a > 0110 1101 > 0x6d;
dig6 = 0x7d; //a0cd efg0 > 0gfe dc0a > 0111 1101 > 0x7d;
dig7 = 0x07; //abc0 0000 > 0000 0cba > 0000 0111 > 0x07;
dig8 = 0x7f; //abcd efg0 > 0gfe dcba > 0111 1111 > 0x7f;
dig9 = 0x6f; //abcd 0fg0 > 0gf0 dcba > 0110 1111 > 0x6f;
dig0 = 0x3f; //abcd ef00 > 00fe dcba > 0011 1111 > 0x3f;

//first wrong translation
wdig1 = 0x06; //0bc0 0000 > 0000 0bc0 > 0000 0110 > 0x06;
wdig2 = 0xad; //ab0d e0g0 > e0g0 ab0d > 1010 1101 > 0xad;
wdig3 = 0x2f; //abcd 00g0 > 00g0 abcd > 0010 1111 > 0x2f;
wdig4 = 0x66; //0bc0 0fg0 > 0fg0 0bc0 > 0110 0110 > 0x66;
wdig5 = 0x6b; //a0cd 0fg0 > 0fg0 a0cd > 0110 1011 > 0x6b;
wdig6 = 0xeb; //a0cd efg0 > efg0 a0cd > 1110 1011 > 0xeb;
wdig7 = 0x0e; //abc0 0000 > 0000 abc0 > 0000 1110 > 0x0e;
wdig8 = 0xef; //abcd efg0 > efg0 abcd > 1110 1111 > 0xef;
wdig9 = 0x6f; //abcd 0fg0 > 0fg0 abcd > 0110 1111 > 0x6f;
wdig0 = 0xcf; //abcd ef00 > ef00 abcd > 1100 1111 > 0xcf;


// single LEDS //
led1 = 0xfe;
led2 = 0xfd;
led3 = 0xfb;
led4 = 0xf7;
led5 = 0xef;
led6 = 0xdf;
led7 = 0xbf;
led8 = 0x7f;
// multiple LEDs //
ledallon = 0x00;
ledalloff = 0xff;
halfon1 = 0x0f;
halfon2 = 0xf0;

// levels of light// on wen "0"
level8 = 0x00; //0000 0000
level7 = 0x01; //0000 0001
level6 = 0x03; //0000 0011
level5 = 0x07; //0000 0111
level4 = 0x0f; //0000 1111
level3 = 0x1f; //0001 1111
level2 = 0x3f; //0011 1111
level1 = 0x7f; //0111 1111
level0 = 0xff; //1111 1111

//traffic lights// on wen "0"
red = 0xfc;     // 0011 1111 > 0x3f
green = 0xf3;  // 1100 1111 > 0xcf
yellow = 0xcf;  // 1111 0011 > 0xf3
white = 0x3f;  // 1111 1100 > 0xfc

//DECLAIRE FUNCTIONS
int segment(int s);
void led();
void digit();
void segment0();
void segment1();
void segment2();
void segment3();
void segment4();
void segment5();
void segment6();
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
void seconds(uchar m);
void delayms();
void delay(uchar xx);
void beep();
/*
int segment(int s)
{   
        if (s = 1) segment1();
        if (s = 2) segment2();
        if (s = 3) segment3();
        if (s = 4) segment4();
        if (s = 5) segment5();
        if (s = 6) segment6();
//    if (s=3){segment3();}else{}


}
*/
void segment1(){
    segdef = 1;
	seg1 = 0;
	segdef = 0;
}
void segment2(){
    segdef = 1;
	seg2 = 0;
	segdef = 0;
}
void segment3(){
    segdef = 1;
	seg3 = 0;
	segdef = 0;
}
void segment4(){
    segdef = 1;
	seg4 = 0;
	segdef = 0;
}
void segment5(){
    segdef = 1;
	seg5 = 0;
	segdef = 0;
}
void segment6(){
    segdef = 1;
	seg6 = 0;
	segdef = 0;
}

void digit1(){
    digdef = 1;
    P0 = dig1;
    digdef = 0;
}

void digit2(){
    digdef = 1;
    P0 = dig2;
    digdef = 0;
}

void digit3(){
    digdef = 1;
    P0 = dig3;
    digdef = 0;
}

void digit4(){
    digdef = 1;
    P0 = dig4;
    digdef = 0;
}


void digit5(){
    digdef = 1;
    P0 = dig5;
    digdef = 0;
}


void digit6(){
    digdef = 1;
    P0 = dig6;
    digdef = 0;
}


void digit7(){
    digdef = 1;
    P0 = dig7;
    digdef = 0;
}


void digit8(){
    digdef = 1;
    P0 = dig8;
    digdef = 0;
}


void digit9(){
    digdef = 1;
    P0 = dig9;
    digdef = 0;
}


void digit0(){
    digdef = 1;
    P0 = dig0;
    digdef = 0;
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
//    delay(10000);
}

void delay(uchar xx){
    unsigned char zx,xz;
    for (xz=0;xz<xx;xz++){
        for (zx=0;zx<120;zx++){}
    }
}