
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
	
		pVectorStruct( signed char , vectorInt_s ) v1;
		
		printf ( "vector v1 : size struct %zu.\n",sizeof(v1)) ; 
		
		printf ( "vector v1 : size data   %zu.\n",sizeof(*v1.data)) ; 

		pVectorAlloc(v1,8);

		// ................................................... vector size capacity
			
		printf ( "vector v1 : size (%zu) capacity (%zu) empty(%d) \n",pVectorSize(v1),pVectorCapacity(v1),pVectorIsEmpty(v1) );

		// ................................................... vector push back
		
		for(int i=0;i<128;i++) pVectorPushBack(v1,i);

		printf ( "vector v1 : size (%zu) capacity (%zu) empty(%d) \n",pVectorSize(v1),pVectorCapacity(v1),pVectorIsEmpty(v1) ) ;

		// ................................................... vector at
		
		printf ( "vector[3]==%d\n",pVectorAt(v1,3) ) ;

		// ................................................... vector dealloc
		
		printf ( "before first  dealloc v1.data==%p\n",v1.data);	
		
		pVectorDealloc(v1);		

		printf ( "before second dealloc v1.data==%p\n",v1.data);	
		
		pVectorDealloc(v1);
		
	//

	// ................................................... vector heap
		
		pVectorStruct( int8t  , pvectorInt_s ) *pv1 = new(struct pvectorInt_s) ;

		printf ( "vector *pv1 : size struct %zu.\n",sizeof(*pv1)) ; 
		
		printf ( "vector *pv1 : size data   %zu.\n",sizeof(*pv1->data)) ; 	

		pVectorAlloc(*pv1,8);

		// ................................................... vector size capacity
			
		printf ( "vector *pv1 : size (%zu) capacity (%zu) empty(%d) \n",pVectorSize(*pv1),pVectorCapacity(*pv1),pVectorIsEmpty(*pv1) );

		// ................................................... vector push back
		
		for(int i=0;i<128;i++) pVectorPushBack(*pv1,i);

		printf ( "vector *pv1 : size (%zu) capacity (%zu) empty(%d) \n",pVectorSize(*pv1),pVectorCapacity(*pv1),pVectorIsEmpty(*pv1) );

		// ................................................... vector at
		
		printf ( "vector[3]==%d\n",pVectorAt(*pv1,3) ) ;

		// ................................................... vector dealloc
						
		printf ( "before first  dealloc *pv1.data==%p\n",pv1->data);	
		
		pVectorDealloc(*pv1);		

		printf ( "before second dealloc *pv1.data==%p\n",pv1->data);	
		
		pVectorDealloc(*pv1);

		// ................................................... vector delete
				
		delete(pv1);

	// ................................................... vector short cut heap

		struct vectorInt_s *	pv2 ;

		pVectorNew( struct vectorInt_s , pv2 , 64 );
	
		printf ( "vector *pv2 : size (%zu) capacity (%zu) empty(%d) \n",pVectorSize(*pv2),pVectorCapacity(*pv2),pVectorIsEmpty(*pv2) );
		
		pVectorDestroy(pv2);
			
	// .............. END
	
	printf("\n");
	gcStop();
  
  return 0 ;
}
