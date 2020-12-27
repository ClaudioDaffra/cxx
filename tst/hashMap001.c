

#include <stdio.h>
#include "../lib/hashMap.h"


// clear  ; gcc lib/hashMap.c tst/hashMap001.c -o bin/x -Wall -pedantic -Wextra
//
//

int main() 
{
	// ......................................................... new
	
    hashMap_t* table = hashMapNew(8);

	// ......................................................... insert

	hashMapPut(table, "abc","123");
	hashMapPut(table, "def","456");
	hashMapPut(table, "ghi","789");
		
    printf("Key count: %d\n", (int)hmapSize(table));

	// ......................................................... get
	    
    void* value = hashMapGet(table, "def");
    
    if(value) {
        printf("Found: %s\n", (char*)value);
    }

	// ......................................................... size capacity

	printf ( "size %zu capacity %zu\n",hmapSize(table) , hmapCapacity(table) ) ;
 
 	// ......................................................... iterator

    for( itMap_t it = itMapBegin(table) ; it < itMapEnd(table) ; itMapNext(it) )
    {
       if ( itMapKey(it)  ) 
       {
		   printf ( "key %s value %s\n",(char*)it->key,(char*)it->value );
	   }
    }       

	// ......................................................... free
	            
    hashMapFree(table);
    
    return 0;
}
