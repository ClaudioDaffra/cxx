#ifndef pVector
#define pVector


#include "cxx.h"


// ........................................................... [] pVector(TYPE)

/*
	----------------------------------------------------- stack

		pVectorStruct( signed char , vectorInt_s ) v1;

		printf ( "vector size struct %zu.\n",sizeof(v1)			) ; 
		printf ( "vector size data   %zu.\n",sizeof(*v1.data)	) ; 

		pVectorAlloc(v1,8);
		...
		pVectorDealloc(v1);

	----------------------------------------------------- heap

		pVectorStruct( int8t  , pvectorInt_s ) *pv1 = new(struct pvectorInt_s ) ;

		printf ( "vector size struct %zu.\n",sizeof(*pv1)) ; 
		printf ( "vector size data   %zu.\n",sizeof(*pv1->data)) ; 	

		pVectorAlloc(*pv1,8);
		...
		pVectorDealloc(*pv1);
			
		delete(pv1); 

*/

#define pVectorStruct(TYPE,ID)		\
struct ID       					\
{                                   \
    TYPE*   data 		;        	\
    size_t  size        ;           \
    size_t  capacity    ;         	\
}

// ........................................................... [] ALLOC TODO initialize memoey allocate CPPCHECK

#define pVectorAlloc(ID,N)                               	\
do{ 														\
	(ID).data = (void*) malloc (sizeof((ID).data) * N);     \
	assert((ID).data!=NULL);								\
	(ID).size      = 0;                                   	\
	(ID).capacity  = N;										\
}while(0);

// ........................................................... [] DEALLOC 

#define pVectorDealloc(ID)                               	\
do{ 														\
if ((ID).data!=NULL)										\
{															\
	(ID).size=0;											\
	(ID).capacity=0;										\
	free((ID).data);										\
	(ID).data=NULL; 										\
}															\
}while(0);

// ........................................................... [] vector NEW

#define pVectorNew(TYPE,ID,N)                         			\
do{ 															\
	(ID)=malloc(sizeof(TYPE));									\
	assert(ID!=NULL);											\
	(ID)->size=0;												\
	(ID)->data = (void*) malloc (sizeof(TYPE) * N);				\
	assert((ID)->data!=NULL);									\
	(ID)->capacity=N;											\
}while(0);

// ........................................................... [] vector DESTROY

#define pVectorDestroy(ID)     												\
do{ 																		\
	if ( (ID)->data	!=NULL) { free((ID)->data	); ((ID)->data	)=NULL; } ;	\
	if ( (ID)		!=NULL) { free((ID)			); ((ID)		)=NULL; } ;	\
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
        (ID).data = realloc  ( (ID).data   , (N) * sizeof((ID).data)  ); 	\
        assert((ID).data!=NULL);											\
        (ID).capacity = (N);                                          		\
    } ;                                                                 	\
    (ID).data[pVectorSize(ID)] = (VAL);                                 	\
    ++(ID).size ;                                                       	\
} while (0) ;

// ........................................................... [] POP_BACK

#define vectorPopBack(ID) do {  \
    if ((ID).size) --(ID).size; \
} while (0)

// ........................................................... [] AT TODO check size range

#define pVectorAt(ID, INDEX) ((ID).data[INDEX])

/*
// ........................................................... [] vectorOfVector ... X , XY , XYZ
   
#define pVectorX(ID,NDX1)                pVectorAt(ID,NDX1)
#define pVectorXY(ID,NDX1,NDX2)          pVectorAt(pVectorAt(ID,NDX1),NDX2)
#define pVectorXYZ(ID,NDX1,NDX2,NDX3)    pVectorAt(pVectorAt(pVectorAt(ID,NDX1),NDX2),NDX3)



*/


#endif



/**/


