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
#include "src/gc.h"

typedef int (*enumFunc)(void *key, int count, int *value, void *user);

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

#endif

#define hash_func meiyan

static inline uint32_t meiyan(const char *key, int count) 
{
	typedef uint32_t* P;
	uint32_t h = 0x811c9dc5;
	while (count >= 8) 
	{
		h = (h ^ ((((*(P)key) << 5) | ((*(P)key) >> 27)) ^ *(P)(key + 4))) * 0xad3e7;
		count -= 8;
		key += 8;
	}
	#define tmp h = (h ^ *(uint16_t*)key) * 0xad3e7; key += 2;
	if (count & 4) { tmp tmp }
	if (count & 2) { tmp }
	if (count & 1) { h = (h ^ *key) * 0xad3e7; }
	#undef tmp
	
	return h ^ (h >> 16);
}

struct hashMapNode_s *hashMapKeyNodeNew(char*k, int l) 
{
	struct hashMapNode_s *node = gcMalloc(sizeof(struct hashMapNode_s));
	node->len = l;
	node->key = gcMalloc(l);
	memcpy(node->key, k, l);
	node->next 	= 0;
	node->value = NULL;
	
	return node;
}

void hashMapKeyNodeDelete(struct hashMapNode_s *node) 
{
	gcFree(node->key);
	if (node->next) hashMapKeyNodeDelete(node->next);
	gcFree(node);
}

struct hashMap_s* hashMapNew(int initial_size) 
{
	struct hashMap_s* hm = gcMalloc(sizeof(struct hashMap_s));
	if (initial_size == 0) initial_size = 1024;
	hm->length = initial_size;
	hm->count = 0;
	hm->table = gcCalloc(sizeof(struct hashMapNode_s*), initial_size);
	hm->growth_treshold = 2.0;
	hm->growth_factor = 10;
	return hm;
}

void hashMapDelete(struct hashMap_s* hm) 
{
	for (int i = 0; i < hm->length; i++) 
	{
		if (hm->table[i])
		hashMapKeyNodeDelete(hm->table[i]);
	}
	gcFree(hm->table);
	hm->table = 0;
	gcFree(hm);
}

void hashMapReinsertWhenResizing(struct hashMap_s* hm, struct hashMapNode_s *k2) 
{
	int n = hash_func(k2->key, k2->len) % hm->length;
	if (hm->table[n] == 0) 
	{
		hm->table[n] = k2;
		hm->value = &hm->table[n]->value;
		return;
	}
	struct hashMapNode_s *k = hm->table[n];
	k2->next = k;
	hm->table[n] = k2;
	hm->value = &k2->value;
}

void hashMapResize(struct hashMap_s* hm, int newsize) 
{
	int o = hm->length;
	struct hashMapNode_s **old = hm->table;
	hm->table = gcCalloc(sizeof(struct hashMapNode_s*), newsize);
	hm->length = newsize;
	for (int i = 0; i < o; i++) 
	{
		struct hashMapNode_s *k = old[i];
		while (k) 
		{
			struct hashMapNode_s *next = k->next;
			k->next = 0;
			hashMapReinsertWhenResizing(hm, k);
			k = next;
		}
	}
	gcFree(old);
}

int hashMapAdd(struct hashMap_s* hm, void *key, int keyn) 
{
	int n = hash_func((const char*)key, keyn) % hm->length;
	if (hm->table[n] == 0) 
	{
		double f = (double)hm->count / (double)hm->length;
		if (f > hm->growth_treshold) 
		{
			hashMapResize(hm, hm->length * hm->growth_factor);
			return hashMapAdd(hm, key, keyn);
		}
		hm->table[n] = hashMapKeyNodeNew((char*)key, keyn);
		hm->value = &hm->table[n]->value;
		hm->count++;
		return 0;
	}
	struct hashMapNode_s *k = hm->table[n];
	while (k) 
	{
		if (k->len == keyn && memcmp(k->key, key, keyn) == 0) 
		{
			hm->value = &k->value;
			return 1;
		}
		k = k->next;
	}
	hm->count++;
	struct hashMapNode_s *k2 = hashMapKeyNodeNew((char*)key, keyn);
	k2->next = hm->table[n];
	hm->table[n] = k2;
	hm->value = &k2->value;
	return 0;
}

