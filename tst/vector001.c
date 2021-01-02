
#include "../src/gc.h"
#include "../src/mvector.h"


/*
	clear  ; gcc src/gc.c tst/vector002.c -o   bin/x           -Wall -Wextra -pedantic 
	
	cls   ; cl  src\gc.c tst\vector002.c      /Febin\x.exe    	/EHsc /WX
*/


int main ( void )
{
    gcStart() ;
   
    // .................................... vector typedef 
 
    printf ( "--- vectorType(int,v1); \n" );

    // vector_ID_d			:	TYPE
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
    
    printf ( "--- vectorPushBack( v1 ,10 ) ; \n" );
    
    vectorPushBack( v1 ,5) ;
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(v1),vectorCapacity(v1),vectorEmpty(v1)	) ; 

    printf ( "--- vectorPushBack( v1 ,10 item ) ; \n" );
    
	for(int i=0;i<10;i++) vectorPushBack( v1 ,i*10 ) ;

    // .................................... vector pop back
    
    printf ( "--- vectorPopBack( v1 ) ; \n" );

    vectorPopBack( v1 ) ;
    
    printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(v1),vectorCapacity(v1),vectorEmpty(v1)	) ;   

    // .................................... vector front back at
    
    printf ( "--- vector front %d back %d  at[3]=%d; \n",vectorFront(v1),vectorBack(v1),vectorAt(v1,3) );

    // .................................... iterator
    
    printf ( "--- iterator ; \n" );
    
    for ( itVector(v1) it = vectorBegin(v1); it<vectorEnd(v1); it++) 
    {
		printf ( "(%02d)",*it );
	}
    printf ( "\n" );   
    for ( itVector(v1) it = vectorRBegin(v1); it>vectorREnd(v1); it--) 
    {
		printf ( "(%02d)",*it );
	}
    printf ( "\n" );   
    
	// .................................... shrink to fit

	printf ( "--- shrink to fit v1\n" ) ; 
	vectorShrinkToFit(v1);
	printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(v1),vectorCapacity(v1),vectorEmpty(v1)	) ;  
	  
	// .................................... reserve

	printf ( "--- reserve v1\n" ) ; 
	vectorReserve(v1,16);
	printf ( "vector : size %zu capacity %zu empty %d.\n",vectorSize(v1),vectorCapacity(v1),vectorEmpty(v1)	) ; 

    // .................................... sort
    
    printf ( "--- sort \n" );   
     
    vectorSort(vector_v1_d,v1,gcCompareInt);

    for ( itVector(v1) it = vectorBegin(v1); it<vectorEnd(v1); it++)   printf ( "[%02d]" ,*it ) ; 
    printf ( "\n" ); 

    // .................................... binary search
     
    vector_v1_d key = 80 ;
    vector_v1_d* value = (vector_v1_d*)vectorBinarySearch(vector_v1_d,v1,gcCompareInt,key ) ;
    if ( value != NULL ) printf ( "found %d in vector.\n" ,key) ; else printf ( "not found %d in vector.\n" ,key);

    // .................................... insert erase eraseN
        
    printf ( "--- insert at 3 33 \n" );  
    vectorInsertAtVal(v1,3,33); 
        
    printf ( "--- erase at 2 \n" );  
    vectorEraseAt(v1,2); 

    printf ( "--- erase at 4 n.3 elements \n" );  
    vectorEraseAtN(v1,4,3);
        
    for ( itVector(v1) it = vectorBegin(v1); it<vectorEnd(v1); it++)   printf ( "[%02d]" ,*it ) ; 
    printf ( "\n" ); 

    // .................................... resize

    printf ( "--- resize > 8,0\n" );  
    vectorResize(v1,8,0); 
	printf ( "vector v1 : size %zu capacity %zu empty %d.\n",vectorSize(v1),vectorCapacity(v1),vectorEmpty(v1)	) ;
    for ( itVector(v1) it = vectorBegin(v1); it<vectorEnd(v1); it++)   printf ( "[%02d]" ,*it ) ; 
    printf ( "\n" ); 	
    
	// .................................... new vector

    printf ( "--- new vector copy append\n" );
    
	vectorTypeDef(int,v2);

	vector_v1_t	*v2 = new(vector_v2_t);

	vectorAlloc(*v2,8) ; // always allocated first

	vectorCopy( *v2 ,v1 ) ;
	vectorAppend( *v2 ,v1 ) ;
		
	printf ( "vector *v2 : size %zu capacity %zu empty %d.\n",vectorSize(*v2),vectorCapacity(*v2),vectorEmpty(*v2)	) ; 

	vectorPrintf("(%02d)",*v2);
    printf("\n");
    
	// .................................... insert vector

    printf ( "--- vectorInsertAtVector(*v2,5,v1); \n" );
    
    //  v1 [00][05][33][20][60][70][80]
    // *v2 [00][05][33][20][60][70][80][00][00][05][33][20][60][70][80][00] 
    // *v2 [00][05][33][20][60]		[00][05][33][20][60][70][80]	[00][70][80][00][00][05][33][20][60][70][80][00]
    
    vectorInsertAtVector(*v2,5,v1);
    
	vectorPrintf("(%02d)",*v2);
	printf ( "\n" ); 	 

    //  v1 [00][05][33]	-	[20][60][70][80]
    // *v2 [00][05][33]		[20][60][00][05][33]	[20][60][70][80][00][70][80][00][00][05][33][20][60][70][80][00]
    //  v1 (00)(05)(33)		(20)(60)(00)(05)(33)	(20)(60)(70)(80)(00)	
    
	vectorInsertAtVectorFromN(v1, 3, *v2 , 3 , 5 );

	vectorPrintf("(%02d)",v1);
	printf ( "\n" ); 
			                                                                       	
