//instr.cpp
#include"header.h"
/*-------------------------------------------------------------------------------uFile methods---*/
uFile::~uFile() {
	Close();
}

int uFile::Open(char* name,int mode) {
	if (hFile) fclose(hFile);
	hFile = fopen(name,modetable[mode&7]);
	if (!hFile) return 1;
	return 0;
}

int uFile::Close() {
	if (hFile) fclose(hFile);
	hFile = 0;
	return 0;
}

void uFile::operator =(uFile& src) {
	hFile = src.hFile;
//	src.hFile = 0;
}
/*-------------------------------------------------------------------------------uBuf methods---*/
int* uBuf::size_seq(char* ps){
int* pRes;
  for(i = 0; i < MAX_SEQ; i++)
      {if(*(ps++) == '\n')break;}//for если символ \0 то результат 13 т.к. \n\0 
return pRes = &i;
}

int uBuf::init_buf(){
  fseek(~fin , 0 , SEEK_END);
  long lSize = ftell(~fin);
  rewind (~fin);

  pbuff = (char*) malloc(sizeof(char)* lSize);
  if (pbuff == NULL)
    {cout << "error memory!" << "\n"; startRead = _stop; return -1;}
  else
  {fread(pbuff, 1, lSize, ~fin); cout << "buff in memory ok!\n"; 
   startRead = _run;
   end_ = _run;
   //pS = seq;//указатель на начальный адрес массива
   return 1;
  }//if else
}

char* uBuf::read_buf(){
  char* pT;
  pT = new char[MAX_SEQ];
  char* _pT;
  _pT = pT;
  while(startRead == 1){
    *pT = *pbuff; cntSeq++;
    //cout << *pT;
    if(*pT == '.'){startRead = _stop; end_ = _stop; break;}//конец файла
    if(*pT == '\n'){pT++;pbuff++;break;}else{pT++;pbuff++;}
  }//while
  pT = _pT;
  if(startRead == -1){
  cout<<"\nRead all buffer!";}
  return pT;
}
/*-------------------------------------------------------------------------------tokenSearch method---*/
char* tokenSearch::searchToken(char* pSeq/*string*/, int* pSzSeq/*size of string*/,char* pSubs/*substring*/, int* pSzSubs/*size of substring*/){
char* _pFnd;
  list<char,allocator<char> > sequence(pSeq, pSeq + *pSzSeq);/*входная строка в ней будем искать*/
  list<char,allocator<char> > subseqnc(pSubs, pSubs + *pSzSubs);/*подстрока поиска, что будем искать*/
  list<char,allocator<char> >::iterator place;/*возвращаемый результат поиска*/

  place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());

  if(*place > 0){find = 1;_pFnd = pSubs;}else{find = -1;_pFnd = NULL;}
  return _pFnd;
}

void tokenSearch::showPchar(char* pchar,int* pSz){
//  pSz = size_seq(pchar);
  for(int i = 0; i < *pSz; i++)
    {cout << *(pchar++);}//for
}//

/*
char* tokenSearch::_searchToken(char* pSeq, int* pSzSeq){
const int* pSz;
char* pSubs;//substring
char* pElem;//WORKING POINTER
char* pFnd;return
int subSize, seqSize;
seqSize = *pSzSeq;
  pArrOfCmd = arrOfCmd;//указатель на указатель массивов
  pSz = &sizeArrOfCmd;//число элементов в массиве массивов
  _while = 0;
  while(_while != *pSz){//просматривает массив arrOfCmd //заменил в операторе while != на >  
    for(int i = 0; i < *pSz; i++){
      pElemArrOfCmd = pArrOfCmd[i];
       for(int j = 0; j < cmd1size; j++){
       }//for j      
    }//for i
  }//while
return pFnd;//вернуть указатель на найденый элемент - строку
}
*/

