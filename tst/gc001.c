
#include "../src/cxx.h"

/*
  
    1)	clear	; gcc src/gc.c tst/gc001.c    	-o bin/x	    -Wall -pedantic -Wextra 

	2)	sh buildLib.sh
		clear	; gcc tst/gc001.c lib/libcxx.so	-o bin/x 	    -Wall -pedantic -Wextra

    3)  cls & cl src\gc.c tst\gc001.c           /Febin\x.exe    /WX /utf-8
    
    4)  wbuildLib.bat
        cls & cl tst\gc001.c lib\cxx.lib        /Febin\x.exe    /WX /utf-8

*/

// ........................................... MAIN

int main()
{
	// .......................... start garbage collector
	
	gcStart();

	// .......................... malloc
	
	int* a1 = gcMalloc(sizeof(int)*1000 ) ;

	(void)a1;

	long* a2 = gcMalloc( sizeof(long)*10 ) ;
	
	// .......................... free
			
	gcFree(a2);

	a2 = gcMalloc( sizeof(long)*410 ) ;

	a2 =  gcRealloc( a2,sizeof(long)*500 );

	// .......................... print
	
	gcPrint();

	// .......................... file open
	
	FILE* fi = gcFileOpen("tst/data.txt","r");
	
	(void)fi ;
	
	gcFileClose(fi) ;
	
	gcFree(a2);
	
	gcFree(a2); // double free !!
		
	// .......................... file temp

    FILE * ft=gcFileTemp();
    
    (void)ft ;
    
	// .......................... stop garbage collector
	
	gcStop();

	return 0;
}
