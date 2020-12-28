
#include "hashMap.h"

static
void hashMapSize(hashMap_t* self, size_t capacity) 
{
	self->records=gcMalloc(sizeof(hashRecord_t)*capacity);

    if(capacity > self->capacity) 
    {
	    self->records = gcRealloc(self->records, sizeof(hashRecord_t) * capacity);	
        size_t diff = (capacity - self->capacity) * sizeof(hashRecord_t);
        memset(&self->records[self->capacity], 0, diff);
    }

    self->capacity = capacity;
}
static
void hashMapGrow(hashMap_t* self) 
{
    hashMapSize(self, self->capacity * 2);
}

hashMap_t* hashMapNew(size_t init_size) 
{
    hashMap_t* self = gcCalloc(sizeof(hashMap_t), 1);
    
    
    
    self->CMP = hashCompareStr ; // default compare function
    hashMapSize(self, init_size);
    return self;
}
static
hashRecord_t* hashMapRecord1(hashMap_t* self, void* k) 
{
    intptr_t kk = (intptr_t)k;
    size_t pos = kk % self->capacity;
    return &self->records[pos];
}
static
hashRecord_t* hashMapRecord2(hashMap_t* self, void* k) 
{
    intptr_t kk = (intptr_t)k;
    size_t pos = (kk / self->capacity) % self->capacity;
    return &self->records[pos];
}
static
void hashMapRecordSwap(hashRecord_t* r1, hashRecord_t* r2) 
{
    hashRecord_t tmp = *r1;
    *r1 = *r2;
    *r2 = tmp;
}

// Helper function
static
void hashMapPutReHash(hashMap_t* self, hashRecord_t* v) 
{
    hashRecord_t* r = hashMapRecord1(self, v->key);
    if(!r->key) 
    {
        hashMapRecordSwap(r, v);
        self->size++;
        return;
    }

    if(r->key == v->key) 
    {
        // Replace
        r->value = v->value;
        return;
    }

    r = hashMapRecord2(self, v->key);
    if(!r->key) 
    {
        hashMapRecordSwap(r, v);
        self->size++;
        return;
    }

    if(r->key == v->key) 
    {
        r->value = v->value;
        return;
    }

    hashMapInsert(self, v);
}

void hashMapSet(hashMap_t* self, void* key, void* value) 
{
    hashRecord_t rec;
    rec.key = key;
    rec.value = value;
    hashMapInsert(self, &rec);
}

void hashMapInsert(hashMap_t* self, hashRecord_t* v) 
{
    for(int n = 0; n < hashMap_MAXLOOP; n++) 
    {
        // Get the object at the requested index
        hashRecord_t* record = hashMapRecord1(self, v->key);

        // Request a swap
        hashMapRecordSwap(v, record);

        // If swapped record is null,
        // we successfully added the key
        if(!v->key) 
        {
            self->size++;
            return;
        }

        // Else, use the alternative hash for the swapped value
        // 1. Find the new index cell
        // 2. Swap index cells
        record = hashMapRecord2(self, v->key);
        hashMapRecordSwap(v, record);

        if(!v->key) 
        {
            self->size++;
            return;
        }
        // If the newly replaced cell wasn't empty, repeat the process
    }

    // Failed?
    // Grow and rehash
    hashMapGrow(self);
    hashMapPutReHash(self, v);
}

void* hashMapGet(hashMap_t* self, void* key) 
{
    hashRecord_t* r = hashMapRecord1(self, key);
    if(r->key && !self->CMP(key, r->key)) return r->value;
    
    r = hashMapRecord2(self, key);
    if(r->key && !self->CMP(key, r->key)) return r->value;
    
    return 0;
}

void* hashMapGetRaw(hashMap_t* self, void* key) 
{
    hashRecord_t* r = hashMapRecord1(self, key);
    if(key == r->key) return r->value;
    r = hashMapRecord2(self, key);
    if(key == r->key) return r->value;
    return 0;
}

void hashMapFree(hashMap_t* self) 
{
    gcFree(self->records);
    gcFree(self);
}

int hashCompareStr(void* left,void*right)
{
	return strcmp( (char*)left,(char*)right ) ;
}

int hashCompareWStr(void* left,void*right)
{
	return wcscmp( (wchar_t*)left,(wchar_t*)right ) ;
}

void* hashMapDel(hashMap_t* self, void* key) 
{
    hashRecord_t* r = hashMapRecord1(self, key);
    if(r->key && !self->CMP(key, r->key)) 
    {
		r->key=NULL;
		r->value=NULL;
		return NULL ;
    }
    
    r = hashMapRecord2(self, key);
    if(r->key && !self->CMP(key, r->key)) 
    {
		r->key=NULL;
		r->value=NULL;
		return NULL ;
    }
    
    return (void*)-1;
}

void* hashMapDelInt(hashMap_t* self, void* key) 
{
    hashRecord_t* r = hashMapRecord1(self, key);
    if(key == r->key) 
    {
		r->key=NULL;
		r->value=NULL;
		return NULL ;
	}
    r = hashMapRecord2(self, key);
    if(key == r->key) 
    {	
		r->key=NULL;
		r->value=NULL;
		return NULL ;
	}
	
    return (void*)-1;
}



/**/


