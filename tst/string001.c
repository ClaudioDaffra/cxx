
#include "../src/string.h"

//	gcc src/string.c tst/string001.c 	-o bin\x 		-Wall -pedantic -Wextra
//	cl 	src\stdio.c  tst\string001 		/Febin\x.exe 	/utf-8

// ...................................................................

int main() 
{
    setlocale(LC_ALL,"");
     
    char32_t* str1 = U"1) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; 
    
    wprintf ( L"%ls\n",cnvS32toWS(str1)) ;

    char16_t* str2 = u"2) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; 

    fwprintf ( stdout, L"%ls\n",cnvS16toWS(str2)) ;

    wchar_t* str3 = L"3) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; 

    fwprintf ( stdout, L"%hs\n",cnvWStoS8(str3)) ;
    
    char* str4 = "claudio daffra";

    fwprintf ( stdout, L"4) %ls\n",cnvS8toWS(str4) ) ;

    return 0; 
} 



