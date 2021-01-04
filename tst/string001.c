
#include "../src/stdio.h"
#include "../src/string.h"

//	gcc src/stdio.c src/string.c tst/string001.c 	-o bin\x 		-Wall -pedantic -Wextra
//	cl 	src\stdio.c src\string.c tst\string001.c    /Febin\x.exe 	/utf-8 /WX

// ...................................................................

int main() 
{
    consoleSetUTF8();
     
    char32_t* str1 = U"1) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; 
    
    wprintf ( L"%ls\n",cnvS32toWS(str1)) ;

    char16_t* str2 = u"2) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; 

    fwprintf ( stdout, L"%ls\n",cnvS16toWS(str2)) ;

    char* str3 = "claudio daffra";

    fwprintf ( stdout, L"3) %ls\n",cnvS8toWS(str4) ) ;

    return 0; 
} 



