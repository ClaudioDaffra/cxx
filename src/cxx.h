
#ifndef CXX
#define CXX

// ................................................ default header

#define _GNU_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <wchar.h>
#include <stdlib.h>  
#include <stdint.h> 
#include <string.h> 
#include <xmmintrin.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>

// ................................................ merge

#ifndef CONCATENATE
#define CONCATENATE(x,y)   x##y
#endif

#ifndef MERGE
#define MERGE(x,y)    CONCATENATE(x,y)
#endif

// ................................................ debug

// warning: ISO C does not support ‘__FUNCTION__’ '__PRETTY_FUNCTION__' predefined identifier [-Wpedantic]
#define debugInfo fprintf ( stderr,"## file[%s] line[%d] fn[%s].\n",__FILE__,__LINE__,__func__);


// ................................................ new

#define new(ID)		malloc(sizeof(ID));

// ................................................ delete

#define delete(ID)	if((ID)!=NULL){free(ID);(ID)=NULL;}


#endif



/**/


