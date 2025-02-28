//main.cpp
#include"instr.cpp"

int main(){
char* pView;
char* pResult;

//SzSeq и _pSzSeq нужны для правильной передачи в метод из main'а
int SzSeq;
int* _pSzSeq;

uBuf bout;
tokenSearch tS;
bout.init_buf();//init buff
_pSzSeq = &SzSeq;

#ifdef showFile
while(bout.end_ == 1){pS = bout.read_buf();
pView = pS;
cout << bout.size_seq(pView) << "\n";}//while
#endif showFile

#ifdef do1
//алгоритм поиска зависает!!!!! 
pS = bout.read_buf();
pView = pS;
SzSeq = *(tS.size_seq(pView));
//cout << "main" << *_pSzSeq;
pResult = tS.SingleSearchToken(pView,_pSzSeq);
//tS.showPchar(pResult,tS.size_seq(pResult));//сбои при выводе
//tS.showSubs();
#endif do1


return 0;
}

