
#ifndef CXX
#define CXX

// ................................................ default header

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// ................................................ merge

#ifndef CONCATENATE
#define CONCATENATE(x,y)   x##y
#endif

#ifndef MERGE
#define MERGE(x,y)    CONCATENATE(x,y)
#endif

// ................................................ debug

// warning: ISO C does not support ‘__FUNCTION__’ predefined identifier [-Wpedantic]
#define debugInfo fprintf ( stderr,"## file[%s] line[%d] fn[%s].\n",__FILE__,__LINE__,__func__);

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

#define new(ID)		malloc(sizeof(ID));

// ................................................ delete

#define delete(ID)	free(ID);


#endif



/**/