int hashMapFind(struct hashMap_s* hm, void *key, int keyn) 
{
	int n = hash_func((const char*)key, keyn) % hm->length;
	#if defined(__MINGW32__) || defined(__MINGW64__)
	__builtin_prefetch(gc->table[n]);
	#endif

	#if defined(_WIN32) || defined(_WIN64)
	_mm_prefetch((char*)gc->table[n], _MM_HINT_T0);
	#endif
	struct hashMapNode_s *k = hm->table[n];
	if (!k) return 0;
	while (k) 
	{
		if (k->len == keyn && !memcmp(k->key, key, keyn)) 
		{
			hm->value = &k->value;
			return 1;
		}
		k = k->next;
	}
	return 0;
}
/*
void dic_forEach(struct hashMap_s* hm, enumFunc f, void *user) 
{
	for (int i = 0; i < hm->length; i++) 
	{
		if (hm->table[i] != 0) 
		{
			struct hashMapNode_s *k = hm->table[i];
			while (k) {
			if (!f(k->key, k->len, &k->value, user)) return;
			k = k->next;
			}
		}
	}
}
*/
#undef hash_func

char* cnvWS2S( wchar_t* ws) ;
char* cnvD2S(double r);
char* cnvL2S(long long r);
char* cnvP2S(void* r);

// ........................................................... convert

char* cnvWS2S( wchar_t* ws )
{
  size_t len = sizeof(wchar_t) * wcslen(ws) ;
  char* buffer = gcCalloc ( sizeof(wchar_t),len );
  int ret = wcstombs ( buffer, ws, len ) ;

  buffer=gcRealloc(buffer,strlen(buffer)+1);

  return buffer ;
}

char* cnvD2S(double r)
{
    const unsigned char maxBufferLen=32;
    char* buffer=gcCalloc(sizeof(char),maxBufferLen);
    gcvt(r,8,buffer);

    return buffer ;
}

char* cnvL2S(long long r)
{
    const unsigned char maxBufferLen=32;
    char* buffer=gcCalloc(sizeof(char),maxBufferLen);
    snprintf(buffer, maxBufferLen, "%lld", r);

    return buffer ;
}

char* cnvP2S(void* r)
{
    const unsigned char maxBufferLen=32;
    char* buffer=gcCalloc(sizeof(char),maxBufferLen);
    snprintf(buffer, maxBufferLen, "%p", r);
   
    return buffer ;
}  

// .......................................... hashMap.h

typedef struct hashMap_s* hashMap_t  ;

// .......................................... hash map get

int hashMapSet( hashMap_t hm,char * key , void * value )
{
	int res=hashMapAdd(hm, key, strlen(key) );
	*hm->value = value;
	return res;
}

// .......................................... hash map set

void* hashMapGet( hashMap_t hm,char * key  )
{
	hashMapFind(hm, key, strlen(key) ) ;
	return hm->value  ;
}

typedef struct hashMapNode_s ** hashMapIt_t ;

#define hashMapCapacity(HM)		(HM->length)
#define hashMapSize(HM)			(HM->count)	

#define hashMapBegin(HM)		(&HM->table[0])
#define hashMapEnd(HM)			(&HM->table[HM->length])

// ..........................................
    
int main()
{
	gcStart();
	
	setlocale(LC_ALL, "") ;

	char*source="claudio";

	// ...................................................... new
	
	hashMap_t hm = hashMapNew(0);

	// ...................................................... set
	
	hashMapSet(hm,cnvWS2S(L"你好吗") 							, (void*) 100 );
	hashMapSet(hm,cnvWS2S(L"§°çéè") 							, (void*) 200 );
	hashMapSet(hm,cnvWS2S(L"°*§ç") 								, (void*) 300 );
	hashMapSet(hm,source 										, (void*) 400 );	
	hashMapSet(hm,cnvD2S (235325325325325353.14159265358L) 		, (void*) 500 );
	hashMapSet(hm,cnvL2S (235325325325325353L) 					, (void*) 600 );
	hashMapSet(hm,cnvP2S (&source) 								, (void*) gcStrDup("daffra") 	);		

	// ...................................................... get
	
	if (hashMapGet(hm, cnvWS2S(L"你好吗")) )
			printf("found: %zu\n", (size_t)*hm->value);
	else 
			printf("error\n");
			
	if (hashMapGet(hm, cnvP2S (&source)) )
			printf("found: %s\n", (char*)*hm->value);
	else 
			printf("error\n");	

	// ...................................................... iterator
	
	printf ("table size %d capacity %d :\n",hashMapSize(hm),hashMapCapacity(hm) ) ;

    for ( hashMapIt_t it=hashMapBegin(hm) ; it < hashMapEnd(hm); ++it )
    {
		if (*it!=NULL) 
		{
			if ((*it)->key!=NULL)
				if ((*it)->value!=NULL)
				
				printf ( "key(%-20s) \nvalue(%p) %zu \n\n", (*it)->key,(*it)->value , (size_t)(*it)->value ) ;
		
		}
	}
		
	hashMapDelete(hm);

	gcStop();
	
return 0;
}

