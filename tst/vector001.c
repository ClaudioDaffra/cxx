
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

    // .................................... front back 

    printf ( "\n --- vectorFront(v3[2]);" ) ;
    printf ( "\n --- vectorBack(v3[2]);" ) ;

    printf ( "\nv3[2] :: vectorFront(v3[2]) :=%d."  , vectorFront(v3[2]) );  // 123
    printf ( "\nv3[2] :: vectorBack(v3[2])  :=%d."  , vectorBack (v3[2]) );  // 456    

    // .................................... clear

    printf ( "\n --- vectorClear(v1) ;" ) ;
    
    vectorClear(v1) ;
    
    // .................................... iterator
   
    for ( int i=0; i<10 ; i++)
    {
        vectorPushBack( v1, i*2 ) ;
    }

    printf ( "\n --- itVector(v1) itv1 ;" ) ;
    
    itVector(v1) itv1 ;
    
    printf ( "\n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ;

    printf ( "\n" );
    for( itv1 = vectorRBegin(v1) ; itv1 != vectorREnd(v1); itv1-- ) printf ( "[%d]" ,*itv1 ) ;

    // .................................... shrink to fit

    printf ( "\n --- vectorShrinkToFit(v1);" ) ;
    
    vectorShrinkToFit(v1);

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );      



    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) ); 

    // .................................... insert At

    printf ( "\n --- vectorInsertAtVal(v1,3,12);" ) ;
  
    vectorInsertAtVal(v1,3,123);  
 
    printf ( "\n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 
    
    // .................................... erase At 

    printf ( "\n --- vectorEraseAt(v1,4);" ) ;
    
    vectorEraseAt(v1,4);

    printf ( "\n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 

    // .................................... erase At N

    printf ( "\n --- vectorEraseAtN(v1,4,2);" ) ;
    
    vectorEraseAtN(v1,4,2);

    printf ( "\n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 

    // .................................... erase At N

    printf ( "\n --- vectorResize(v1,16,0);" ) ;
    
    vectorResize(v1,16,0);

    printf ( "\nv1 :: size %d capacity %d.", (int)vectorSize(v1) , (int)vectorCapacity(v1) );
    printf ( "\n" );    
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 

    // .................................... copy
     
    vectorCopy ( v3[2] , v1 ) ;
    
    printf ( "\n" ); 
    //for( unsigned int i=0; i<vectorSize(v3[2]) ; i++  )   printf ( "[%d]" ,v3[2].data[i] ) ; 
    for( unsigned int i=0; i<vectorSize(v3[2]) ; i++  )   printf ( "[%d]" ,vectorAt(v3[2],i) ) ; 

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
 
    // .................................... sort
    
    vectorSort(v1,gcCompareInt);

    printf ( "\n sort \n" );
    for( itv1 = vectorBegin(v1) ; itv1 != vectorEnd(v1); itv1++ )   printf ( "[%d]" ,*itv1 ) ; 
    
    // .................................... free

    printf ( "\n --- vectorFree( ... ) ;" ) ;

    vectorFree( v1 ) ;
    vectorFree( v2 ) ;    
    vectorFree( v3[2] ) ;   
    //vectorFree( v4 ) ;  
*/

    // .................................... dealloc
    
    printf ( "--- dealloc v1\n" ) ;    
	vectorDealloc(v1);

    // ...................................... stop
    
    gcStop() ;

    printf ("\n");
    
	return 0 ;
}



/**/


