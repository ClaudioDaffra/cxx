// Cuckoo hashing implementation

#ifndef cuckoo_hash_h
#define cuckoo_hash_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <wchar.h>

typedef struct 
{
    void* key;
    void* value;
} hashRecord_t;

typedef struct 
{
    hashRecord_t* records;
    size_t capacity;
    size_t size;
    int (*CMP)(void*,void*) ;	// compare function
} hashMap_t;

#define hashMap_MAXLOOP 10

typedef void (*hashMapfunc)(void* key, void* value);

// Interface

int 			hashCompareStr	(void* left,void*right) ;
int 			hashCompareWStr (void* left,void*right) ;
void 			hashMapInsert	(hashMap_t* self, hashRecord_t* v);
hashMap_t* 		hashMapNew		(size_t init_size);
void 			hashMapSet		(hashMap_t* self, void* key, void* value);
void* 			hashMapGet		(hashMap_t* self, void* key) ;
void* 			hashMapGetRaw	(hashMap_t* self, void* key) ;
void 			hashMapFree		(hashMap_t* self);
void* 			hashMapDel		(hashMap_t* self, void* key) ;
void* 			hashMapDelInt	(hashMap_t* self, void* key) ;

// macro

#define hmapCapacity(T)	(T->capacity)
#define hmapSize(T)		(T->size)

#define itMap(IT) 		hashRecord_t* IT 
#define itMapBegin(T)	&T->records[0]
#define itMapEnd(T)		&T->records[T->capacity]
#define itMapNext(IT)	IT++
#define itMapKey(IT)	(IT)->key
#define itMapValue(IT)	(IT)->value

typedef hashRecord_t* 	itMap_t ;

#define hashMapGetInt(HMAP,KEY)			hashMapGetRaw(HMAP, (void*)KEY)
#define hashMapSetInt(HMAP,KEY,VALUE)	hashMapSet(HMAP, (void*)KEY ,VALUE)

#endif



/**/


