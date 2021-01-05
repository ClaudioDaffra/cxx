
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
    char* str3 = "claudio daffra";

	// convert
	fprintf ( stdout,"\n" );
	
	fprintf ( stdout,"(%s)\n",cnvR64toS8(DBL_MAX) ) ;
	fprintf ( stdout,"(%s)\n",cnvR32toS8(FLT_MAX) ) ;

	fprintf ( stdout,"(%s)\n",cnvPTRtoS8(str3) ) ;
	
	fprintf ( stdout,"(%s)\n",cnvI80toS8(LLONG_MAX) 	) ;
	fprintf ( stdout,"(%s)\n",cnvI64toS8(LONG_MAX) 		) ;	
	fprintf ( stdout,"(%s)\n",cnvI32toS8(INT_MAX) 		) ;
	fprintf ( stdout,"(%s)\n",cnvI16toS8(SHRT_MAX) 		) ;
	
    #ifdef _MSC_VER
        SetConsoleOutputCP( 65001 );
        char* x= NULL ;
        x = cnvWStoS8(L"[你好吗]\r\n") ; 
        fprintf ( stdout,"%hs"  ,x ) ;
    #else
        char* x = cnvWStoS8(L"你好吗") ;
        printf ( "[%hs]\n",x ) ;
    #endif

    printf("\nthat's al folks !\n");
    
    return 0; 
} 



