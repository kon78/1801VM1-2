//header.h
#include<iostream.h>
#include<stdio.h>
#include<string.h>
#include <algorithm>
#include <list>
#include<vector>

#pragma hdrstop
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif
#define MAX_SEQ 40
#define MAX_SUBS 10
//#define MAX_BUF 32
#define _run 1
#define _stop -1
#define _reading 100
#define SizeArrOfCmd 3 
#define do1 true
//#define showFile true
#define pResultShow true
#define MAX_STACK 10

#define Search1 true
#define Search2 true
#define Search3 true
#define Search4 true
#define Search5 true
#define Search6 true
#define Search7 true
#define Search8 true
#define Search9 true

char* cmd1[] =       {"clr","clrb","com","comb",
					  "inc","incb","dec","decb","neg","negb","tst","tstb",
					  "asr","asrb","asl","aslb","ror","rorb","rol","rolb",
					  "adc","adcb","sbc","sbcb","sxt","swab",         "mfps",
					        														 "mrts"};
const int cmd1size = sizeof(cmd1) / sizeof(char*);

char* cmd2[] = {"mov","movb","cmp","cmpb","bit","bitb","bic","bicb",
					  "bis","bisb","add","sub","xor"};
const int cmd2size = sizeof(cmd2) / sizeof(char*);

char* cmd3[] = {"jsr" ,"rst","mark","sob"};
const int cmd3size = sizeof(cmd3) / sizeof(char*);

char* cmd4[] = {"br" ,"bne" ,"beq","bpl" ,"bmi","bvc" ,
					  "bvs","bcc" ,"bcs","bge" ,"blt","bgt" ,"ble","bhi" ,
							"blos","jmp"};
const int cmd4size = sizeof(cmd4) / sizeof(char*);

char* cmd5[] = {"emt","trap","iot","bpt" ,"rti","rtt"};
const int cmd5size = sizeof(cmd5) / sizeof(char*);

char* cmd6[] = {"halt","wait","reset"};
const int cmd6size = sizeof(cmd6) / sizeof(char*);

char* cmd7[] = {"cln","clz" ,"clv","clc","ccc","sen" ,"sez","sev"
					  ,"sec","scc" ,"nop"};
const int cmd7size = sizeof(cmd7) / sizeof(char*);

char* cmd8[] = {"mul","div","ash","ashc"};
const int cmd8size = sizeof(cmd8) / sizeof(char*);

char* cmd9[] = {"fadd","fsub","fmul","fdiv"};
const int cmd9size = sizeof(cmd9) / sizeof(char*);

char* operand2[] = {"01","11","02","12","03","13","04","14","05","15","06","16","074"};
int op2size = sizeof(operand2) / sizeof(char*);

char* arrOfCmd[] = {*cmd1,*cmd2,*cmd3,*cmd4,*cmd5,*cmd6,*cmd7,*cmd8,*cmd9};
const int sizeArrOfCmd = (sizeof(arrOfCmd) / sizeof(char*));

char** pArrOfCmd;
char* pElemArrOfCmd;
char seq[MAX_SEQ];
char subseq[MAX_SUBS];
char cmd[MAX_SUBS];
//char subseq[10];
char* pS;//под операцию new
char* _pS;//в основном теле программы

char  modetable[8][4] = {"rt","wt","at","r+t","rb","wb","ab","r+b"};
int _while;
/*-------------------------------------------------------------------------------functions---*/
void code();
/*-------------------------------------------------------------------------------class Command---*/
class Command{
public:
  virtual ~Command() {}
  virtual void execute() = 0;
};
/*-------------------------------------------------------------------------------class asm2instr---*/
class TwoAddrCmd : public Command{
public:
  virtual void execute(){code();}
};
/*-------------------------------------------------------------------------------class uFile---*/
class uFile {
public:
	 uFile() {hFile = NULL; }
//	 ~uFile();
	virtual   ~uFile(); // only for disable warning

	int   Open(char* name,int mode);
	int   Close();

	FILE*   operator ~() {return hFile; }

	void   operator =(uFile& src);

enum {fmText=0,fmBin=4,fmRead=0,fmWrite=1,fmAppend=2,fmUpdate=3};
protected:
	FILE*  hFile;
};
/*-------------------------------------------------------------------------------class uBuf---*/
class uBuf{
public:
int i;
int end_;
int startRead;	
int cntSeq;
uBuf(){
    fin.Open("code.asm",uFile::fmText|uFile::fmRead); startRead = _reading; end_ = 0;
    cntSeq = 0;
}

~uBuf(){
  free(pbuff);
}

int _end(){return end_;}
int* size_seq(char* ps);
int init_buf();
char* read_buf();
int clearSeqBack(char* clr);
int clearSeqFrwd(char* clr);

private:
  char* pseq;
  char* pbuff;//указатель на buf
  uFile fin;
};
/*-------------------------------------------------------------------------------class BuildCommand---*/
class BuildCommand{
public:
char* cmd;//текущая команда
unsigned short addr;//текущий адрес
BuildCommand(){addr = 0;}
void showCom(char* pS);
~BuildCommand(){};
private:
//Stack* S;//стек для адресов под команды перехода
};
/*-------------------------------------------------------------------------------class tokenSearch---*/
class tokenSearch{
public:
BuildCommand BC;
int find;
tokenSearch(){find = 0;}
char* searchToken(char* pSeq/*string*/, int* pSzSeq/*size of string*/,char* pSubs/*substring*/, int* pSzSubs/*size of substring*/);
//char* _searchToken(char* pSeq/*string*/, int* pSzSeq/*size of string*/);
char* SingleSearchToken(char* pSeq/*string*/, int* pSzSeq/*size of string*/);
int* size_seq(char* ps);
void showPchar(char* pchar,int* pSz);
/*копирование строк поиска из указателей в массив subs*/
void copyPtrSeq2Arr(char* pS);
void copyPtrSubs2Arr(char* pS);
void copyPtrSeq2Cmd(char* pS);
void clearSeq();//очистка массива seq[]
void clearSubs();//очистка массива subs[]
void showSeq();
void showSubs();
void tokenSearch::showCmd();
};
/*-------------------------------------------------------------------------------class Stack---
class Stack{
private:
void push()//внести в стек два элемента cmd & addr
//Stack(){}//конструктор для стека
public:
char* command[MAX_STACK];
unsigned short* address[MAX_STACK];
};
-------------------------------------------------------------------------------*/