char* tokenSearch::SingleSearchToken(char* pSeq/*string*/, int* pSzSeq/*size of string*/){
const int* pSz;
char* pSubs;/*substring*/
char* pElem;/*WORKING POINTER*/
char* pFnd;/*return*/
int subSize, seqSize, cmdSize;
seqSize = *pSzSeq;
  pArrOfCmd = arrOfCmd;//указатель на указатель массивов
  pSz = &sizeArrOfCmd;//число элементов в массиве массивов
  pFnd = NULL;
_while = 0;

  while(_while != *pSz){//просматривает массив arrOfCmd //заменил в операторе while != на >
    for(int i = 0; i < *pSz; i++){
    pElemArrOfCmd = pArrOfCmd[i];
/*-----------cmd1[]---------------*/
      if(pElemArrOfCmd == cmd1[0]){    
       for(int j = 0; j < cmd1size; j++){
         pElem = cmd1[j];
         pSubs = pElem;
  		 copyPtrSubs2Arr(pSubs);//pSubs -> subseq[]
  		 copyPtrSeq2Arr(pSeq);//pSeq -> seq[]
  		 copyPtrSeq2Cmd(pSeq);//pSeq -> cmd[]  		 
subSize = strlen(subseq);
cmdSize = strlen(cmd);
list<char,allocator<char> >::iterator place;
list<char,allocator<char> > sequence(seq, seq + seqSize);//массив строки (char, char + int) seq[] - виден
list<char,allocator<char> > subseqnc(subseq, subseq + subSize);
#ifdef Search1
  		 place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
		 if((*place > 0) & (cmdSize == subSize)){cout << "\n-->";find = 1;pFnd = pSubs;cout << "j=" << j; break;}//else{find = -1;pFnd = NULL;}//if		 
 		 clearSeq();//заполнение seq[] ' ' пробелами
		 clearSubs();//заполнение 	subseq[] ' ' пробелами	 
#endif Search1
	  }//for j              
      }//if cmd1
if(find > 0)break;
/*-----------cmd2[]---------------*/	  
      if(pElemArrOfCmd == cmd2[0]){    
       for(int j = 0; j < cmd2size; j++){
         pElem = cmd2[j];
         pSubs = pElem;
  		 copyPtrSubs2Arr(pSubs);//pSubs -> subseq[]
  		 copyPtrSeq2Arr(pSeq);//pSeq -> seq[]
  		 copyPtrSeq2Cmd(pSeq);//pSeq -> cmd[]  		 
subSize = strlen(subseq);
cmdSize = strlen(cmd);
list<char,allocator<char> >::iterator place;
list<char,allocator<char> > sequence(seq, seq + seqSize);//массив строки (char, char + int) seq[] - виден
list<char,allocator<char> > subseqnc(subseq, subseq + subSize);
#ifdef Search2
  		 place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
		 if((*place > 0) & (cmdSize == subSize)){cout << "\n-->";find = 1;pFnd = pSubs;cout << "j=" << j; break;}//else{find = -1;pFnd = NULL;}//if		 
 		 clearSeq();//заполнение seq[] ' ' пробелами
		 clearSubs();//заполнение 	subseq[] ' ' пробелами	 
#endif Search2
	  }//for j              
      }//if cmd2
if(find > 0)break;
/*-----------cmd3[]---------------*/	  
      if(pElemArrOfCmd == cmd3[0]){    
       for(int j = 0; j < cmd3size; j++){
         pElem = cmd3[j];
         pSubs = pElem;
  		 copyPtrSubs2Arr(pSubs);//pSubs -> subseq[]
  		 copyPtrSeq2Arr(pSeq);//pSeq -> seq[]
  		 copyPtrSeq2Cmd(pSeq);//pSeq -> cmd[]
subSize = strlen(subseq);
cmdSize = strlen(cmd);
list<char,allocator<char> >::iterator place;
list<char,allocator<char> > sequence(seq, seq + seqSize);//массив строки (char, char + int) seq[] - виден
list<char,allocator<char> > subseqnc(subseq, subseq + subSize);
#ifdef Search3
  		 place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
		 if((*place > 0) & (cmdSize == subSize)){cout << "\n-->";find = 1;pFnd = pSubs;cout << "j=" << j; break;}//else{find = -1;pFnd = NULL;}//if		 
 		 clearSeq();//заполнение seq[] ' ' пробелами
		 clearSubs();//заполнение 	subseq[] ' ' пробелами	 
#endif Search3
	  }//for j              
      }//if cmd3
if(find > 0)break;
/*-----------cmd4[]---------------*/	  
      if(pElemArrOfCmd == cmd4[0]){    
       for(int j = 0; j < cmd4size; j++){
         pElem = cmd4[j];
         pSubs = pElem;
  		 copyPtrSubs2Arr(pSubs);//pSubs -> subseq[]
  		 copyPtrSeq2Arr(pSeq);//pSeq -> seq[]
  		 copyPtrSeq2Cmd(pSeq);//pSeq -> cmd[]
subSize = strlen(subseq);
cmdSize = strlen(cmd);
list<char,allocator<char> >::iterator place;
list<char,allocator<char> > sequence(seq, seq + seqSize);//массив строки (char, char + int) seq[] - виден
list<char,allocator<char> > subseqnc(subseq, subseq + subSize);
#ifdef Search4
  		 place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
		 if((*place > 0) & (cmdSize == subSize)){cout << "\n-->";find = 1;pFnd = pSubs;cout << "j=" << j; break;}//else{find = -1;pFnd = NULL;}//if		 
 		 clearSeq();//заполнение seq[] ' ' пробелами
		 clearSubs();//заполнение 	subseq[] ' ' пробелами	 
#endif Search4
	  }//for j              
      }//if cmd4
if(find > 0)break;
/*-----------cmd5[]---------------*/	  
      if(pElemArrOfCmd == cmd5[0]){    
       for(int j = 0; j < cmd5size; j++){
         pElem = cmd5[j];
         pSubs = pElem;
  		 copyPtrSubs2Arr(pSubs);//pSubs -> subseq[]
  		 copyPtrSeq2Arr(pSeq);//pSeq -> seq[]
  		 copyPtrSeq2Cmd(pSeq);//pSeq -> cmd[]
subSize = strlen(subseq);
cmdSize = strlen(cmd);
list<char,allocator<char> >::iterator place;
list<char,allocator<char> > sequence(seq, seq + seqSize);//массив строки (char, char + int) seq[] - виден
list<char,allocator<char> > subseqnc(subseq, subseq + subSize);
#ifdef Search5
  		 place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
		 if((*place > 0) & (cmdSize == subSize)){cout << "\n-->";find = 1;pFnd = pSubs;cout << "j=" << j; break;}//else{find = -1;pFnd = NULL;}//if		 
 		 clearSeq();//заполнение seq[] ' ' пробелами
		 clearSubs();//заполнение 	subseq[] ' ' пробелами	 
#endif Search5
	  }//for j              
      }//if cmd5
if(find > 0)break;
/*-----------cmd6[]---------------*/	  
      if(pElemArrOfCmd == cmd6[0]){    
       for(int j = 0; j < cmd6size; j++){
         pElem = cmd6[j];
         pSubs = pElem;
  		 copyPtrSubs2Arr(pSubs);//pSubs -> subseq[]
  		 copyPtrSeq2Arr(pSeq);//pSeq -> seq[]
  		 copyPtrSeq2Cmd(pSeq);//pSeq -> cmd[]
subSize = strlen(subseq);
cmdSize = strlen(cmd);
list<char,allocator<char> >::iterator place;
list<char,allocator<char> > sequence(seq, seq + seqSize);//массив строки (char, char + int) seq[] - виден
list<char,allocator<char> > subseqnc(subseq, subseq + subSize);
#ifdef Search6
  		 place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
		 if((*place > 0) & (cmdSize == subSize)){cout << "\n-->";find = 1;pFnd = pSubs;cout << "j=" << j; break;}//else{find = -1;pFnd = NULL;}//if		 
 		 clearSeq();//заполнение seq[] ' ' пробелами
		 clearSubs();//заполнение 	subseq[] ' ' пробелами	 
#endif Search6
	  }//for j              
      }//if cmd6
if(find > 0)break;
/*-----------cmd7[]---------------*/	  
      if(pElemArrOfCmd == cmd7[0]){    
       for(int j = 0; j < cmd7size; j++){
         pElem = cmd7[j];
         pSubs = pElem;
  		 copyPtrSubs2Arr(pSubs);//pSubs -> subseq[]
  		 copyPtrSeq2Arr(pSeq);//pSeq -> seq[]
  		 copyPtrSeq2Cmd(pSeq);//pSeq -> cmd[]
subSize = strlen(subseq);
cmdSize = strlen(cmd);
list<char,allocator<char> >::iterator place;
list<char,allocator<char> > sequence(seq, seq + seqSize);//массив строки (char, char + int) seq[] - виден
list<char,allocator<char> > subseqnc(subseq, subseq + subSize);
#ifdef Search7
  		 place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
		 if((*place > 0) & (cmdSize == subSize)){cout << "\n-->";find = 1;pFnd = pSubs;cout << "j=" << j; break;}//else{find = -1;pFnd = NULL;}//if		 

 		 clearSeq();//заполнение seq[] ' ' пробелами
		 clearSubs();//заполнение 	subseq[] ' ' пробелами	 
#endif Search7
	  }//for j              
      }//if cmd7
if(find > 0)break;
/*-----------cmd8[]---------------*/	  
      if(pElemArrOfCmd == cmd8[0]){    
       for(int j = 0; j < cmd8size; j++){
         pElem = cmd8[j];
         pSubs = pElem;
  		 copyPtrSubs2Arr(pSubs);//pSubs -> subseq[]
  		 copyPtrSeq2Arr(pSeq);//pSeq -> seq[]
  		 copyPtrSeq2Cmd(pSeq);//pSeq -> cmd[]
subSize = strlen(subseq);
cmdSize = strlen(cmd);
list<char,allocator<char> >::iterator place;
list<char,allocator<char> > sequence(seq, seq + seqSize);//массив строки (char, char + int) seq[] - виден
list<char,allocator<char> > subseqnc(subseq, subseq + subSize);
#ifdef Search8
  		 place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
		 if((*place > 0) & (cmdSize == subSize)){cout << "\n-->";find = 1;pFnd = pSubs;cout << "j=" << j; break;}//else{find = -1;pFnd = NULL;}//if		 
 		 clearSeq();//заполнение seq[] ' ' пробелами
		 clearSubs();//заполнение 	subseq[] ' ' пробелами	 
#endif Search8
	  }//for j              
      }//if cmd8
if(find > 0)break;
/*-----------cmd9[]---------------*/	  
      if(pElemArrOfCmd == cmd9[0]){    
       for(int j = 0; j < cmd9size; j++){
         pElem = cmd9[j];
         pSubs = pElem;
  		 copyPtrSubs2Arr(pSubs);//pSubs -> subseq[]
  		 copyPtrSeq2Arr(pSeq);//pSeq -> seq[]
  		 copyPtrSeq2Cmd(pSeq);//pSeq -> cmd[]
subSize = strlen(subseq);
cmdSize = strlen(cmd);
list<char,allocator<char> >::iterator place;
list<char,allocator<char> > sequence(seq, seq + seqSize);//массив строки (char, char + int) seq[] - виден
list<char,allocator<char> > subseqnc(subseq, subseq + subSize);
#ifdef Search9
  		 place = std::search(sequence.begin(), sequence.end(),
                 subseqnc.begin(), subseqnc.end());
		 if((*place > 0) & (cmdSize == subSize)){cout << "\n-->";find = 1;pFnd = pSubs;cout << "j=" << j; break;}//else{find = -1;pFnd = NULL;}//if		 
 		 clearSeq();//заполнение seq[] ' ' пробелами
		 clearSubs();//заполнение 	subseq[] ' ' пробелами	 
#endif Search9
	  }//for j              
      }//if cmd9
if(find > 0)break;
    }//for i
    if(find > 0)break;    
    _while++;    
}//while
return pFnd;
}//tokenSearch