/*   
    // .................................... vector of vector
 
;
    
    printf ( "\nv2 :: size %d capacity %d.", (int)vectorSize(v2) , (int)vectorCapacity(v2) );   

    printf ( "\n --- vectorAt(vectorAt(v2,0),0)) " ) ;
    
    printf ( "\nv2 :: vectorAt(vectorAt(v2,0),0)):=%d.", vectorAt(vectorAt(v2,0),0)    );  // 10
    printf ( "\nv2 :: vectorAt(vectorAt(v2,0),0)):=%d.", vectorXY(v2,0,0)              );  // 10
 
    // .................................... array of vector 


    printf ( "\n --- vectorPushBack( v3[2] ,123 ) ;" ) ;
    printf ( "\n --- vectorPushBack( v3[2] ,456 ) ;" ) ;
 
    vectorPushBack( v3[2] ,123 ) ;
    vectorPushBack( v3[2] ,456 ) ;
    
    printf ( "\nv3[2] :: size %d capacity %d.", (int)vectorSize(v3[2]) , (int)vectorCapacity(v3[2]) );   
    
    printf ( "\nv3[2] :: vectorAt(v3[2],0):=%d.", vectorAt(v3[2],0) );  // 123
    printf ( "\nv3[2] :: vectorAt(v3[2],1):=%d.", vectorAt(v3[2],1) );  // 456    

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );      

    // .................................... Append

    printf ( "\n --- vectorType(int,v4);" ) ;

    vectorType(int,v4);

    vectorNew( v4 , 128 );
    
    vectorAppend( v4,v1 ) ;
  
    itVector(v4) itv4; // vectorDataType ## ID* ... vectorDataTypev4 *itv4
    
    printf ( "\nv4 :: size %d capacity %d.", (int)vectorSize(v4) , (int)vectorCapacity(v4) );
    printf ( "\n" );    
    for( itv4 = vectorBegin(v4) ; itv4 != vectorEnd(v4); itv4++ )   printf ( "[%d]" ,*itv4 ) ; 
  
    // .................................... insert at vector

    printf ( "\n --- vectorInsertAtVector(v1, 2, v4 ) ;" ) ;
 
    vectorInsertAtVector(v1, 2, v4 ) ; 

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );
    printf ( "\n" );    
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 
 
    // .................................... insert at vector from and for

    printf ( "\n --- vectorInsertAtVectorFromN(v1, 2, v4 ,2, 2) ;" ) ;
    
    vectorInsertAtVectorFromN(v1, 2, v4 ,2, 2) ;

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );
    printf ( "\n" );    
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 
 
*/

    // .................................... dealloc
    
    printf ( "--- dealloc v1\n" ) ;    
	vectorDealloc(v1);
	
	vectorDealloc(*v2);
	delete(v2);
	
    // ...................................... stop
    
    gcStop() ;

    printf ("\n");
    
	return 0 ;
}



/**/


