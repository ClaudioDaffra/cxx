

#include <stdio.h>
#include "../lib/gc.h"
#include "../lib/hashMap.h"

// clear  ; gcc lib/gc.c lib/hashMap.c tst/hashMap004.c -o bin/x 		-Wall -pedantic -Wextra
// cls    & cl  lib\gc.c lib\hashMap.c tst\hashMap004.c /Febin\x.exe 	/utf-8 /W4 /EHsc
//

int main() 
{
	gcStart() ;
	
	// ......................................................... new
	
    hashMap_t* table = hashMapNew(8);

	// ......................................................... insert

	hashMapSet(table, "a1","123");
	hashMapSet(table, "a2","456");
	hashMapSet(table, "a3","789");
	hashMapSet(table, "a4","abc");
	 		
    printf("Key count: %d\n", (int)hmapSize(table));

	// ......................................................... get
	    
    void* value = hashMapGet(table, "a2" );
    
    if(value) printf("Found: %s\n", (char*)value);

	// ......................................................... del
	
	//hashMapDel(table, "a2" ) ;
	
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
    
    gcStop();
    
    return 0;
}
