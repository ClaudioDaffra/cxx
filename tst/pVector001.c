#include <stdio.h>
#include "../lib/gc.h"
#include "../lib/pVector.h"

// clear  ; gcc lib/gc.c tst/pVector001.c -o bin/x -Wall -pedantic -Wextra
// valgrind ./bin/x
// cppcheck tst/pVector001.c



int main ( void ) 
{
	// .............. START
	
	gcStart();

	// ................................................... vector stack
	
	pVectorStruct( int8t , vectorInt_s ) v1;
	
	
	printf ( "vector size struct %zu.\n",sizeof(v1)) ; 
	printf ( "vector size data   %zu.\n",sizeof(*v1.data)) ; 

	pVectorAlloc(v1,8);

	// ................................................... vector size capacity
		
	printf ( "vector : size (%zu) capacity (%zu) empty(%d) \n",pVectorSize(v1),pVectorCapacity(v1),pVectorIsEmpty(v1) );
	


	// ................................................... vector push back
	
	for(int i=0;i<128;i++) pVectorPushBack(v1,i);

	printf ( "vector : size (%zu) capacity (%zu) empty(%d) \n",pVectorSize(v1),pVectorCapacity(v1),pVectorIsEmpty(v1) ) ;

	printf ( "vector[3]==%d\n",pVectorAt(v1,3) ) ;
	
	pVectorDealloc(v1);		

	//pVectorDealloc(v1);	 TODO check with garbage collector
		
	//
	
	
	
	
	// ................................................... vector heap
		
	pVectorStruct( int8t  , pvectorInt_s ) *pv1 = new(struct pvectorInt_s) ;
	
	
	printf ( "vector size struct %zu.\n",sizeof(*pv1)) ; 
	printf ( "vector size data   %zu.\n",sizeof(*pv1->data)) ; 	

	pVectorAlloc(*pv1,8);

	// ................................................... vector size capacity
		
	printf ( "vector : size (%zu) capacity (%zu) empty(%d) \n",pVectorSize(*pv1),pVectorCapacity(*pv1),pVectorIsEmpty(*pv1) );

	// ................................................... vector push back
	
	for(int i=0;i<128;i++) pVectorPushBack(*pv1,i);

	printf ( "vector size (%zu) capacity (%zu) empty(%d) \n",pVectorSize(*pv1),pVectorCapacity(*pv1),pVectorIsEmpty(*pv1) );

	printf ( "vector[3]==%d\n",pVectorAt(*pv1,3) ) ;
				
	pVectorDealloc(*pv1);
		
	delete(pv1);

	// .............. END
	
	printf("\n");
	gcStop();
  
  return 0 ;
}
