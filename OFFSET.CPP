#include <stdio.h>
#include <conio.h>

void main ()
	{
	int direction = 0;
	short addr, code, pc;
	code = 0400;
	pc =  00;
	addr = 04;

	if (direction==1) {
	//inference offset
	code = code + ((addr^0177)+1);
					  }

	if (direction==0) {
	//reverse offset
	code = code + ((addr^077)+1);
					  }
	clrscr();
	printf ("%o", code);
	}