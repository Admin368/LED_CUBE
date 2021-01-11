//IR_API_by_SimonNakibinge
#include<reg52.h> 
#define uchar unsigned char
uchar IRDATA[32];
int i = 31;
bit bootCode = 1;			  // boot code boolean
bit realData = 0;				// data after the bootcode
uchar count2 = 0;				 // timer zero count2	
uchar newCode = 0;       // new remote input code flag
uchar dataCode1 = 0x00;  // the infrared code, its inverse is dataCode2
void initInfraredRemCon();//initialization,{call first} 
uchar irCodeDecoder();    // get pressed button 
static void  pulsePosiDem();     //ifrared pulse position demodulation
void timer_reload(){TH0=(65536-46082)/256;TL0=(65536-46082)%256;}
void initInfraredRemCon() // initialize infrared remote control
{
	// external interrupt 0
	EA  = 1;
	EX0 = 1;	// enable external interrupt	
	IT0 = 1;  // activated on falling edge

	// timer zero
	TMOD = TMOD|0x02;  // timer mode 2 for timer 0 
	ET0  = 1;					 // enable timer 0 interrupt 
	TH0=0x00; 	
  TL0=0x00;
}
static void  pulsePosiDem()
{
		uchar i = 0,j=0,k=0, 
		userCode1 = 0x00, userCode2 = 0x00,
		dataCode2 = 0x00, baiti = 0x00,IRByte=0x80;
	
		if(!newCode) return;  // no new remote input yet
			
		for(j=0;j<32;j=j+8)
		{
				
			for(k=j;k<j+8;k++)
			{
				if(IRDATA[k]>6)   // logic one
						baiti |= IRByte;
			
				IRByte>>=1;			
			
			}
			switch(j)
			{
				case 0:  dataCode2 = baiti; break;
				case 8:  dataCode1 = baiti; break;
				case 16: userCode2 = baiti; break;
				case 24: userCode1 = baiti; break;
			};
		
			baiti = 0x00;
			IRByte = 0x80;
		}
		newCode = 0;
}
uchar irCodeDecoder() 
{
			 uchar buttonNum = 24;   // number of button on the infrared sender
	
				pulsePosiDem();
	
       switch(dataCode1) 
			 {
					case 0x45 :	buttonNum=0;  break; // corresponding button number
					case 0x46 :	buttonNum=1;  break;
					case 0x47 :	buttonNum=2;  break;
					case 0x44 :	buttonNum=3;  break;
					case 0x40 :	buttonNum=4;  break;
					case 0x43 :	buttonNum=5;  break;
					case 0x07 :	buttonNum=6;  break;
					case 0x15 :	buttonNum=7;  break;
					case 0xd9 :	buttonNum=8;  break;
					case 0x16 :	buttonNum=9;  break;
					case 0x19 :	buttonNum=10; break;
					case 0x0d :	buttonNum=11; break;
					case 0x0c :	buttonNum=12; break;
					case 0x18 :	buttonNum=13; break;
					case 0x5e :	buttonNum=14; break;
					case 0x08 :	buttonNum=15; break;
					case 0x1c :	buttonNum=16; break;
					case 0x5a :	buttonNum=17; break;
					case 0x42 :	buttonNum=18; break;
					case 0x52 :	buttonNum=19; break;
					case 0x4a :	buttonNum=20; break;
					default : break;
			}

		  return buttonNum;

}


void extInterrupt0() interrupt 0
{
	
		if(bootCode)  // boot code
		{   
				bootCode = 0;
				count2 = 0;
				//TR0 = 1;
				timer_reload();
		} 
		else 
		{		
				if(count2>=32&&count2<=49)  // correct boot code! we start extracting data at next interrupt
				{												  // bootcode and the result code takes 9ms + 4.5ms aprox. 48.6 overflows	
						i = 31;
				}
				else
				{
						IRDATA[i--] = count2;
						count2 = 0;

						if(i <= -1)     // got all the 32 bits
						{
								i = 31;
								bootCode = 1;
								//TR0 = 0; 	   // turn off timer	
								timer_reload();
								newCode = 1;
						}
				}
		}
}

void timer_0_interrupt() interrupt 1 using 1
{
	 count2++;    // 3.6 overflows aprox. to 1 millisecond 
}

