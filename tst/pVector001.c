#include <stdio.h>
#include "../lib/tgc.h"
#include "../lib/pVector.h"

// gcc tst/pVector001.c lib/tgc.c -o bin/x
// valgrind --undef-value-errors=no ./bin/x

static tgc_t gc;

int main ( int argc , char* argv[] ) 
{
	tgc_start(&gc, &argc);

	// ..............
	
	pVectorStructDef(int , vectorInt_s ) ;
	
	typedef struct vectorInt_s vector_t ;
	
	// ..............

	struct	vectorInt_s v1 ;

	pVectorAlloc( v1 , 128 , int ) ;
				
	printf ( "vector size  %zu capacity %zu\n",pVectorSize(v1),pVectorCapacity(v1) ) ;
	
//	pVectorDeAlloc(v1) ;


	// ..............

	struct	vectorInt_s*  pv2 ; 
		 #define N 128
		 #define TYPE struct	vectorInt_s
		 #define TYPE2 int
	//pVectorNew( pv2 , struct	vectorInt_s , 64  , int ) ;
pv2 			= (TYPE*)tgc_alloc (&gc,sizeof(TYPE));					 
pv2->data		= (TYPE2*)tgc_alloc (&gc,sizeof(TYPE2)*N);			 
pv2->size      = 0;                                   		 
pv2->capacity  = N;	

tgc_free(&gc,pv2->data);
									 
/*
printf ( "size struct	vectorInt_s %zu\n",sizeof(struct	vectorInt_s))  ;
printf ( "size pv2 %zu\n",sizeof(pv2))  ;
printf ( "size pv2.data %zu\n",sizeof(pv2->data))  ;
	
	//(pv2) 		= tgc_alloc (&gc,sizeof(struct	vectorInt_s));	
	//(pv2)->data	= tgc_alloc (&gc,sizeof(pv2)*64);		
	//tgc_free(&gc,(pv2)->data);
*/
/*
	printf ( "vector size  %zu capacity %zu\n",pVectorSize(*pv2),pVectorCapacity(*pv2) ) ;
	
	pVectorDelete( pv2 ) ;
*/					 
	// ..............
	
	tgc_stop(&gc);
  
  return 0 ;
}
