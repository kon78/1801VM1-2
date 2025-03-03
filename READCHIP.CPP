#include <stdio.h>

class uFile{
  public:
  uFile() {hFile = NULL; }
  //~uFile();

  virtual   ~uFile(); // only for disable warning

  int   Open(char* name,int mode);
  int   Close();

  FILE*   operator ~() {return hFile; }

  void   operator =(uFile& src);

enum {fmText=0,fmBin=4,fmRead=0,fmWrite=1,fmAppend=2,fmUpdate=3};
protected:
	FILE*  hFile;
};

char  modetable[8][4] = {"rt","wt","at","r+t","rb","wb","ab","r+b"};


uFile::~uFile() {
	Close();
}

int
uFile::Open(char* name,int mode) {
	if (hFile) fclose(hFile);
	hFile = fopen(name,modetable[mode&7]);
	if (!hFile) return 1;
	return 0;
}

int
uFile::Close() {
	if (hFile) fclose(hFile);
	hFile = 0;
	return 0;
}

void
uFile::operator =(uFile& src) {
	hFile = src.hFile;
//	src.hFile = 0;
}

 void main(int argc,char* argv[]) {
	uFile  fin, fout;
	if (argc<3) {
		printf("Usage: readchip <binary-file> <text-file>\n");
		return;
	}
	if (fin.Open(argv[1],uFile::fmBin|uFile::fmRead)) {
		printf("Error open input file\n");
		return;
	}
	if (fout.Open(argv[2],uFile::fmBin|uFile::fmWrite)) {
		printf("Error open output file\n");
		return;
	}
	unsigned short LB,HB,buf[512];
	int  size;
	int  n = 0;
	int  addr = 0;
	while (size=fread(buf,1,512,~fin),size>0) {
		for (int i=0;i<size;i++) {
			n=n++;LB = buf[i];LB=LB&0xff;
			n=n++;HB = buf[i];HB=HB&0xff00;HB=HB>>8;
			if(HB==0X28&LB==0x28){
			  fprintf(~fout,"%d",LB);
			  fprintf(~fout,",");
			  fprintf(~fout,"%d",HB);
			  fprintf(~fout,"//");
			  fprintf(~fout,"%d",n);
			  return;}else{
			  fprintf(~fout,"%d",LB);
			  fprintf(~fout,",");
			  fprintf(~fout,"%d",HB);
			  fprintf(~fout,",");}
		}
	}

}
