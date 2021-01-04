
#include "../src/cxx.h"

/*
	1)	gcc src/stdio.c src/string.c tst/string001.c 	-o bin/x	-Wall -pedantic -Wextra

	2)	sh buildLib.h
		clear  	; gcc tst/string001.c	lib/libcxx.so   -o bin/x	-Wall -Wextra -pedantic

	3)  cls     & cl 	src\stdio.c src\string.c tst\string001.c    /Febin\x.exe 	/utf-8 /WX
    
    4)  wbuildLib.bat
        cls & cl tst\string001.c lib\cxx.lib            /Febin\x.exe    /utf-8 /WX
*/


int main() 
{
/*
    consoleSetUTF8();
     
    char32_t* str1 = U"1) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; 
    
    printf ( "%s\n",cnvS32toWS(str1)) ;

    char16_t* str2 = u"2) ç°§é*èé€ 一周有七天。一周有七天,сказать,غداً في العاشرة و.\n"; 

    fprintf ( stdout, "%s\n",cnvS16toWS(str2)) ;
*/
    char* str3 = "claudio daffra";
/*
    fprintf ( stdout, "3) %s\n",cnvS8toWS(str3) ) ;
*/
	// convert
	fprintf ( stdout,"\n" );
	
	fprintf ( stdout,"(%s)\n",cnvR64toS8(1.8446744073709552e+019L) ) ;
	fprintf ( stdout,"(%s)\n",cnvR32toS8(-1.0737418e+008f) ) ;
	fprintf ( stdout,"(%s)\n",cnvI64toS8(1234567890) ) ;
	fprintf ( stdout,"(%s)\n",cnvPTRtoS8(str3) ) ;
	fprintf ( stdout,"(%s)\n",cnvI80toS8(LLONG_MAX) ) ;
				
    return 0; 
} 



