
#include "../src/cxx.h"

/*
	1)	gcc src/stdio.c src/string.c tst/string002.c 	-o bin/x	-Wall -pedantic -Wextra

	2)	sh buildLib.h
		clear  	; gcc tst/string002.c	lib/libcxx.so   -o bin/x	-Wall -Wextra -pedantic

	3)  cls     & cl 	src\stdio.c src\string.c tst\string002.c    /Febin\x.exe 	/utf-8 /WX
    
    4)  wbuildLib.bat
        cls & cl tst\string002.c lib\cxx.lib            /Febin\x.exe    /utf-8 /WX
*/


int main() 
{
    consoleSetUTF8();
     
    char32_t* str1 = U"1) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; 
    
    wprintf ( L"%ls\n",cnvS32toWS(str1)) ;

    char16_t* str2 = u"2) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; 

    fwprintf ( stdout, L"%ls\n",cnvS16toWS(str2)) ;

    char* str3 = "claudio daffra";

    fwprintf ( stdout, L"3) %ls\n",cnvS8toWS(str3) ) ;

	// convert
	fwprintf ( stdout,L"\n" );
	
	fwprintf ( stdout,L"(%ls)\n",cnvR64toWS(1.8446744073709552e+019L) ) ;
	fwprintf ( stdout,L"(%ls)\n",cnvR32toWS(-1.0737418e+008f) ) ;
	fwprintf ( stdout,L"(%ls)\n",cnvI64toWS(1234567890) ) ;
	fwprintf ( stdout,L"(%ls)\n",cnvPTRtoWS(str1) ) ;
	fwprintf ( stdout,L"(%ls)\n",cnvI80toWS(LLONG_MAX) ) ;
				
    return 0; 
} 


