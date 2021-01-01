#ifndef HASHDICTC
#define HASHDICTC

#define _GNU_SOURCE

#include <stdlib.h>  
#include <stdint.h> 
#include <string.h> 
#include <xmmintrin.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "gc.h"

//typedef int (*enumFunc)(void *key, int count, int *value, void *user);

#define hashValue_t 	void*
#define hashLength_t 	uint8_t

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
	int 					length; 
	int						count;
	double 					growth_treshold;
	double 					growth_factor;
	hashValue_t *			value;
};


struct hashMap_s* 	hashMapNew		(int initial_size);
void 				hashMapDelete	(struct hashMap_s* hm);
int 				hashMapAdd		(struct hashMap_s* hm, void *key, int keyn);
int 				hashMapFind		(struct hashMap_s* hm, void *key, int keyn);
//void dic_forEach(struct hashMap_s* hm, enumFunc f, void *user);

char* cnvWS2S( wchar_t* ws) ;
char* cnvD2S(double r);
char* cnvL2S(long long r);
char* cnvP2S(void* r);

typedef struct hashMap_s* hashMap_t  ;

int 	hashMapSet	( hashMap_t hm,char * key , void * value ) ;
void* 	hashMapGet	( hashMap_t hm,char * key  ) ;

typedef struct hashMapNode_s ** hashMapIt_t ;

#define hashMapCapacity(HM)		(HM->length)
#define hashMapSize(HM)			(HM->count)	

#define hashMapBegin(HM)		(&HM->table[0])
#define hashMapEnd(HM)			(&HM->table[HM->length])


#endif



/**/


