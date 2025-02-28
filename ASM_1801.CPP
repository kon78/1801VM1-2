#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <math.h>
#include <stdlib.h>

char op_g_txt[8]="";
unsigned char str_tp;
unsigned short opcod_g;
short addr;
short pc;
int k;
double result_k;
const char* cmd2[] = {"mov","movb","cmp","cmpb","bit","bitb","bic","bicb",
					  "bis","bisb","add","sub","xor"};
const int cmd2size = sizeof(cmd2) / sizeof(char*);
const char* cmd1[] = {"clr","clrb","com","comb",
					  "inc","incb","dec","decb","neg","negb","tst","tstb",
					  "asr","asrb","asl","aslb","ror","rorb","rol","rolb",
					  "adc","adcb","sbc","sbcb","sxt","swab",      "mfps",
					  "mrts"};
const int cmd1size = sizeof(cmd1) / sizeof(char*);
const char* cmd4[] = {"br" ,"bne" ,"beq","bpl" ,"bmi","bvc" ,
					  "bvs","bcc" ,"bcs","bge" ,"blt","bgt" ,"ble","bhi" ,
							"blos","jmp"};
const int cmd4size = sizeof(cmd4) / sizeof(char*);
const char* cmd3[] = {"jsr" ,"rst","mark","sob"};
const int cmd3size = sizeof(cmd3) / sizeof(char*);
const char* cmd5[] = {"emt","trap","iot","bpt" ,"rti","rtt"};
const int cmd5size = sizeof(cmd5) / sizeof(char*);
const char* cmd6[] = {"halt","wait","reset"};
const int cmd6size = sizeof(cmd6) / sizeof(char*);
const char* cmd7[] = {"cln","clz" ,"clv","clc","ccc","sen" ,"sez","sev"
					  ,"sec","scc" ,"nop"};
const int cmd7size = sizeof(cmd7) / sizeof(char*);
const char* cmd8[] = {"mul","div","ash","ashc"};
const int cmd8size = sizeof(cmd8) / sizeof(char*);
const char* cmd9[] = {"fadd","fsub","fmul","fdiv"};
const int cmd9size = sizeof(cmd9) / sizeof(char*);


short jump_code(short code, short addr, int direction)
{
	if (direction==1) {
	//inference offset
	code = code + ((addr^0177)+1);
					  }

	if (direction==0) {
	//reverse offset
	code = code + ((addr^077)+1);
					  }
	return code;
}


short Asm2 (char* src, char* buf)
		  {
		   char *razd = ", ";
		   char *p, *endptr;
		   char op1[6]="", op2[6]="";
		   char keyword[16], op_txt[16]="";
		   int res = sscanf(src,"%s",keyword);
		   int n;
		   opcod_g = 0;
		   for (n=0; n<cmd2size; n++)
			  {
			   if (!strcmp(keyword,cmd2[n])) break;
			  }
		   if (n==cmd2size)
			 {
			  result_k = fmod (3,2);//don't finded operand
			 }

		   switch(n)
		   {
			//two address command
			case  0: sprintf(op_txt,"01"); break;//mov
			case  1: sprintf(op_txt,"11"); break;//movb
			case  2: sprintf(op_txt,"02"); break;//cmp
			case  3: sprintf(op_txt,"12"); break;//cmpb
			case  4: sprintf(op_txt,"03"); break;//bit
			case  5: sprintf(op_txt,"13"); break;//bitb
			case  6: sprintf(op_txt,"04"); break;//bic
			case  7: sprintf(op_txt,"14"); break;//bicb
			case  8: sprintf(op_txt,"05"); break;//bis
			case  9: sprintf(op_txt,"15"); break;//bisb
			case 10: sprintf(op_txt,"06"); break;//add
			case 11: sprintf(op_txt,"16"); break;//sub
			case 12: sprintf(op_txt,"074");break;//xor
		   }
		   p = strtok (src, razd);
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op1,p);
				 }
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op2,p);
				 }
		   char *fnd_op1 = strchr (op1,'@');
		   char *fnd_op2 = strchr (op2,'@');

		   if(!fnd_op1) goto L2; else goto L1;

