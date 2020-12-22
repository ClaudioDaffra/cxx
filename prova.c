
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

/* See README.md */

struct gc_s* 	gc_new		(int initial_size);
void 			gc_del		(struct gc_s* gc);
int 			gc_add		(struct gc_s* gc, void *key, int keyn);
int 			gc_find	(struct gc_s* gc, void *key, int keyn);
//void 			dic_forEach	(struct gc_s* gc, enumFunc f, void *user);
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

struct gcKeyNode_s *gc_node_new(char*k, int l) 
{
	struct gcKeyNode_s *node = (struct gcKeyNode_s *) malloc(sizeof(struct gcKeyNode_s));
	node->len = l;
	node->key = (char*) malloc(l);
	memcpy(node->key, k, l);
	node->next = 0;
	node->value = NULL;
	return node;
}

// ........................................... gc delete node

void gc_node_del(struct gcKeyNode_s *node) 
{
	if ( node->key!=NULL ) free(node->key);
	
	if ( node->value!=NULL ) free(node->value);	
	
	if (node->next) gc_node_del(node->next);
	
	free(node);
}

// ........................................... gc new

struct gc_s* gc_new(int initial_size) 
{
	struct gc_s* gc = (struct gc_s *)malloc(sizeof(struct gc_s));
	if (initial_size == 0) initial_size = 1024;
	gc->length = initial_size;
	gc->count = 0;
	gc->table =  calloc(sizeof(struct gcKeyNode_s*), initial_size);
	gc->growth_treshold = 2.0;
	gc->growth_factor = 10;
	return gc;
}

// ........................................... gc delete

void gc_del(struct gc_s* gc) 
{
	for (int i = 0; i < gc->length; i++) 
	{
		if (gc->table[i])
		gc_node_del(gc->table[i]);
	}
	free(gc->table);
	gc->table = 0;
	free(gc);
}

// ........................................... gc reinsert when resizing

void gc_reinsert_when_resizing(struct gc_s* gc, struct gcKeyNode_s *k2) 
{
	int n = hash_func(k2->key, k2->len) % gc->length;
	if (gc->table[n] == 0) 
	{
		gc->table[n] = k2;
		gc->value = &gc->table[n]->value;
		return;
	}
	struct gcKeyNode_s *k = gc->table[n];
	k2->next = k;
	gc->table[n] = k2;
	gc->value = &k2->value;
}

// ........................................... gc  resize

void gc_resize(struct gc_s* gc, int newsize) 
{
	int o = gc->length;
	struct gcKeyNode_s **old = gc->table;
	gc->table = calloc(sizeof(struct gcKeyNode_s*), newsize);
	gc->length = newsize;
	for (int i = 0; i < o; i++) 
	{
		struct gcKeyNode_s *k = old[i];
		while (k) 
		{
			struct gcKeyNode_s *next = k->next;
			k->next = 0;
			gc_reinsert_when_resizing(gc, k);
			k = next;
		}
	}
	free(old);
}

// ........................................... gc add

int gc_add(struct gc_s* gc, void *key, int keyn)
{
	int n = hash_func((const char*)key, keyn) % gc->length;
	if (gc->table[n] == 0)
	{
		double f = (double)gc->count / (double)gc->length;
		if (f > gc->growth_treshold)
		{
			gc_resize(gc, gc->length * gc->growth_factor);
			return gc_add(gc, key, keyn);
		}
		gc->table[n] = gc_node_new((char*)key, keyn);
		gc->value = &gc->table[n]->value;
		gc->count++;
		return 0;
	}
	struct gcKeyNode_s *k = gc->table[n];
	while (k) 
	{
		if (k->len == keyn && memcmp(k->key, key, keyn) == 0) 
		{
			gc->value = &k->value;
			return 1;
		}
		k = k->next;
	}
	gc->count++;
	struct gcKeyNode_s *k2 = gc_node_new((char*)key, keyn);
	k2->next = gc->table[n];
	gc->table[n] = k2;
	gc->value = &k2->value;
	return 0;
}

// ........................................... gc find

int gc_find(struct gc_s* gc, void *key, int keyn) 
{
	int n = hash_func((const char*)key, keyn) % gc->length;
	__builtin_prefetch(gc->table[n]);
	struct gcKeyNode_s *k = gc->table[n];
	if (!k) return 0;
	while (k) 
	{
		if (k->len == keyn && !memcmp(k->key, key, keyn)) 
		{
			gc->value = &k->value;
			return 1;
		}
		k = k->next;
	}
	return 0;
}
/*
void dic_forEach(struct gc_s* gc, enumFunc f, void *user) 
{
	for (int i = 0; i < gc->length; i++) 
	{
		if (gc->table[i] != 0) 
		{
			struct gcKeyNode_s *k = gc->table[i];
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

// ........................................... gc add

int gcAdd(struct gc_s* gc,void* key)
{
    union {
        char  ptrc[8];
        void* ptr;
    } pkey ;
	pkey.ptr=(void*)key;
	gc_add(gc, pkey.ptrc, 8);
	*gc->value = (void*)key;
}

// ........................................... gc find

int gcFind(struct gc_s* gc,void* key)
{
    union {
        char  ptrc[8];
        void* ptr;
    } pkey ;
    pkey.ptr=(void*)key;
    return gc_find(gc, pkey.ptrc, 8);
}

// ........................................... gc malloc

void* gcMalloc( struct gc_s* gc , size_t size )
{
	void* ptr = malloc( size ) ;
	gcAdd(gc,ptr);
	return ptr ;
}

// ........................................... gc free

void* gcFree( struct gc_s* gc , void* ptr )
{
	if ( gcFind(gc,ptr) ) 
	{
		if (*gc->value!=NULL)
		{ 
			free(*gc->value);
			
			*gc->value=NULL ;
			
			ptr=NULL;
		}
	}
	return ptr;
}

// ........................................... gc realloc

void* gcRealloc( struct gc_s* gc , void* ptr, size_t size )
{
	void* old = ptr ;

	ptr = realloc( ptr,size ) ;
	gcAdd(gc,ptr); 

	gcFind(gc,old);
	*gc->value=NULL ;	

	return ptr ;
}

// ........................................... MAIN

int main()
{
	struct gc_s* gc = gc_new(0);

	int* a1 = gcMalloc( gc, sizeof(int)*10 ) ;
	long* a2 = gcMalloc( gc, sizeof(long)*10 ) ;
		
	gcFree(gc,a2);
	
	a2 = gcMalloc( gc, sizeof(long)*410 ) ;

	a2 =  gcRealloc( gc,a2,sizeof(long)*500 );
	
	gcFree(gc,a2);

	gc_del(gc);

	return 0;
}
