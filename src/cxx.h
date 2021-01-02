
#ifndef CXX
#define CXX

// ................................................ default header

#define _GNU_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include <xmmintrin.h>
#include <locale.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>

// ................................................ gcc

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

// ................................................ merge

#ifndef CONCATENATE
#define CONCATENATE(x,y)   x##y
#endif

#ifndef MERGE
#define MERGE(x,y)    CONCATENATE(x,y)
#endif

// ................................................ debug

// warning: ISO C does not support ‘__FUNCTION__’ '__PRETTY_FUNCTION__' predefined identifier [-Wpedantic]
#define debugInfo(...) fprintf ( stderr,"## file[%s] line[%d] fn[%s].\n",__FILE__,__LINE__,__func__);/*__VA_ARGS__*/

// ................................................ new

#define new(ID)		gcMalloc(sizeof(ID));

// ................................................ delete

#define delete(ID)	if((ID)!=NULL){gcFree(ID);(ID)=NULL;}


#endif



/**/


