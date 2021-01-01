
#include "../src/gc.h"

/*
 * 	gcc -Wall -pedantic -Wextra src/gc.c tst/gc001.c -o bin/x
 *  valgrind ./bin/x
 *
 *  cl src\gc.c tst\gc001.c /Febin\x.exe /W4
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
	
	gcFree(a2); // double free !!
		
	// .......................... file temp

    FILE * ft=gcFileTemp();
    
    (void)ft ;
    
	// .......................... stop garbage collector
	
	gcStop();

	return 0;
}
