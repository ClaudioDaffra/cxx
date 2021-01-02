
#include "../src/gc.h"
#include "../src/mvector.h"


/*
	clear  ; gcc src/gc.c tst/vector002.c -o   bin/x           -Wall -Wextra -pedantic 
	
	cls   ; cl  src\gc.c src\fs.c test\ex_vector_1.c      /Fex.exe    /EHsc /WX
*/


int main ( void )
{
    gcStart() ;
   
    // .................................... vector typedef
 
    printf ( "--- vectorType(int,v1);\n" );

    // vector_ID_d			:	TYPE
	// vector_ID_s			:	struct vector_ID_s
	// vector_ID_t			:	vector_ID_s
	// vector_ID_p			:	vector_ID_t*
	 
    vectorTypeDef(int,v1);
    
    printf ( "vector : data size %zu , struct size %zu , struct size %zu,  struct * size %zu\n"
		,sizeof(vector_v1_d),sizeof(struct vector_v1_s),sizeof(vector_v1_t),sizeof(vector_v1_p) );

    // .................................... vector new
    
    vector_v1_t	*v1 = new(vector_v1_t);
    
    vectorAlloc(*v1,8) ;

    // .................................... vector size capacity empty
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)	) ; 

    // .................................... vector push back
    
    printf ( "--- vectorPushBack( *v1 ,10 ) ; \n" );
    
    vectorPushBack( *v1 ,5 ) ;
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)	) ; 

    printf ( "--- vectorPushBack( v1 ,10 item ) ; \n" );
    
	for(int i=0;i<10;i++) vectorPushBack( *v1 ,i*11 ) ;

    // .................................... vector pop back
    
    printf ( "--- vectorPop( *v1 ) ; \n" );

    vectorPopBack( *v1 ) ;
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)	) ;  

    // .................................... vector front back at
    
    printf ( "--- vector front %d back %d  at[3]=%d; \n",vectorFront(*v1),vectorBack(*v1),vectorAt(*v1,3) );

    // .................................... iterator
    
    printf ( "--- iterator ; \n" );
    
    for ( itVector(v1) it = vectorBegin(*v1); it<vectorEnd(*v1); it++) 
    {
		printf ( "(%02d)",*it );
	}
    printf ( "\n" );   
    for ( itVector(v1) it = vectorRBegin(*v1); it>vectorREnd(*v1); it--) 
    {
		printf ( "(%02d)",*it );
	}
    printf ( "\n" );   

	// .................................... shrink to fit

	printf ( "--- shrink to fit *v1\n" ) ; 
	vectorShrinkToFit(*v1);
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)	) ;
        
	// .................................... reserve

	printf ( "--- reserve *v1\n" ) ; 
	vectorReserve(*v1,16);
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)	) ;

    // .................................... sort
    
    printf ( "--- sort \n" );   
     
    vectorSort(vector_v1_d,*v1,gcCompareInt);

    for ( itVector(v1) it = vectorBegin(*v1); it<vectorEnd(*v1); it++)   printf ( "[%02d]" ,*it ) ; 
    printf ( "\n" ); 

    // .................................... binary search
     
    vector_v1_d key = 88 ;
    vector_v1_d* value = (vector_v1_d*)vectorBinarySearch(vector_v1_d,*v1,gcCompareInt,key ) ;
    if ( value != NULL ) printf ( "found %d in vector.\n" ,key) ; else printf ( "not found %d in vector.\n" ,key);
       	
    // .................................... dealloc
    
    printf ( "--- dealloc *v1\n" ) ;    
	vectorDealloc(*v1);
	
    // ...................................... delete
    
    delete(v1) ;
           	    		        
    // ...................................... stop
    
    gcStop() ;

    printf ("\n");
    
	return 0 ;
}



/**/


