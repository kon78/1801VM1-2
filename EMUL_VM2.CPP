#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <math.h>
#include <stdlib.h>
//#include "mem.cpp"

int n,n_enblrd,k,type_cmd;
unsigned short src,dst,code;
unsigned int bank_mem[1024]={0};//1024 byte
//cmd2 - two adr.cmd
const unsigned short cmd2[] = {9,13,14,15,16,17,20};
const int cmd2size = sizeof(cmd2) / sizeof(unsigned short);

//memory map
//    0...16383 x 16bit
//16384...32767 x 16bit
//32768...49151 x 16bit
//49152...65535 x 16bit

	unsigned int memory (unsigned int nmb_cell,
						 unsigned int data, int oprtn)//nmb_cell-number cell
													  //oprtn - operation
													  //rslt-result
{
	unsigned int rslt;
	//operation read
	if (oprtn==0) {
				   rslt=bank_mem[nmb_cell];
				   data=0;
				   oprtn=0;
				   return (rslt);
				  }

	//operation write
	if (oprtn==1) {
				   bank_mem[nmb_cell]=data;
				   data=0;
				   oprtn=0;
				   return(0);
				  }
}

	int bin_printf(unsigned short byte)
{
	for (int i=0;i<16;i++) {
	printf("%d",byte>>15);
	byte=byte<<1;
	}
	printf("\n");
	return k=0;
}
	short read_cmd (int enble_rd)
{
	char text[25]="";
	char str[25]="";
	char end[]="@end\n";
	int lng_str;
	char *endptr;
	FILE *fp;
	fp = fopen ("code.lda", "rt");

	n=1;
	fgets (text,25,fp);
	if(!strcmp(end,text)) {n=0;}
	lng_str = strlen(text);
	strncat(str,text,lng_str-1);
	code = strtol(str, &endptr, 8);//translate to octal command

	if (n==0) {fclose(fp);}
	return k = 0;
}
	short command_analys(unsigned short command)
{   unsigned short COP,MTD_R1,MTD_R0;
	int n;

	COP=command&0170000; COP=COP/010000;
	MTD_R1=command&07700; MTD_R1=MTD_R1/0100;
	MTD_R0=command&077;
	//bin_printf(low_byte_0);
	//printf("%o",low_byte_0);

	for (n=0; n<cmd2size; n++)
	{
	 if (COP==cmd2[n]) type_cmd=2;
					   src=MTD_R1; dst=MTD_R0;
					   break; //type_cmd - two adr.cmd
	}
		   if (n==cmd2size)
			 {
			  type_cmd=0;//type_cmd - uncnown cmd.
			  src=0; dst=0;
			 }


	return k=0;
}

void main()//CPU
{
	char* src,buf;
	unsigned short ccp;
	unsigned short R0,R1,R2,R3,R4,R5,PC,US,SK;
	unsigned short code;
	unsigned int cell,result;
	int start;
	start=1;
	memory(12,34563,1);
	//printf("%6o\n",code);
	//bin_printf(code);
	//read_cmd(start);
	//command_analys(code);
	result=memory(12,0,0);
	//printf("%o\n",result);
	bin_printf(result);
}