L2:        if(!strcmp(fnd_op1,fnd_op2)) goto L6; else goto L3;
L1:		   if(!strcmp(fnd_op1,fnd_op2)) goto L7; else goto L3;
L6:        //XX2727
		   strcat (op_txt,op1);
		   strcat (op_txt,op2);
		   goto L8;
L7:        //XX3737
		   fnd_op1 = strtok (op1,"@");
		   fnd_op2 = strtok (op2,"@");
		   strcat (op_txt,fnd_op1);
		   strcat (op_txt,fnd_op2);
		   goto L8;
L3:		   if (!fnd_op1) {//XX2737
						  strcat (op_txt,op1);
						  fnd_op2 = strtok (op2,"@");
						  strcat (op_txt,fnd_op2);
						  goto L8;
						 }
		   else {//XX3727
				 fnd_op1 = strtok (op1,"@");
				 strcat (op_txt,fnd_op1);
				 strcat (op_txt,op2);
				 goto L8;
				}
L8:        //strcpy (op_g_txt, op_txt);
		   opcod_g = strtol(op_txt, &endptr, 10);//decimal command
}

short Asm1 (char* src, char* buf)
		  {
		   char *razd = ", ";
		   char *p, *endptr;
		   char op1[6]="";
		   char keyword[16], op_txt[16]="";
		   int res = sscanf(src,"%s",keyword);
		   int n;
		   str_tp = 1;
		   opcod_g = 0;
		   for (n=0; n<cmd1size; n++)
			  {
			   if (!strcmp(keyword,cmd1[n])) break;
			  }
		   if (n==cmd1size)
			 {
			  result_k = fmod (5,2);//don't finded operand
			 }

		   switch(n)
		   {
			//one address command
			case  0: sprintf(op_txt,"0050");break;//clr
			case  1: sprintf(op_txt,"1050");break;//clrb
			case  2: sprintf(op_txt,"0051");break;//com
			case  3: sprintf(op_txt,"1051");break;//comb
			case  4: sprintf(op_txt,"0052");break;//inc
			case  5: sprintf(op_txt,"1052");break;//incb
			case  6: sprintf(op_txt,"0053");break;//dec
			case  7: sprintf(op_txt,"1053");break;//decb
			case  8: sprintf(op_txt,"0054");break;//neg
			case  9: sprintf(op_txt,"1054");break;//negb
			case 10: sprintf(op_txt,"0057");break;//tst
			case 11: sprintf(op_txt,"1057");break;//tstb
			case 12: sprintf(op_txt,"0062");break;//asr
			case 13: sprintf(op_txt,"1062");break;//asrb
			case 14: sprintf(op_txt,"0063");break;//asl
			case 15: sprintf(op_txt,"1063");break;//aslb
			case 16: sprintf(op_txt,"0060");break;//ror
			case 17: sprintf(op_txt,"1060");break;//rorb
			case 18: sprintf(op_txt,"0061");break;//rol
			case 19: sprintf(op_txt,"1061");break;//rolb
			case 20: sprintf(op_txt,"0055");break;//adc
			case 21: sprintf(op_txt,"1055");break;//adcb
			case 22: sprintf(op_txt,"0056");break;//sbc
			case 23: sprintf(op_txt,"1056");break;//sbcb
			case 24: sprintf(op_txt,"0067");break;//sxt
			case 25: sprintf(op_txt,"0003");break;//swab
			case 26: sprintf(op_txt,"1067");break;//mfps
			case 27: sprintf(op_txt,"1064");break;//mtrs
		   }
		   p = strtok (src, razd);
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op1,p);
				 }
		   p = strtok (NULL, razd);
		   char *fnd_op1 = strchr (op1,'@');
		   if(!fnd_op1) goto L10; else goto L9;

L9:		   //XXXX37
		   fnd_op1 = strtok (op1,"@");//delete @
		   strcat (op_txt,fnd_op1);
		   goto L11;
L10: 	   //XXXX27
		   strcat (op_txt,op1);
		   goto L11;
L11:       opcod_g = strtol(op_txt, &endptr, 10);//decimal command
		  }

