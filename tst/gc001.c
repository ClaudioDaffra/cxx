
#include "../lib/gc.h"

/*
 * 	gcc lib/gc.c tst/gc001.c -o bin/x
 *  valgrind ./bin/x
 *  cl lib\gc.c tst\gc001.c /Febin\x.exe
 */

// ........................................... MAIN

int main()
{
	gcStart();

	int* a1 = gcMalloc(sizeof(int)*10 ) ;

	long* a2 = gcMalloc( sizeof(long)*10 ) ;
		
	gcFree(a2);

	a2 = gcMalloc( sizeof(long)*410 ) ;

	a2 =  gcRealloc( a2,sizeof(long)*500 );

	gcPrint(gc);
	
	FILE* fi = gcFileOpen("tst/data.txt","r");
	
	gcFileClose(fi) ;
	
	gcFree(a2);
//
    FILE * ft=gcFileTemp();
    
//
	gcStop();

	return 0;
}
