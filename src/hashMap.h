#ifndef HASHDICTC
#define HASHDICTC

#define _GNU_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1

#include <stdlib.h>  
#include <stdint.h> 
#include <string.h> 
#include <xmmintrin.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "gc.h"

typedef size_t (*enumFunc)(void *key, size_t count, size_t *value, void *user);

#define hashValue_t 	void*
#define hashLength_t 	size_t

struct hashMapNode_s 
{
	struct hashMapNode_s *	next;
	char *					key;
	hashLength_t 			len;
	hashValue_t 			value;
};

struct hashMap_s 
{
	struct hashMapNode_s **	table;
	size_t 					length; 
	size_t						count;
	double 					growth_treshold;
	double 					growth_factor;
	hashValue_t *			value;
};


struct hashMap_s* 	hashMapNew		(size_t initial_size);
void 				hashMapDelete	(struct hashMap_s* hm);
size_t 				hashMapAdd		(struct hashMap_s* hm, void *key, size_t keyn);
size_t 				hashMapFind		(struct hashMap_s* hm, void *key, size_t keyn);
//void dic_forEach(struct hashMap_s* hm, enumFunc f, void *user);

#endif



typedef struct hashMapNode_s ** hashMapIt_t ;


#define hashMapCapacity(HM)		(HM->length)
#define hashMapSize(HM)			(HM->count)	

#define hashMapBegin(HM)		(&HM->table[0])
#define hashMapEnd(HM)			(&HM->table[HM->length])


char* cnvWS2S( wchar_t* ws) ;
char* cnvD2S(double r);
char* cnvL2S(long long r);
char* cnvP2S(void* r);

typedef struct hashMap_s* hashMap_t  ;


// .......................................... hash map get

size_t hashMapSet( hashMap_t hm,char * key , void * value ) ;
 
// .......................................... hash map set

void* hashMapGet( hashMap_t hm,char * key  ) ;
 
/**/