short Asm3 (char* src, char* buf)
		  {
		   char text[16]="";
		   char *razd = ", ";
		   char *p, *endptr;
		   char *fnd_op1, *fnd_op2;
		   char op1[6]="", op2[6]="";
		   char keyword[16], op_txt[16]="";
		   short cod;
		   int res = sscanf(src,"%s",keyword);
		   int n;

		   for (n=0; n<cmd3size; n++)
			  {
			   if (!strcmp(keyword,cmd3[n])) break;
			  }
		   if (n==cmd3size)
			 {
			  result_k = fmod (9,2);//don't finded operand
			 }

		   switch(n)
		   {
			//command subprogram
			case  0: sprintf(op_txt,"004"); break;//jsr 4RD; jsr RXXX 27or@37
			case  1: sprintf(op_txt,"00020"); break;//rst 20R; rst RXXX
			case  2: sprintf(op_txt,"0064"); break;//mark 64N; mark N
			case  3: sprintf(op_txt,"077"); break;//sob 77RN; sob RXXX N
		   }
		   p = strtok (src, razd);
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op1,p);
				 }
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op2,p);
				 }

		   if (n==0) {
					  //4RX@37 or 27
					  fnd_op1 = strtok (op1,"R");//delete R
					  fnd_op2 = strtok (op2,"@");//delete @
					  strcat (op_txt,fnd_op1);
					  strcat (op_txt,fnd_op2);
					  str_tp = 1;
					  opcod_g = strtol(op_txt, &endptr, 10);//decimal command
					 }

		   if (n==1) {
					  //20R
					  fnd_op1 = strtok (op1,"R");//delete R
					  strcat (op_txt,fnd_op1);
					  str_tp = 0;
					  opcod_g = strtol(op_txt, &endptr, 10);//decimal command
					 }

		   if (n==2) {//64N
					  fnd_op1 = strtok (op1,"N");//delete N;
					  short param = strtol(fnd_op1, &endptr, 10);//param -> addr
					  //subprogram calculate address jump
					  str_tp = 0;
					  opcod_g = jump_code (06400, param, 0);
					 }

		   if (n==3) {
					  //77RN
					  fnd_op1 = strtok (op1,"R");//delete R
					  fnd_op2 = strtok (op2,"N");//delete N
					  cod = (strtol (fnd_op1, &endptr, 10))*0100 + 077000;
					  short param = strtol(fnd_op2, &endptr, 10);//param -> addr

					  //subprogram calculate address jump
					  str_tp = 0;
					  opcod_g = jump_code (cod, param, 0);
					 }
		  }

short Asm4 (char* src, char* buf)
		  {
		   char text[16]="";
		   char *razd = ", :";
		   char *p, *endptr;;
		   char op1[6]="", op2[6]="";
		   char keyword[16], opcod_txt[8]="";
		   int res = sscanf(src,"%s",keyword);
		   int n;
		   short opcod;
		   double L_nmb;
		   FILE *fp2;

		   fp2 = fopen ("label.txt", "rt");
		   for (n=0; n<cmd4size; n++)
			  {
			   if (!strcmp(keyword,cmd4[n])) break;
			  }
		   if (n==cmd4size)
			 {
			  result_k = fmod (9,2);//don't finded operand
			 }

		   switch(n)
		   {
			case  0: sprintf(opcod_txt,"000400"); opcod = 0400; break;//br
			case  1: sprintf(opcod_txt,"001000"); opcod = 01000; break;//bne
			case  2: sprintf(opcod_txt,"001400"); opcod = 01400; break;//beq
			case  3: sprintf(opcod_txt,"100000"); opcod = 0100000; break;//bpl
			case  4: sprintf(opcod_txt,"100400"); opcod = 0100400; break;//bvc
			case  5: sprintf(opcod_txt,"102400"); opcod = 0102400; break;//bvs
			case  6: sprintf(opcod_txt,"103000"); opcod = 0103000; break;//bcc
			case  7: sprintf(opcod_txt,"103400"); opcod = 0103400; break;//bcs
			case  8: sprintf(opcod_txt,"002000"); opcod = 02000; break;//bge
			case  9: sprintf(opcod_txt,"002400"); opcod = 02400; break;//blt
			case 10: sprintf(opcod_txt,"003000"); opcod = 03000; break;//bgt
			case 11: sprintf(opcod_txt,"003400"); opcod = 03400; break;//ble
			case 12: sprintf(opcod_txt,"101000"); opcod = 0101000; break;//bhi
			case 13: sprintf(opcod_txt,"101400"); opcod = 0101400; break;//blos
			case 14: sprintf(opcod_txt,"000001"); opcod = 01; break;//jmp
		   }
		   p = strtok (src, razd);//src -> XXX MX;
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op1,p);//op1 -> MX;
				 }
		   n=1;
		   do {
			   fgets (text,16,fp2);
			   p = strtok (text, razd);//text -> MX: YY;
			   p = strtok (NULL, razd);
			   if(p) {
				  strcpy (op2,p);//op2 -> YY; address;
				 }
			   if(!strcmp(text,op1)) n=0;//(!MX,MX)

			  } while (n==1);

		   fclose (fp2);
		   short label = strtol(op2, &endptr, 10);//label -> YY (number)
		   str_tp = 0;
		   opcod_g = jump_code (opcod, label, 1);
		   //put to file cmd
		  }


