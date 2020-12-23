#ifndef pVector
#define pVector


#include "cxx.h"


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

#define pVectorStruct(TYPE,ID)	\
struct ID       					\
{                                   \
    TYPE*   data 		;        	\
    size_t  size        ;           \
    size_t  capacity    ;         	\
}


// ........................................................... [] ALLOC TODO initialize memoey allocate

#define pVectorAlloc(ID,N)                               	\
do{ 														\
(ID).data = (void*) malloc (sizeof((ID).data) * N);     	\
(ID).size      = 0;                                   		\
(ID).capacity  = N;											\
}while(0);

// ........................................................... [] DEALLOC 
// TODO pointer=NULL lo fa la garbage size capacity 0 pointer NULL

#define pVectorDealloc(ID)                               	\
do{ 														\
if ( (ID).data!=NULL) free((ID).data); 						\
}while(0);


// ........................................................... [] NEW

#define pVectorNew(ID,N)                         			\
do{ 														\
(ID) = malloc ( sizeof( (ID) )  ) ; 						\
pVectorAlloc(ID,N) 	;										\
}while(0);

// ........................................................... [] Destroy

#define pVectorDestroy(ID)     								\
do{ 														\
pVectorDeAlloc(ID); 										\
if ( (ID)!=NULL) free((ID)); 								\
}while(0);


// ........................................................... [] SIZE

#define pVectorSize(ID) ((ID).size)

// ........................................................... [] CAPACITY

#define pVectorCapacity(ID) ((ID).capacity)

// ........................................................... [] IS EMPTY

#define pVectorIsEmpty(ID) ((ID).size == 0)

// ........................................................... [] CLEAR

#define pVectorClear(ID) ((ID).size = 0)  

// ........................................................... [] PUSH_BACK  TODO IF NULL NOT


#define pVectorPushBack(ID, VAL)											\
do {                            											\
    if ((ID).size + 1 > (ID).capacity) {                               		\
        size_t N = ((ID).capacity += (ID).capacity);                     	\
        (ID).data = realloc  ( (ID).data   , (N) * sizeof((ID).data)  ); 	\
        (ID).capacity = (N);                                          		\
    } ;                                                                 	\
    (ID).data[pVectorSize(ID)] = (VAL);                                 	\
    ++(ID).size ;                                                       	\
} while (0) ;

// ........................................................... [] POP_BACK [check < 0  );

#define vectorPopBack(ID) do {  \
    if ((ID).size) --(ID).size; \
} while (0)

// ........................................................... [] AT check size

#define pVectorAt(ID, INDEX) ((ID).data[INDEX])

/*
// ........................................................... [] vectorOfVector ... X , XY , XYZ
   
#define pVectorX(ID,NDX1)                pVectorAt(ID,NDX1)
#define pVectorXY(ID,NDX1,NDX2)          pVectorAt(pVectorAt(ID,NDX1),NDX2)
#define pVectorXYZ(ID,NDX1,NDX2,NDX3)    pVectorAt(pVectorAt(pVectorAt(ID,NDX1),NDX2),NDX3)



*/


#endif



/**/


