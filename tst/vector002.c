
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
    
    vectorAlloc(*v1,16) ;

    // .................................... vector size capacity empty
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)	) ; 

    // .................................... vector push back
    
    printf ( "--- vectorPushBack( *v1 ,10 ) ; \n" );
    
    vectorPushBack( *v1 ,10 ) ;
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(*v1),vectorCapacity(*v1),vectorEmpty(*v1)	) ; 
    		        
    // ...................................... stop
    
    gcStop() ;

    printf ("\n");
    
	return 0 ;
}



/**/