/*
short Asm5 (char* src, char* buf)
		  {
		   char text[16]="";
		   char *razd = ", ";
		   char *p;
		   char op1[4]="", op2[4]="";
		   char keyword[16], opcod[8]="";
		   int res = sscanf(src,"%s",keyword);
		   int n, z;
		   for (n=0; n<cmd5size; n++)
			  {
			   if (!strcmp(keyword,cmd5[n])) break;
			  }
		   if (n==cmd5size)
			 {
			  result_k = fmod (11,2);//don't finded operand
			 }

		   switch(n)
		   {
			//command interrupt
			case 61: sprintf(opcod,"104000");result_k = fmod (8,2);break;//emt 104000-104377
			case 62: sprintf(opcod,"104400");result_k = fmod (8,2);break;//trap 104400-104777
			case 63: sprintf(opcod,"000004");result_k = fmod (8,2);break;//iot
			case 64: sprintf(opcod,"000003");result_k = fmod (8,2);break;//bpt
			case 65: sprintf(opcod,"000002");result_k = fmod (8,2);break;//rti
			case 66: sprintf(opcod,"000006");result_k = fmod (8,2);break;//rtt
		   }
		   p = strtok (src, razd);//src -> XXX YY;
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op1,p);//op1 -> YY; for command emt and trap;
				 }

		  }
*/

/*
short Asm6 (char* src, char* buf)
		  {
		   char text[16]="";
		   char *razd = ", ";
		   char *p;
		   char op1[4]="", op2[4]="";
		   char keyword[16], opcod[8]="";
		   int res = sscanf(src,"%s",keyword);
		   int n, z;
		   for (n=0; n<cmd6size; n++)
			  {
			   if (!strcmp(keyword,cmd6[n])) break;
			  }
		   if (n==cmd6size)
			 {
			  result_k = fmod (13,2);//don't finded operand
			 }

		   switch(n)
		   {
			//command administrate machine
			case 67: sprintf(opcod,"000000"); result_k = fmod (10,2);break;//halt
			case 68: sprintf(opcod,"000001"); result_k = fmod (10,2);break;//wait
			case 69: sprintf(opcod,"000005"); result_k = fmod (10,2);break;//reset
		   }
		   strcpy (opcod_g, opcod);
		  }
*/

/*
short Asm7 (char* src, char* buf)
		  {
		   char keyword[16];
		   int res = sscanf(src,"%s",keyword);
		   int n;
		   for (n=0; n<cmd7size; n++)
			  {
			   if (!strcmp(keyword,cmd7[n])) break;
			  }
		   if (n==cmd7size)
			 {
			  result_k = fmod (15,2);//don't finded operand
			 }

		   switch(n)
		   {
			//command change appointment flag
			case  0: sprintf(opcod,"000250"); result_k = fmod (12,2);break;//cln
			case  1: sprintf(opcod,"000244"); result_k = fmod (12,2);break;//clz
			case  2: sprintf(opcod,"000242"); result_k = fmod (12,2);break;//clv
			case  3: sprintf(opcod,"000241"); result_k = fmod (12,2);break;//clc
			case  4: sprintf(opcod,"000247"); result_k = fmod (12,2);break;//ccc
			case  5: sprintf(opcod,"000270"); result_k = fmod (12,2);break;//sen
			case  6: sprintf(opcod,"000264"); result_k = fmod (12,2);break;//sez
			case  7: sprintf(opcod,"000262"); result_k = fmod (12,2);break;//sev
			case  8: sprintf(opcod,"000261"); result_k = fmod (12,2);break;//sec
			case  9: sprintf(opcod,"000267"); result_k = fmod (12,2);break;//scc
			case 10: sprintf(opcod,"000240"); result_k = fmod (12,2);break;//nop
		   }
		   strcpy (opcod_g, opcod);
		  }
*/

