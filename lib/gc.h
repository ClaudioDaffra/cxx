
#ifndef gcGarbageCollector
#define gcGarbageCollector

#include <stdlib.h> 
#include <stdint.h> 
#include <string.h> 
#include <stdio.h> 

//typedef int (*enumFunc)(void *key, int count, int *value, void *user);

#define HASHDICT_VALUE_TYPE void*
#define KEY_LENGTH_TYPE 	int

struct gcKeyNode_s 
{
	struct gcKeyNode_s *	next;
	char *					key;
	KEY_LENGTH_TYPE 		len;
	HASHDICT_VALUE_TYPE 	value;
};

struct gc_s 
{
	struct gcKeyNode_s **	table;
	int 					length, count;
	double 					growth_treshold;
	double 					growth_factor;
	HASHDICT_VALUE_TYPE *	value;
};

struct gc_s* 	gc_new		(int initial_size);
void			gc_del		(struct gc_s* gc);
static 
int				gc_add		(struct gc_s* gc , void *key, int keyn );
static 
int				gc_find		(struct gc_s* gc , void *key, int keyn );
void* 			gcMalloc_	(struct gc_s* gc , size_t size ) ;
void* 			gcFree_		(struct gc_s* gc , void* ptr ) ;
void* 			gcRealloc_	(struct gc_s* gc , void* ptr, size_t size ) ;
void 			gcPrint_	(struct gc_s* gc );

#define 		gcStart(...)	gc=gc_new(0)/*__VA_ARGS__*/
#define 		gcStop(...)		gc_del(gc)/*__VA_ARGS__*/

#define 		gcRealloc(ptr,size)	gcRealloc_(gc,ptr,size)
#define 		gcFree(ptr)			gcFree_(gc,ptr)
#define 		gcMalloc(size)		gcMalloc_(gc,size)
#define 		gcPrint(...)		gcPrint_(gc)/*__VA_ARGS__*/


extern struct gc_s* gc ;

#endif



/**/


