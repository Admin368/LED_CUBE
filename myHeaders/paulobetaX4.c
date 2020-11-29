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
/*CHANGES
>>paulo.h
    -The original Header file
>>paulobetaX.h
    -elimination of 18 unncessary functions
        and replaced with 7 switch statements;
    -burning size redution;
    -replacement of unnecesary variables 
        with just actual values to savce space
    -reduction of memory leakage
>>paulobetaX2.h
    - fixed xsegement to call xdelayms() instead of delay();
    - use of "x" before function names
        to avoid redifination of common names
>>paulobetaX3.h
    - use of "x" before Global varaible names
    - introduction  of xgetkey() function 
        that does row and column check;
    - introduction of xtranslatekey(uchar key)
        to relate the key value to digits and letters;
>>paulobetaX4.h
	- change of xdigit() to xdisplay:
		coz 8bit seg is planned to show 
		letters,symbols,and the digits;
	- removed or P1 = key; at each key press
	- introduction of xresetkey(); 
		to reset all values to 0, to avoid noise
		to other xgetkey() calls;
	- intro of effector and letter array
		into the xtranslatekey(); function
	- brought old reference from paulo.h
>>paulobetaX5.h
	- add a xTranslateLetter
	- add xGetFullLetter 
	- add xletter
	- add getletter = true and use
		xgetkey
	-
*/
//FUNCTION_CLAIM>>START
#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
sbit xseglock = P2^7;
sbit xsegdef = P2^7;
sbit xdiglock = P2^6;
sbit xdigdef = P2^6;
sbit xbuzzer = P2^0;
uchar xsegdelay = 10;
uchar xdigdelay = 10;
uchar xkey,xprekey,xeffector,xletter;
//uchar xgeteffector,xgetletter;
void xbeep();                   //[paulobetaX1.h]
void xseconds(uchar mm);        //[paulobetaX1.h]
void xdelayms();                //[paulobetaX1.h]
void xdelay(uchar xx);          //[paulobetaX1.h]
void xled(uchar ld);            //[paulobetaX2.h]
void xsegment(uchar xseg);      //[paulobetaX2.h]
void xdisplay(uchar xdisp);     //[paulobetaX2.h]
void xgetfullkey();             //[paulobetaX2.h]
void xgetkey();                 //[paulobetaX3.h]
uchar xtranslatekey(uchar key); //[paulobetaX3.h]
void xtranslateeffector();      //[paulobetaX4.h]
void xresetkey();   			//[paulobetaX4.h]
//FUNCTION_CLAIM>>END

