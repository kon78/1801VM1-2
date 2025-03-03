#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm1801.cpp"

char  Banner[] =
"dis1801 - дизассемблер процессора ВМ1801\n"
"dis1801 <program> [base-addr(oct.)] [options]\n"
"OPTIONS:\n"
"  r - поменять порядок байтов в слове\n"
"  o - выводить операнды команд отдельно\n"
;

void main(int argc,char* argv[]) {
	if (argc<2) {
		printf("%s",Banner);
		return;
	}
	int  addr = strtol(argv[2],NULL,8);
	bool  reverse_bytes = false;
	bool  print_operands = false;
   	if (argc>3) {
	    char*  cpos = argv[3];
	    strlwr(cpos);
	   	while (*cpos) {
	   		switch (*cpos) {
	   			case 'r': reverse_bytes = true; break;
	   			case 'o': print_operands = true; break;
	   		}
	   		cpos++;
	   	}
   	}

	FILE*  f;
	f = fopen(argv[1],"rb");
	if (!f) {
		printf("error open file '%s' for read\n",argv[1]);
		return;
	}
	fseek(f,0,SEEK_END);
	long  fsize = ftell(f);
	char*  buf = new char[fsize];
	fseek(f,0,SEEK_SET);
	fsize = fread(buf,1,fsize,f);
	fclose(f);

	// reverse byte order
	if (reverse_bytes) {
		for (long n=0;n<fsize;n+=2) {
			char  t = buf[n];
			buf[n] = buf[n+1];
			buf[n+1] = t;
		}
	}

	char  asms[80];
	for (long n=0;n<fsize;n+=2) {
		short  w = *(short*)&buf[n];
		int  nskip = disasm_VM1801((short*)&buf[n],asms,addr+n);
		printf("%06lo: %6o ; %s\n",addr+n,w,asms);
		if (print_operands) {
			while (nskip>0) {
				n += 2;
				printf("%06lo: %6o\n",addr+n,*(short*)&buf[n]);
				nskip -= 2;
			}
		}
		else n += nskip;
	}
}
