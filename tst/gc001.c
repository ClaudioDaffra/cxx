
#include "../lib/gc.h"

/*
 * 	gcc lib/gc.c tst/gc001.c -o bin/x
 *  valgrind ./bin/x
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
	
	gcFree(a2);

	gcStop();

	return 0;
}
