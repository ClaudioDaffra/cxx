

#include <stdio.h>
#include "../lib/hashMap.h"


// clear  ; gcc lib/hashMap.c tst/hashMap003.c -o bin/x -Wall -pedantic -Wextra
// cls    & cl lib\stdio.c lib\hashMap.c tst\hashMap003.c /Febin\x.exe /utf-8 /W4 /EHsc
//

int main() 
{
	// ......................................................... new
	
    hashMap_t* table = hashMapNew(8);

	// ......................................................... insert

	hashMapSetInt(table, 1,"123");
	hashMapSetInt(table, 2,"456");
	hashMapSetInt(table, 3,"789");
 		
    printf("Key count: %d\n", (int)hmapSize(table));

	// ......................................................... get
	    
    void* value = hashMapGetInt(table, 2);
    
    if(value) printf("Found: %s\n", (char*)value);

	// ......................................................... size capacity

	printf ( "size %zu capacity %zu\n",hmapSize(table) , hmapCapacity(table) ) ;
 
 	// ......................................................... iterator

    for( itMap_t it = itMapBegin(table) ; it < itMapEnd(table) ; itMapNext(it) )
    {
       if ( itMapKey(it)  ) 
       {
		   printf ( "key %zu value %s\n",(uint64_t)it->key,(char*)it->value );
	   }
    }       

	// ......................................................... free
	            
    hashMapFree(table);
    
    return 0;
}