/*
short Asm8 (char* src, char* buf)
		  {
		   char text[16]="";
		   char *razd = ", ";
		   char *p;
		   char op1[4]="", op2[4]="";
		   char keyword[16], opcod[8]="";
		   int res = sscanf(src,"%s",keyword);
		   int n, z;
		   for (n=0; n<cmd8size; n++)
			  {
			   if (!strcmp(keyword,cmd8[n])) break;
			  }
		   if (n==cmd8size)
			 {
			  result_k = fmod (17,2);//don't finded operand
			 }

		   switch(n)
		   {
			//command ariphmetics
			case  0: sprintf(opcod,"070"); break;//mul
			case  1: sprintf(opcod,"071"); break;//div
			case  2: sprintf(opcod,"072"); break;//ash
			case  3: sprintf(opcod,"073"); break;//ashc
		   }
		   p = strtok (src, razd);
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op1,p);
				 }
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op2,p);
				 }
		   //
		   //******
		  }
*/

/*
short Asm9 (char* src, char* buf)
		  {
		   char text[16]="";
		   char *razd = ", ";
		   char *p;
		   char op1[4]="", op2[4]="";
		   char keyword[16], opcod[8]="";
		   int res = sscanf(src,"%s",keyword);
		   int n, z;
		   for (n=0; n<cmd9size; n++)
			  {
			   if (!strcmp(keyword,cmd9[n])) break;
			  }
		   if (n==cmd9size)
			 {
			  result_k = fmod (19,2);//don't finded operand
			 }

		   switch(n)
		   {
			//command ariphmetics dot
			case 85: sprintf(opcod,"07500"); break;//fadd
			case 86: sprintf(opcod,"07501"); break;//fsub
			case 87: sprintf(opcod,"07502"); break;//fmul
			case 88: sprintf(opcod,"07503"); break;//fdiv
		   }
		   p = strtok (src, razd);//src -> XXX YY;
		   p = strtok (NULL, razd);
		   if(p) {
				  strcpy (op1,p);//op1 -> YY; for command emt and trap;
				 }
		  //
		  //*****
		  }
*/


void main()
{
	char str[16]="";
	char strfree[]="";
	char text[16]="";
	char end[] = "@end\n";
	char binbuf[32];
	char *endptr;
	//char symbol = ' ';
	int n, i, lng_str;
	char *razd = ", ";
	FILE *fp, *fp1;

	fp = fopen ("code.asm", "rt");
   fp1 = fopen ("code.lda", "wt");
L11:
	n=1;
	addr = 0;
	do {
		fgets (text,16,fp);
		pc = pc + 1;//counter string
		if(!strcmp(end,text)) {n=0; goto L12;}
		lng_str = strlen(text);
		strncat(str,text,lng_str-1);
		k = 0;//search command from file - start

		do {
			k = Asm1(str, binbuf);
			k = Asm2(str, binbuf);
			k = Asm3(str, binbuf);
			k = Asm4(str, binbuf);
		   } while (k==1);

		fprintf (fp1, "%o\n", opcod_g);
		if (k==-1) n=0; else goto L10;
	   } while (n==1);

L10:    if (str_tp==2) {
		for (i=0; i<2; i++) {
							 str[0]='\0';
							 fgets (text,16,fp);
							 lng_str = strlen(text);
							 strncat(str,text,lng_str-1);
							 short op = strtol (str, &endptr, 10);
							 fprintf (fp1, "%o\n", op);
							}
					   }

		if (str_tp==1) {
		for (i=0; i<1; i++) {
							 str[0]='\0';
							 fgets (text,16,fp);
							 lng_str = strlen(text);
							 strncat(str,text,lng_str-1);
							 short op = strtol (str, &endptr, 10);
							 fprintf (fp1, "%o\n", op);
							}
					   }


		str[0] = '\0';
		op_g_txt[0] = '\0';
		goto L11;
L12:	fclose(fp);
		fclose(fp1);
}