void tokenSearch::showSeq(){
cout << "\nseq=";
for(int i = 0; i < MAX_SEQ; i++)
 {
  cout << seq[i];
 }//for i
cout << " ";
}

void tokenSearch::showSubs(){
cout << "\nsubseq=";
for(int i = 0; i < MAX_SUBS; i++)
 {
  cout << subseq[i];
 }//for i
cout << " ";
}

void tokenSearch::showCmd(){
cout << "\nCommand=";
for(int i = 0; i < MAX_SUBS; i++)
 {
  cout << cmd[i];
 }//for i
cout << " ";
}

int* tokenSearch::size_seq(char* ps){
int* pRes; int i;pRes = &i;
  for(i = 0; i < MAX_SEQ; i++)
      {if(*(ps++) == '\n')break;}//for если символ \0 то результат 13 т.к. \n\0 
return pRes;
}

void tokenSearch::copyPtrSeq2Arr(char* pS){
char ch;
for(int i = 0; i < MAX_SEQ; i++)
 {
  ch = pS[i];
  seq[i] = ch;
  if(ch == '\n'){seq[i] = '\n';break;}
 }//for i
};

void tokenSearch::copyPtrSubs2Arr(char* pS){
char ch;
for(int i = 0; i < MAX_SUBS; i++)
 {
  ch = pS[i];
  subseq[i] = ch;
  if(ch == '\n'){seq[i] = '\n';break;}
 }//for i
}

void tokenSearch::clearSeq(){
for(int i = 0; i < MAX_SEQ; i++)
 {
  seq[i] = ' ';
 }//for i
}

void tokenSearch::clearSubs(){
for(int i = 0; i < MAX_SUBS; i++)
 {
  subseq[i] = ' ';
 }//for i
}

void tokenSearch::copyPtrSeq2Cmd(char* pS){
char ch;
for(int i = 0; i < MAX_SUBS; i++)
 {
  ch = pS[i];
  if(ch == ' '){cmd[i] = '\0';break;}else{cmd[i] = ch;}
 }//for i
}
/*-------------------------------------------------------------------------------BuildCommand method---*/
void BuildCommand::showCom(char* pS){

}