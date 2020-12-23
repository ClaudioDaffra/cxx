
#include "../lib/gc.h"

/*
 * 	gcc -Wall -pedantic -Wextra lib/gc.c tst/gc001.c -o bin/x
 *  valgrind ./bin/x
 *  cl lib\gc.c tst\gc001.c /Febin\x.exe
 */

// ........................................... MAIN

int main()
{
	// .......................... start garbage collector
	
	gcStart();

	// .......................... malloc
	
	int* a1 = gcMalloc(sizeof(int)*10 ) ;

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
	
	// .......................... file temp

    FILE * ft=gcFileTemp();
    
    (void)ft ;
    
	// .......................... stop garbage collector
	
	gcStop();

	return 0;
}
