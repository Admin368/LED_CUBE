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
#include "..\_OwnMadeStcHeaderFiles\paulobetax3.c"
#define uchar unsigned char
	
void main(){
	uchar bX;
	while(1){
		for(bX=1;bX<7;bX++){
			xled(bX);
			xdigit(bX);
			xsegment(bX);
			xseconds(1);
		}
	}
}