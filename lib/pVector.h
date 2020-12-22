#ifndef pVector
#define pVector



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tgc.h"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif


#ifndef CONCATENATE
#define CONCATENATE(x,y)   x##y
#endif

#ifndef MERGE
#define MERGE(x,y)    CONCATENATE(x,y)
#endif

#endif

// ........................................................... [] pVector(TYPE)

/*
	pVectorStructDef( int , vint_s ) ;
	pVectorTypeDef( vint_s  ) vint_t ;
	pVectorTypeDef( vint_s* ) pvint_t ;
	vint_t v1 ;
	pVectorAlloc(v1,16);
	pvint_t  pv1 = NULL ;
	pVectorNew(pv1,vint_t,128);
*/

#define pVectorStructDef(TYPE,ID)	\
struct ID       					\
{                                   \
    TYPE*   data 		;        	\
    size_t  size        ;           \
    size_t  capacity    ;         	\
}

#define pVectorTypeDef(ID) 			\
typedef struct ID    

// ........................................................... [] ALLOC

#define pVectorAlloc(ID,N)                               	\
do{ 														\
(ID).data = (void*) malloc (sizeof((ID).data) * N);     	\
(ID).size      = 0;                                   		\
(ID).capacity  = N;											\
}while(0);

// ........................................................... [] DEALLOC

#define pVectorDeAlloc(ID)                               	\
do{ 														\
if ( (ID).data!=NULL) tgc_free(&gc,(ID).data); 						\
}while(0);

// ........................................................... [] NEW

#define pVectorNew(ID,TYPE,N)                         		\
do{ 														\
(ID) = tgc_alloc ( &gc,sizeof( TYPE )  ) ; 						\
pVectorAlloc(*ID,N) 										\
}while(0);

// ........................................................... [] Destroy

#define pVectorDestroy(ID)     								\
do{ 														\
pVectorDeAlloc(*ID); 										\
if ( (ID)!=NULL) tgc_free(&gc,(ID)); 								\
}while(0);

// ........................................................... [] SIZE

#define pVectorSize(ID) ((ID).size)

// ........................................................... [] CAPACITY

#define pVectorCapacity(ID) ((ID).capacity)

// ........................................................... [] IS EMPTY

#define pVectorIsEmpty(ID) ((ID).size == 0)

// ........................................................... [] CLEAR

#define pVectorClear(ID) ((ID).size = 0)  

// ........................................................... [] PUSH_BACK


#define pVectorPushBack(ID, VAL)											\
do {                            											\
    if ((ID).size + 1 > (ID).capacity) {                               		\
        size_t N = ((ID).capacity += (ID).capacity);                     	\
        (ID).data = tgc_realloc  ( &gc,(ID).data   , (N) * sizeof((ID).data)  ); 	\
        (ID).capacity = (N);                                          		\
    } ;                                                                 	\
    (ID).data[pVectorSize(ID)] = (VAL);                                 	\
    ++(ID).size ;                                                       	\
} while (0) ;


// ........................................................... [] AT

#define pVectorAt(ID, INDEX) ((ID).data[INDEX])

// ........................................................... [] vectorOfVector ... X , XY , XYZ
   
#define pVectorX(ID,NDX1)                pVectorAt(ID,NDX1)
#define pVectorXY(ID,NDX1,NDX2)          pVectorAt(pVectorAt(ID,NDX1),NDX2)
#define pVectorXYZ(ID,NDX1,NDX2,NDX3)    pVectorAt(pVectorAt(pVectorAt(ID,NDX1),NDX2),NDX3)
