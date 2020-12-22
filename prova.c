#ifndef HASHDICTC
#define HASHDICTC
#include <stdlib.h> /* malloc/calloc */
#include <stdint.h> /* uint32_t */
#include <string.h> /* memcpy/memcmp */
#include <stdio.h> /* malloc/calloc */


typedef int (*enumFunc)(void *key, int count, int *value, void *user);

#define HASHDICT_VALUE_TYPE void*
#define KEY_LENGTH_TYPE int

struct keynode 
{
	struct keynode *next;
	char *key;
	KEY_LENGTH_TYPE len;
	HASHDICT_VALUE_TYPE value;
};

struct dictionary 
{
	struct keynode **table;
	int length, count;
	double growth_treshold;
	double growth_factor;
	HASHDICT_VALUE_TYPE *value;
};

/* See README.md */

struct dictionary* 	dic_new		(int initial_size);
void 				dic_delete	(struct dictionary* dic);
int 				dic_add		(struct dictionary* dic, void *key, int keyn);
int 				dic_find	(struct dictionary* dic, void *key, int keyn);
//void 				dic_forEach	(struct dictionary* dic, enumFunc f, void *user);
#endif

#define hash_func meiyan

static inline uint32_t meiyan(const char *key, int count) 
{
	typedef uint32_t* P;
	uint32_t h = 0x811c9dc5;
	while (count >= 8) {
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

struct keynode *keynode_new(char*k, int l) 
{
	struct keynode *node = (struct keynode *) malloc(sizeof(struct keynode));
	node->len = l;
	node->key = (char*) malloc(l);
	memcpy(node->key, k, l);
	node->next = 0;
	node->value = NULL;
	return node;
}

void keynode_delete(struct keynode *node) 
{
	if ( node->key!=NULL ) free(node->key);
	
	if ( node->value!=NULL ) free(node->value);	
	
	if (node->next) keynode_delete(node->next);
	
	free(node);
}

struct dictionary* dic_new(int initial_size) 
{
	struct dictionary* dic = (struct dictionary *)malloc(sizeof(struct dictionary));
	if (initial_size == 0) initial_size = 1024;
	dic->length = initial_size;
	dic->count = 0;
	dic->table =  calloc(sizeof(struct keynode*), initial_size);
	dic->growth_treshold = 2.0;
	dic->growth_factor = 10;
	return dic;
}

void dic_delete(struct dictionary* dic) 
{
	for (int i = 0; i < dic->length; i++) 
	{
		if (dic->table[i])
		keynode_delete(dic->table[i]);
	}
	free(dic->table);
	dic->table = 0;
	free(dic);
}

void dic_reinsert_when_resizing(struct dictionary* dic, struct keynode *k2) 
{
	int n = hash_func(k2->key, k2->len) % dic->length;
	if (dic->table[n] == 0) 
	{
		dic->table[n] = k2;
		dic->value = &dic->table[n]->value;
		return;
	}
	struct keynode *k = dic->table[n];
	k2->next = k;
	dic->table[n] = k2;
	dic->value = &k2->value;
}

void dic_resize(struct dictionary* dic, int newsize) 
{
	int o = dic->length;
	struct keynode **old = dic->table;
	dic->table = calloc(sizeof(struct keynode*), newsize);
	dic->length = newsize;
	for (int i = 0; i < o; i++) 
	{
		struct keynode *k = old[i];
		while (k) 
		{
			struct keynode *next = k->next;
			k->next = 0;
			dic_reinsert_when_resizing(dic, k);
			k = next;
		}
	}
	free(old);
}

int dic_add(struct dictionary* dic, void *key, int keyn)
{
	int n = hash_func((const char*)key, keyn) % dic->length;
	if (dic->table[n] == 0)
	{
		double f = (double)dic->count / (double)dic->length;
		if (f > dic->growth_treshold)
		{
			dic_resize(dic, dic->length * dic->growth_factor);
			return dic_add(dic, key, keyn);
		}
		dic->table[n] = keynode_new((char*)key, keyn);
		dic->value = &dic->table[n]->value;
		dic->count++;
		return 0;
	}
	struct keynode *k = dic->table[n];
	while (k) 
	{
		if (k->len == keyn && memcmp(k->key, key, keyn) == 0) 
		{
			dic->value = &k->value;
			return 1;
		}
		k = k->next;
	}
	dic->count++;
	struct keynode *k2 = keynode_new((char*)key, keyn);
	k2->next = dic->table[n];
	dic->table[n] = k2;
	dic->value = &k2->value;
	return 0;
}

int dic_find(struct dictionary* dic, void *key, int keyn) 
{
	int n = hash_func((const char*)key, keyn) % dic->length;
	__builtin_prefetch(dic->table[n]);
	struct keynode *k = dic->table[n];
	if (!k) return 0;
	while (k) 
	{
		if (k->len == keyn && !memcmp(k->key, key, keyn)) 
		{
			dic->value = &k->value;
			return 1;
		}
		k = k->next;
	}
	return 0;
}
/*
void dic_forEach(struct dictionary* dic, enumFunc f, void *user) 
{
	for (int i = 0; i < dic->length; i++) 
	{
		if (dic->table[i] != 0) 
		{
			struct keynode *k = dic->table[i];
			while (k) 
			{
				if (!f(k->key, k->len, &k->value, user)) return;
				k = k->next;
			}
		}
	}
}
*/
#undef hash_func

int dicAdd(struct dictionary* dic,void* key)
{
    union {
        char  ptrc[8];
        void* ptr;
    } pkey ;
	pkey.ptr=(void*)key;
	dic_add(dic, pkey.ptrc, 8);
	*dic->value = (void*)key;
}

int dicFind(struct dictionary* dic,void* key)
{
    union {
        char  ptrc[8];
        void* ptr;
    } pkey ;
    pkey.ptr=(void*)key;
    return dic_find(dic, pkey.ptrc, 8);
}

void* gcMalloc( struct dictionary* dic , size_t size )
{
	void* ptr = malloc( size ) ;
	dicAdd(dic,ptr);
	return ptr ;
}
void* gcFree( struct dictionary* dic , void* ptr )
{
	if ( dicFind(dic,ptr) ) 
	{
		if (*dic->value!=NULL)
		{ 
			free(*dic->value);
			
			*dic->value=NULL ;
			
			ptr=NULL;
		}
	}
	return ptr;
}
void* gcRealloc( struct dictionary* dic , void* ptr, size_t size )
{
	void* old = ptr ;

	ptr = realloc( ptr,size ) ;
	dicAdd(dic,ptr); 

	dicFind(dic,old);
	*dic->value=NULL ;	

	return ptr ;
}
int main()
{
	struct dictionary* dic = dic_new(0);
/*
	int x=100;
	int y=200;
	int z=300;

	dicAdd(dic,&x);
	dicAdd(dic,&y);
	dicAdd(dic,&z);

	if (dicFind(dic,&x) ) printf("x found: %p\n", (void*)*dic->value); else printf("error\n");
	if (dicFind(dic,&y) ) printf("y found: %p\n", (void*)*dic->value); else printf("error\n");
	if (dicFind(dic,&z) ) printf("z found: %p\n", (void*)*dic->value); else printf("error\n");
*/	 
	int* a1 = gcMalloc( dic, sizeof(int)*10 ) ;
	long* a2 = gcMalloc( dic, sizeof(long)*10 ) ;
		
	gcFree(dic,a2);
	
	a2 = gcMalloc( dic, sizeof(long)*410 ) ;

	a2 =  gcRealloc( dic,a2,sizeof(long)*500 );
	
	gcFree(dic,a2);

	dic_delete(dic);

	return 0;
}
