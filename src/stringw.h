#ifndef mwstring8
#define mwstring8

#include "cxx.h"

//.................................................... [] wstring(TYPE) 

// wstringTypeDef(TYPE,ID)

/*
 
    wstring_ID_d			:	TYPE
    ID_d				:   TYPE
	wstring_ID_s			:	struct wstring_ID_s
	wstring_ID_t			:	wstring_ID_s
	wstring_ID_p			:	wstring_ID_t*
*/

#define wstringTypeDef(TYPE,ID)                         	\
typedef TYPE MERGE ( MERGE ( wstring_ , ID )  , _d );  	\
typedef TYPE MERGE ( ID  , _d );  						\
typedef struct MERGE ( MERGE ( wstring_ , ID )  , _s )	\
{                                                   	\
    TYPE*   data ;                                  	\
    size_t  size        ;                           	\
    size_t  capacity    ;                           	\
}  MERGE ( MERGE ( wstring_ , ID )  , _t ) ;				\
typedef MERGE ( MERGE ( wstring_ , ID )  , _t ) * MERGE ( MERGE ( wstring_ , ID )  , _p );

// wstringType(TYPE,ID) :  generic wstring

#define wstringType(TYPE)	wstringTypeDef(TYPE,TYPE)

// ........................................................... [] wstringAlloc(ID,N) 
 
#define wstringAlloc(ID,N)                        			\
(ID).data = (void*) gcMalloc ( sizeof((ID).data) * N ); 	\
assert((ID).data!=NULL);									\
(ID).size      = 0;                                    		\
(ID).capacity  = N;    
  
// ........................................................... [] SIZE

#define wstringSize(ID) ((ID).size)

// ........................................................... [] CAPACITY

#define wstringCapacity(ID) ((ID).capacity)

// ........................................................... [] EMPTY

#define wstringEmpty(ID) ((ID).size == 0) 

// ........................................................... [] PUSH_BACK

#define wstringPushBack(ID, VAL) do {                                   	\
    if ((ID).size + 1 >= (ID).capacity) {                                	\
        size_t N = ((ID).capacity += (ID).capacity);                     	\
        (ID).data = gcRealloc  ( (ID).data   , (N) * sizeof((ID).data)  );	\
        (ID).capacity = (N);                                             	\
    } ;                                                                     \
    size_t len=wstringSize(ID);                                             \
    (ID).data[len]   = (VAL);                                    	        \
    (ID).data[len+1] = 0    ;                                    	        \
    ++(ID).size ;                                                       	\
} while (0)

// ........................................................... [] POP_BACK

#define wstringPopBack(ID) do {             \
    if ((ID).size) {                        \
        (ID).data[wstringSize(ID)-1] = 0;    \
        --(ID).size ;                       \
    };\
} while (0)

// ........................................................... [] CLEAR

#define wstringClear(ID) do {       \
    (ID).size = 0       ;           \
    (ID).data[0] = 0    ;           \
} while (0)

// ........................................................... [] DATA

#define wstringData(ID) (ID).data


// ........................................................... [] AT 

#define wstringAt(ID, INDEX) (ID).data[INDEX]    

/*
// ........................................................... [] wstringOfwstring ... X , XY , XYZ
    
#define wstringX(ID,NDX1)                wstringAt(ID,NDX1)
#define wstringXY(ID,NDX1,NDX2)          wstringAt(wstringAt(ID,NDX1),NDX2)
#define wstringXYZ(ID,NDX1,NDX2,NDX3)    wstringAt(wstringAt(wstringAt(ID,NDX1),NDX2),NDX3)
*/
// ........................................................... [] FRONT

#define wstringFront(ID) (ID).data[0]

// ........................................................... [] BACK 

#define wstringBack(ID) (ID).data[wstringSize(ID) - 1]

/*
// ........................................................... [] ITERATOR 

#define itWString(ID)        MERGE ( MERGE ( wstring_ , ID )  , _d )*  
 
#define wstringBegin(ID)     (ID).data
#define wstringEnd(ID)       ((ID).data+(ID).size) 

#define wstringRBegin(ID)    ((ID).data + (ID).size - 1)
#define wstringREnd(ID)      ((ID).data - 1 )
*/
// ........................................................... [] SHRINK TO FIT

#define wstringShrinkToFit(ID) do {                                                  \
    (ID).data = gcRealloc  ( (ID).data   , ((ID).size) * sizeof((ID).data)  );      \
    (ID).capacity = (ID).size;                                                      \
} while (0)    

