#ifndef mmbstring8
#define mmbstring8

#include "cxx.h"

//.................................................... [] mbstring(TYPE) 

// mbstringTypeDef(TYPE,ID)

/*
 
    mbstring_ID_d			:	TYPE
    ID_d				:   TYPE
	mbstring_ID_s			:	struct mbstring_ID_s
	mbstring_ID_t			:	mbstring_ID_s
	mbstring_ID_p			:	mbstring_ID_t*
*/

#define mbstringTypeDef(TYPE,ID)                        \
typedef TYPE MERGE ( MERGE ( mbstring_ , ID )  , _d );  \
typedef TYPE MERGE ( ID  , _d );  						\
typedef struct MERGE ( MERGE ( mbstring_ , ID )  , _s )	\
{                                                   	\
    TYPE*   data ;                                  	\
    size_t  size        ;                           	\
    size_t  capacity    ;                           	\
}  MERGE ( MERGE ( mbstring_ , ID )  , _t ) ;				\
typedef MERGE ( MERGE ( mbstring_ , ID )  , _t ) * MERGE ( MERGE ( mbstring_ , ID )  , _p );

// mbstringType(TYPE,ID) :  generic mbstring

#define mbstringType(TYPE)	mbstringTypeDef(TYPE,TYPE)

// ........................................................... [] mbstringAlloc(ID,N) 
 
#define mbstringAlloc(ID,N)                        			\
(ID).data = (void*) gcMalloc ( sizeof((ID).data) * N ); 	\
assert((ID).data!=NULL);									\
(ID).size      = 0;                                    		\
(ID).capacity  = N;    
  
// ........................................................... [] SIZE

#define mbstringSize(ID) ((ID).size)

// ........................................................... [] CAPACITY

#define mbstringCapacity(ID) ((ID).capacity)

// ........................................................... [] EMPTY