//FUNCTIONS_MAIN>>START
void xbeep(){
    xbuzzer = 1; // on
    xdelay(400);
    xbuzzer = 0;
}
void xseconds(uchar mm){
    uchar mmm;
	for (mmm=0;mmm<mm+1;mmm++)
	{
			xdelayms();
	}
}
void xdelayms(){
    uchar ii,jj,kk;
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
void xdelay(uchar xx){
    uchar xz,zx;
    for (xz=0;xz<xx;xz++){
        for (zx=0;zx<120;zx++){}
    }
}
void xled(uchar ld){   
        if (ld == 1){P1 = 0xfe;} //led1 = 0xfe;
        if (ld == 2){P1 = 0xfd;} //led2 = 0xfd;
        if (ld == 3){P1 = 0xfb;} //led3 = 0xfb;
        if (ld == 4){P1 = 0xf7;} //led4 = 0xf7;
        if (ld == 5){P1 = 0xef;} //led5 = 0xef;
        if (ld == 6){P1 = 0xdf;} //led6 = 0xdf;
        if (ld == 7){P1 = 0xbf;} //led7 = 0xbf;
        if (ld == 8){P1 = 0x7f;} //led8 = 0x7f;
        if (ld == 0){P1 = 0xff;} //ledalloff = 0xff;
        if (ld == 00){P1 = 0xff;} //ledalloff = 0xff;
        if (ld == 11){P1 = 0x00;} //ledallon = 0x00;
        if (ld == 21){P1 = 0x0f;} //halfon1 = 0x0f;
        if (ld == 22){P1 = 0x0f;} //halfon2 = 0x0f;
}
void xsegment(uchar xseg){
    switch(xseg)
		{
			case 0:
				P0 = 0xff; //segnone = 0xff;
				break;
			case 1:
				P0 = 0xfe; //seg1 = 0xfe;
				break;
			case 2:
				P0 = 0xfd; //seg2 = 0xfd;
				break;
			case 3:
				P0 = 0xfb; //seg3 = 0xfb;
				break;
			case 4:
				P0 = 0xf7; //seg4 = 0xf7;
				break;
			case 5:
				P0 = 0xef; //seg5 = 0xef;
				break;
			case 6:
				P0 = 0xdf; //seg6 = 0xdf;
				break;
            case 11:
                P0 = 0x00; // segall = 0x00;
			default:
				xsegdef = 0;
				return;
        }
    xdelay(xsegdelay);
    xsegdef = 1;
    xsegdef = 0;
}

void xdisplay(uchar xdisp){
		char x2disp = xdisp;
    switch(x2disp)
        {  
            case 0:
                P0 = 0x3f; //dig0 = 0x3f;
                break;
            case 1:
                P0 = 0x06; //dig1 = 0x06;
                break;
            case 2:
                P0 = 0x5b; //dig2 = 0x5b;
                break; 
            case 3:
                P0 = 0x4f; //dig3 = 0x4f;
                break;
            case 4:
                P0 = 0x66; //dig4 = 0x66;
                break;
            case 5: 
                P0 = 0x6d; //dig5 = 0x6d;
                break;
            case 6:
                P0 = 0x7d; //dig6 = 0x7d;
                break;
            case 7:
                P0 = 0x07; //dig7 = 0x07;
                break;
            case 8:
                P0 = 0x7f; //dig8 = 0x7f;
                break;
            case 9:
                P0 = 0x6f; //dig9 = 0x6f;
                break;
						case 'n': //displays nothing 
								P0 = 0x08;
								break;
			default:
                return;
        }
    xdigdef = 1;
    xdigdef = 0;
//    delay(xdigdelay);
}
void xgetfullkey(){
    xgetkey();
    xtranslatekey(xprekey);
}
void xgetkey(){
    uchar colvalue,rowvalue;
	P3 = 0xf0;//columnCheck //11110000
	if(P3 != 0xf0){
		xdelay(10);//verifying button press
		if(P3 != 0xf0){//columnCheck //11110000
			colvalue=~0xf0|P3; //flips the 0to1 and vise vesa
			P3 = 0x0f;//rowCheck //00001111
			rowvalue = ~0x0f|P3;    // checking row
			xprekey = colvalue&rowvalue;	
        }
	}   
}
uchar xtranslatekey(uchar xprekey){
	//uchar xletter[6] = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z}
	//uchar xeffector[4] = {e0, e1, e2, e3, e4, e5}
switch(xprekey)
		{
		    case 0xee:									
			    xkey = 1;
				break;
			case 0xde:									
				xkey = 2;
				break;								
			case 0xbe:									
				xkey = 3;
				break;								
			case 0x7e:									
				xkey = 4;	
				break;
			case 0xed:									
				xkey = 5;	
				break;
			case 0xdd:									
				xkey = 6;	
				break;								
			case 0xbd:									
				xkey = 7;	
		        break;								
			case 0x7d:									
				xkey = 8;	
				break;									
			case 0xeb:									
				xkey = 9;	
				break;
			case 0xdb:									
				xkey = 10;	
				break;								
			case 0xbb:
				xkey = 10;									
				break;								
			case 0x7b:
				xkey = 11;									
				break;
				xkey = 12;
			case 0xe7:
				xkey = 13;									
				break;
			case 0xd7:
				xkey = 14;									
				break;								
			case 0xb7:									
				xkey= 15;
				break;								
			case 0x77:									
				xkey= 16;	
				break;								
			default:
				xkey = 0;			
		}
return xkey;
}

void xgeteffector(){
			xgetkey();
			xtranslateeffector();
}	
void xtranslateeffector(){
			if (xprekey>0){
				switch(xkey){
					case 1:// addition +
						xeffector = 1;
						break;
					case 2:// subtraction -
						xeffector = 2;
						break;
					case 3:// division /
						xeffector = 3;
						break;
					case 4:// get result
						xeffector = 4;
						break;
					default:
						break;
				}
			}
}


void xresetkey(){
	P3 = 0x00;
	xprekey = 0;
	xkey = 0;
	//xgeteffector = 0;
	//xgetletter = 0;
}

//void xgetletter(){}
/*
void xdisplayletter(){
	switch(xletter)
		case 1:
		P0 = 0x00;
		default:
}
*/
void xgetsidekeys(){}
//FUNCTIONS_MAIN>>END

// REFERENCE //
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
wdig6 = 0xeb; //a0cd efg0 > efg0 a0cd > 1110 1011 > 0xeb;
wdig7 = 0x0e; //abc0 0000 > 0000 abc0 > 0000 1110 > 0x0e;
wdig8 = 0xef; //abcd efg0 > efg0 abcd > 1110 1111 > 0xef;
wdig9 = 0x6f; //abcd 0fg0 > 0fg0 abcd > 0110 1111 > 0x6f;
wdig0 = 0xcf; //abcd ef00 > ef00 abcd > 1100 1111 > 0xcf;

LETTERS
01.A>abc0 efg0>1110 1110>0111 0111>0x77
02.b>00cd efg0>0011 1110>0111 1100>0x7c
03.c>000d e0g0>0001 1010>0101 1000>0x58
04.d>0dcd e0g0>0111 1010>0101 1110>0x5e
05.E>a00d efg0>1001 1110>0111 1001>0x79
06.F>a000 efg0>1000 1110>0111 0001>0x71
07.g>abcd 0fg0>1111 0110>0110 1111>0x6f
08.h>00c0 efg0>0010 1110>0111 0100>0x64
09.I>0000 ef00>0000 1100>0011 0000>0x30
10.J>0bcd e000>0111 1000>0001 1110>0x1e
11.K>!>0x00
12.L>000d ef00>0001 1100>0011 1000>0x38
13.M>!>0x00
14.n>00c0 e0g0>0010 1010>0101 0100>0x54
15.o>00cd e0g0>0011 1010>0101 1100>0x5c
16.p>ab00 efg0>1100 1110>0111 0011>0x73
17.q>abc0 0fg0>1110 0110>0110 0111>0x67
18.r>0000 e0g0>0000 1010>0101 0000>0x50
19.S>a0cd 0fg0>1011 0110>0110 1101>0x6d
20.t>000d efg0>0001 1110>0111 1000>0x78
21.u>00cd e000>0011 1000>0001 1100>0x1c
22.V>!>0x00
23.W>!>0x00
24.X>0bc0 efg0>0110 1110>0111 0110>0x6e
25.y>0bcd 0fg0>0111 0110>0110 1110>0x76
26.Z>ab0d e0g0>1101 1010>0101 1011>0xda
27..>0000 000h>0000 0001>1000 0000>0x80
28._>000d 0000>0001 0000>0000 1000>0x08
29.->0000 00g0>0000 0010>0100 0000>0x40

*/


