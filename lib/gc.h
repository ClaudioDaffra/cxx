
#ifndef gcGarbageCollector
#define gcGarbageCollector

#define _GNU_SOURCE
#include <stdlib.h> 
#include <stdint.h> 
#include <string.h> 
#include <stdio.h> 
#include <xmmintrin.h>

//#define HASHDICT_VALUE_TYPE void*

typedef void(*HASHDICT_VALUE_TYPE)(void*);

#define KEY_LENGTH_TYPE 	int

struct gcKeyNode_s 
{
	struct gcKeyNode_s *	next;
	char *					key;
	KEY_LENGTH_TYPE 		len;
	HASHDICT_VALUE_TYPE 	dtor;
};

struct gc_s 
{
	struct gcKeyNode_s **	table;
	int 					length, count;
	double 					growth_treshold;
	double 					growth_factor;
	HASHDICT_VALUE_TYPE *	dtor;
};

void 			cb_fclose	(void*ptr) ;
struct gc_s* 	gc_new		(int initial_size);
void			gc_del		(struct gc_s* gc);
int 			gcAdd		(struct gc_s* gc,void* key,HASHDICT_VALUE_TYPE dtor);
int 			gc_find		(struct gc_s* gc, void *key, int keyn) ;
void* 			gcMalloc_	(struct gc_s* gc , size_t size ) ;
void* 			gcFree_		(struct gc_s* gc , void* ptr ) ;
void* 			gcRealloc_	(struct gc_s* gc , void* ptr, size_t size ) ;
void 			gcPrint_	(struct gc_s* gc );
void*           gcFileOpen_ ( struct gc_s* gc ,char* fileName, char* action);
FILE*           gcFileTemp  ( void ) ;

#define 		gcStart(...)	gc=gc_new(0)/*__VA_ARGS__*/
#define 		gcStop(...)		gc_del(gc)/*__VA_ARGS__*/

#define 		gcRealloc(ptr,size)	gcRealloc_(gc,ptr,size)
#define 		gcFree(ptr)			gcFree_(gc,ptr)
#define 		gcMalloc(size)		gcMalloc_(gc,size)
#define 		gcPrint(...)		gcPrint_(gc)/*__VA_ARGS__*/
#define 		gcFileOpen(pf,mode)		gcFileOpen_(gc,pf,mode)
#define 		gcFileClose(ptr)		gcFree_(gc,ptr)

extern struct gc_s* gc ;

#endif



/**/