#define mbstringEmpty(ID) ((ID).size == 0) 
/*
// ........................................................... [] PUSH_BACK

#define mbstringPushBack(ID, VAL) do {                                   		\
    if ((ID).size + 1 > (ID).capacity) {                                	\
        size_t N = ((ID).capacity += (ID).capacity);                     	\
        (ID).data = gcRealloc  ( (ID).data   , (N) * sizeof((ID).data)  );	\
        (ID).capacity = (N);                                             	\
    } ;                                                                 	\
    (ID).data[mbstringSize(ID)] = (VAL);                                    	\
    ++(ID).size ;                                                       	\
} while (0)

// ........................................................... [] POP_BACK

#define mbstringPopBack(ID) do {  \
    if ((ID).size) --(ID).size; \
} while (0)

// ........................................................... [] CLEAR

#define mbstringClear(ID) do {    \
    (ID).size = 0;              \
} while (0)

// ........................................................... [] DATA

#define mbstringData(ID) (ID).data

// ........................................................... [] AT 

#define mbstringAt(ID, INDEX) (ID).data[INDEX]    

// ........................................................... [] mbstringOfmbstring ... X , XY , XYZ
    
#define mbstringX(ID,NDX1)                mbstringAt(ID,NDX1)
#define mbstringXY(ID,NDX1,NDX2)          mbstringAt(mbstringAt(ID,NDX1),NDX2)
#define mbstringXYZ(ID,NDX1,NDX2,NDX3)    mbstringAt(mbstringAt(mbstringAt(ID,NDX1),NDX2),NDX3)

// ........................................................... [] FRONT

#define mbstringFront(ID) (ID).data[0]

// ........................................................... [] BACK 

#define mbstringBack(ID) (ID).data[mbstringSize(ID) - 1]

// ........................................................... [] ITERATOR 

#define itmbstring(ID)        MERGE ( MERGE ( mbstring_ , ID )  , _d )*  
 
#define mbstringBegin(ID)     (ID).data
#define mbstringEnd(ID)       ((ID).data+(ID).size) 

#define mbstringRBegin(ID)    ((ID).data + (ID).size - 1)
#define mbstringREnd(ID)      ((ID).data - 1 )

// ........................................................... [] SHRINK TO FIT

#define mbstringShrinkToFit(ID) do {                                                  \
    (ID).data = gcRealloc  ( (ID).data   , ((ID).size) * sizeof((ID).data)  );      \
    (ID).capacity = (ID).size;                                                      \
} while (0)    

// ........................................................... [] RESERVE 

#define mbstringReserve(ID, N) do {                                                   \
    if ((ID).capacity < (N)) {                                                      \
        (ID).data = gcRealloc  ( (ID).data   , (N) * sizeof((ID).data)  );          \
        (ID).capacity = (N);                                                        \
    } \
} while (0)

// ........................................................... [] mbstringInsertAtVal     
        
#define mbstringInsertAtVal(ID, POS, VAL) do {                                                \
    while ((ID).size + 1 > (ID).capacity) {                                                 \
        (ID).capacity *= 2;                                                                 \
        (ID).data = gcRealloc  ( (ID).data   , (ID).capacity * sizeof((ID).data)  );        \
    } ;                                                                                     \
    memmove((ID).data + POS + 1, (ID).data + POS, ((ID).size - POS) * sizeof((ID).data) );  \
    ++(ID).size;                                                                            \
    (ID).data[POS] = VAL;                                                                   \
} while (0)

// ........................................................... [] ERASE at
                
#define mbstringEraseAt(ID, POS) do {                                                         \
    if ( (ID).size ) {                                                                      \
    (ID).size -= 1;                                                                         \
    memmove((ID).data + POS, (ID).data + POS + 1, ((ID).size - POS) * sizeof *(ID).data);   \
    } ;                                                                                     \
} while (0)

// ........................................................... [] ERASE N
        
#define mbstringEraseAtN(ID, POS, N) do {                                                         \
    if ( ((ID).size-(N))>0 ) {                                                                  \
    (ID).size -= (N);                                                                           \
    memmove((ID).data + POS, (ID).data + POS + (N), ((ID).size - POS) * sizeof *(ID).data );    \
    }                                                                                           \
} while (0)

// ........................................................... [] RESIZE
    
#define mbstringResize(ID, N, VAL) do {                                       \
    if ((N) > (ID).capacity)                                                \
        (ID).data = gcRealloc ( (ID).data ,  (N) * sizeof((ID).data)   );   \
    if ( (ID).size<(N) )                                                    \
        for (int i = (ID).size; i < (N); ++i) (ID).data[i] = (VAL);         \
    (ID).size = (N);                                                        \
} while (0)

// ........................................................... [] COPY V1 <- V2 
 
#define mbstringCopy(ID, PTR ) do {                                                               \
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
 
#define mbstringAppend(ID, V2 ) do {                                                      \
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

// ........................................................... [] insert mbstring at

#define mbstringInsertAtmbstring(ID, POS, PTR ) do {                                                    \
    while ((ID).size + (PTR).size > (ID).capacity) {                                                \
        (ID).capacity *= 2;                                                                         \
        (ID).data = gcRealloc ( (ID).data , (ID).capacity *  sizeof((ID).data)   );                 \
    }                                                                                               \
    memmove((ID).data + POS + (PTR).size, (ID).data + POS, ((ID).size - POS) * sizeof *(ID).data);  \
    for (size_t i = 0; i < (PTR).size; i++)                                                       	\
        (ID).data[POS + i] = (PTR).data[0 + i];                                                     \
    (ID).size += (PTR).size;                                                                        \
} while (0)

// ........................................................... [] mbstringInsertAtmbstringFromN( v1, POS1, v2 , POS2 , N )

#define mbstringInsertAtmbstringFromN(ID, POS, PTR , POS2 , N) do {                                     \
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

#define mbstringPrintf(FORMAT,ID) do { 												\
for ( size_t i = 0 ; i < (ID).size ; i++)  printf ( FORMAT , (ID).data[i] ) ;		\
}while(0);

// ........................................................... [] FREE 

#define mbstringDealloc(ID) do {                        \
    if ( (ID).data != NULL ) gcFree( (ID).data );     \
} while(0)
   
// ........................................................... [] SORT 

#define mbstringSort(TYPE,ID,CMP)  qsort((ID).data, (ID).size, sizeof(TYPE), CMP )  

// ........................................................... [] BINARY SEARCH 

#define mbstringBinarySearch(TYPE,ID,CMP,KEY)  bsearch (&KEY, (ID).data, (ID).size , sizeof (TYPE), CMP) 

// ........................................................... [] mbstring ALLLOC mbstring 

#define mbstringAllocmbstring(TYPE,ID,N)                  		\
(ID).data = (void*) gcMalloc ( sizeof(TYPE) * N ); 			\
assert((ID).data!=NULL);									\
(ID).size      = 0;                                    		\
(ID).capacity  = N;	
*/

#endif

 
 
/**/