/*
// ........................................................... [] RESERVE 

#define wstringReserve(ID, N) do {                                                   \
    if ((ID).capacity < (N)) {                                                      \
        (ID).data = gcRealloc  ( (ID).data   , (N) * sizeof((ID).data)  );          \
        (ID).capacity = (N);                                                        \
    } \
} while (0)

// ........................................................... [] wstringInsertAtVal     
        
#define wstringInsertAtVal(ID, POS, VAL) do {                                                \
    while ((ID).size + 1 > (ID).capacity) {                                                 \
        (ID).capacity *= 2;                                                                 \
        (ID).data = gcRealloc  ( (ID).data   , (ID).capacity * sizeof((ID).data)  );        \
    } ;                                                                                     \
    memmove((ID).data + POS + 1, (ID).data + POS, ((ID).size - POS) * sizeof((ID).data) );  \
    ++(ID).size;                                                                            \
    (ID).data[POS] = VAL;                                                                   \
} while (0)

// ........................................................... [] ERASE at
                
#define wstringEraseAt(ID, POS) do {                                                         \
    if ( (ID).size ) {                                                                      \
    (ID).size -= 1;                                                                         \
    memmove((ID).data + POS, (ID).data + POS + 1, ((ID).size - POS) * sizeof *(ID).data);   \
    } ;                                                                                     \
} while (0)

// ........................................................... [] ERASE N
        
#define wstringEraseAtN(ID, POS, N) do {                                                         \
    if ( ((ID).size-(N))>0 ) {                                                                  \
    (ID).size -= (N);                                                                           \
    memmove((ID).data + POS, (ID).data + POS + (N), ((ID).size - POS) * sizeof *(ID).data );    \
    }                                                                                           \
} while (0)

// ........................................................... [] RESIZE
    
#define wstringResize(ID, N, VAL) do {                                       \
    if ((N) > (ID).capacity)                                                \
        (ID).data = gcRealloc ( (ID).data ,  (N) * sizeof((ID).data)   );   \
    if ( (ID).size<(N) )                                                    \
        for (int i = (ID).size; i < (N); ++i) (ID).data[i] = (VAL);         \
    (ID).size = (N);                                                        \
} while (0)

// ........................................................... [] COPY V1 <- V2 
 
#define wstringCopy(ID, PTR ) do {                                                               \
    while ((ID).size + (PTR).size > (ID).capacity) {                                            \
        (ID).capacity *= 2;                                                                     \
        (ID).data = gcRealloc ( (ID).data , (ID).capacity * sizeof((ID).data)   );              \
    } ;                                                                                         \
    memmove((ID).data + 0 + (PTR).size, (ID).data + 0, ((ID).size - 0) * sizeof *(ID).data);    \
    for (size_t i = 0; i < (PTR).size; i++)                                                   	\
        (ID).data[0 + i] = (PTR).data[0 + i];                                                   \
    (ID).size = (PTR).size;                                                                     \
} while (0)


// ........................................................... [] APPEND 
 
#define wstringAppend(ID, V2 ) do {                                                      \
    size_t V1z = (ID).size ;                                                          	\
    size_t V2z = (V2).size ;                                                          	\
    if ((ID).capacity < (V1z+V2z)) {                                                    \
        (ID).data = gcRealloc ( (ID).data , (V1z + V2z ) *  sizeof((ID).data) ) ;       \
    }                                                                                   \
    (ID).capacity = V1z + V2z ;                                                         \
    while (V2z > 0) {                                                                   \
        (ID).data[ (V1z + V2z - 1) ] = (V2).data[V2z-1];                                \
        --V2z ;                                                                         \
    }                                                                                   \
    (ID).size = (ID).capacity ;                                                         \
} while (0)

// ........................................................... [] insert wstring at

#define wstringInsertAtwstring(ID, POS, PTR ) do {                                                    \
    while ((ID).size + (PTR).size > (ID).capacity) {                                                \
        (ID).capacity *= 2;                                                                         \
        (ID).data = gcRealloc ( (ID).data , (ID).capacity *  sizeof((ID).data)   );                 \
    }                                                                                               \
    memmove((ID).data + POS + (PTR).size, (ID).data + POS, ((ID).size - POS) * sizeof *(ID).data);  \
    for (size_t i = 0; i < (PTR).size; i++)                                                       	\
        (ID).data[POS + i] = (PTR).data[0 + i];                                                     \
    (ID).size += (PTR).size;                                                                        \
} while (0)

// ........................................................... [] wstringInsertAtwstringFromN( v1, POS1, v2 , POS2 , N )

#define wstringInsertAtwstringFromN(ID, POS, PTR , POS2 , N) do {                                     \
    while ((ID).size + (N) > (ID).capacity) {                                                       \
        (ID).capacity *= 2;                                                                         \
        (ID).data = gcRealloc ( (ID).data , (ID).capacity *  sizeof((ID).data)  );                  \
    } ;                                                                                             \
    memmove((ID).data + POS + (N), (ID).data + POS, ((ID).size - POS) * sizeof *(ID).data);         \
    for (size_t i = 0; i < (N); i++)                                                              	\
        (ID).data[POS + i] = (PTR).data[POS2 + i];                                                  \
    (ID).size += (N);                                                                               \
} while (0)

// ........................................................... [] PRINTF

#define wstringPrintf(FORMAT,ID) do { 												\
for ( size_t i = 0 ; i < (ID).size ; i++)  printf ( FORMAT , (ID).data[i] ) ;		\
}while(0);
*/
// ........................................................... [] FREE 

#define wstringDealloc(ID) do {                        \
    if ( (ID).data != NULL ) gcFree( (ID).data );     \
} while(0)

/*   
// ........................................................... [] SORT 

#define wstringSort(TYPE,ID,CMP)  qsort((ID).data, (ID).size, sizeof(TYPE), CMP )  

// ........................................................... [] BINARY SEARCH 

#define wstringBinarySearch(TYPE,ID,CMP,KEY)  bsearch (&KEY, (ID).data, (ID).size , sizeof (TYPE), CMP) 

// ........................................................... [] wstring ALLLOC wstring 

#define wstringAllocwstring(TYPE,ID,N)                  		\
(ID).data = (void*) gcMalloc ( sizeof(TYPE) * N ); 			\
assert((ID).data!=NULL);									\
(ID).size      = 0;                                    		\
(ID).capacity  = N;	
*/

#endif

 
 
/**/
