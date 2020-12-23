#ifndef CXX
#define CXX

// ................................................ default header

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ................................................ useful macro

#ifndef CONCATENATE
#define CONCATENATE(x,y)   x##y
#endif

#ifndef MERGE
#define MERGE(x,y)    CONCATENATE(x,y)
#endif

// ................................................ typedef

typedef unsigned char 	uchar8t 	;
typedef signed char 	char8t 		;

typedef unsigned char* 	puchar8t	;
typedef signed char* 	pchar8t		;

typedef unsigned char* 	string8t	;

typedef unsigned char 	uint8t 		;
typedef signed char 	int8t 		;
typedef unsigned char* 	puint8t		;
typedef signed char* 	pint8t		;

typedef unsigned int 	uint32t 	;
typedef signed int 		int32t 		;
typedef unsigned int* 	puint32t 	;
typedef signed int* 	pint32t 	;

// ................................................ new
#define new(ID)	malloc(sizeof(ID));

// ................................................ delete
#define delete(ID)	free(ID);

// ................................................ size struct
#define sizeofStruct(ID)	 sizeof(*(ID))

// ................................................ size struct data
#define sizeofStructData(ID)	sizeof(*(ID)->data)

#endif


/**/



