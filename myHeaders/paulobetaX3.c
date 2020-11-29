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
>>paulobetaX3.h
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
uchar xkey,xprekey;
void xbeep();                   //[paulobetaX1.h]
void xseconds(uchar mm);        //[paulobetaX1.h]
void xdelayms();                //[paulobetaX1.h]
void xdelay(uchar xx);          //[paulobetaX1.h]
void xled(uchar ld);            //[paulobetaX2.h]
void xsegment(uchar xseg);      //[paulobetaX2.h]
void xdigit(uchar xdig);        //[paulobetaX2.h]
void xgetfullkey();             //[paulobetaX2.h]
void xgetkey();                  //[paulobetaX3.h]
uchar xtranslatekey(uchar key);   //[paulobetaX3.h]
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

void xdigit(uchar xdig){
    switch(xdig)
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
	switch(xprekey)
		{
		    case 0xee:
                P1 = xkey;  // light LED									
			    xkey = 1;
				break;
			case 0xde:									
				P1 = xkey;  // light LED
				xkey = 2;
				break;								
			case 0xbe:									
				P1 = xkey;  // light LED
				xkey = 3;
				break;								
			case 0x7e:									
			    P1 = xkey;  // light LED
				xkey = 4;	
				break;
			case 0xed:									
				P1 = xkey;  // light LED
				xkey = 5;	
				break;
			case 0xdd:									
				P1 = xkey;  // light LED
				xkey = 6;	
				break;								
			case 0xbd:									
				P1 = xkey;  // light LED
				xkey = 7;	
		        break;								
			case 0x7d:									
			    P1 = xkey;  // light LED
				xkey = 8;	
				break;									
			case 0xeb:									
				P1 = xkey;  // light LED
				xkey = 9;	
				break;
			case 0xdb:									
				P1 = xkey;  // light LED
				xkey = 0;	
				break;								
			case 0xbb:									
				P1 = xkey;  // light LED
				break;								
			case 0x7b:									
				P1 = xkey;  // light LED
				break;
			case 0xe7:									
				P1 = xkey;  // light LED
				break;
			case 0xd7:									
				P1 = xkey;  // light LED
				break;								
			case 0xb7:									
				P1 = xkey;  // light LED
				xkey='+';
				break;								
			case 0x77:									
				P1 = xkey;  // light LED
				xkey='=';	
				break;								
			default:
				xkey = 0;			
		}			
	return xkey;
}
//FUNCTIONS_MAIN>>END

