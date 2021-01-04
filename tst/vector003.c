
#include "../src/gc.h"
#include "../src/mvector.h"
#include "../src/iterator.h"

/*
	1) 	clear  	; gcc src/gc.c tst/vector003.c 			-o   bin/x	-Wall -Wextra -pedantic 

	2) 	sh buildLib.sh
		clear  	; gcc tst/vector003.c	lib/libcxx.so   -o   bin/x	-Wall -Wextra -pedantic
	
	cls     & cl src\gc.c tst\vector003.c       /Febin\x.exe    /WX
*/


int main ( void )
{
    gcStart() ;
   
    // .................................... vector typedef 
 
    printf ( "--- vectorType(int,v1); \n" );

    // vector_ID_d			:	TYPE
    // ID_d					:	TYPE    
	// vector_ID_s			:	struct vector_ID_s
	// vector_ID_t			:	vector_ID_s
	// vector_ID_p			:	vector_ID_t*
	 
    vectorTypeDef(int,v1);
    
    printf ( "vector : data size %zu , struct size %zu , struct size %zu,  struct * size %zu\n"
		,sizeof(vector_v1_d),sizeof(struct vector_v1_s),sizeof(vector_v1_t),sizeof(vector_v1_p) );

    // .................................... vector new
    
    vector_v1_t	v1 ;
    
    vectorAlloc(v1,8) ;

    // .................................... vector size capacity empty
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(v1),vectorCapacity(v1),vectorEmpty(v1)	) ; 
		   
    // .................................... vector push back

    printf ( "--- vectorPushBack( v1 ,10 item ) ; \n" );
    
	for(int i=0;i<10;i++) vectorPushBack( v1 ,i*10 ) ;

    // .................................... iterator
    
    printf ( "--- iterator vector ; \n" );
    
    for ( itVector(v1) it = vectorBegin(v1); it<vectorEnd(v1); it++) 
    {
		printf ( "(%02d)",*it );
	}

    // .................................... iterator
    
    printf ( "\n--- iterator ; \n" );
    
    for ( iterator(v1) it = vectorBegin(v1); it<vectorEnd(v1); it++) 
    {
		printf ( "(%02d)",*it );
	}

    // .................................... distance

    printf ( "\n difference %zu\n",itDistance(vectorBegin(v1),vectorEnd(v1)) )  ;    

    // .................................... dealloc
    
    printf ( "\n--- dealloc v1\n" ) ;  
      
	vectorDealloc(v1);

    // .................................... vector type	

	vectorType(int); // for int* -> typedef int* pint ;
	
	vector_int_t v3, *v4 = new(vector_int_t);
	
	vectorAlloc(v3,8);
	
	vectorAlloc(*v4,8);
	
	delete(v4);	
	
    // ...................................... stop
    
    gcStop() ;

    printf ("\n");
    
	return 0 ;
}



/**/


