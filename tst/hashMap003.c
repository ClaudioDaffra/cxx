

#include <stdio.h>
#include <locale.h>
#include "../lib/stdio.h"
#include "../lib/hashMap.h"

// clear  ; gcc lib/stdio.c lib/hashMap.c tst/hashMap003.c -o bin/x -Wall -pedantic -Wextra
// cls    & cl lib\stdio.c lib\hashMap.c tst\hashMap003.c /Febin\x.exe /utf-8 /W4 /EHsc
//
#include <stdint.h>



int main() 
{
	consoleSetUTF8();

	// ......................................................... new
	
    hashMap_t* table = hashMapNew(8);

	// ......................................................... insert
	
    const double PI = 1241243.14159265358979 ;
    
	hashMapPut(table, hmReal(PI),"123");
	hashMapPut(table, "ciao","456");
	hashMapPut(table, hmInt(3),"789");

    printf("Key count: %d\n", (int)hmapSize(table));

	// ......................................................... get
	    
    void* value ;

    value = hashMapGetRaw(table,hmReal(PI));
    if(value) printf("Found: %s\n", (char*)value);

    value = hashMapGetRaw(table,hmReal(1241243.141592654)); // not found right !
    if(value) printf("Found: %s\n", (char*)value);
    
    value = hashMapGetRaw(table,"ciao");
    if(value) printf("Found: %s\n", (char*)value);
    
    value = hashMapGetRaw(table,hmInt(3));
    if(value) printf("Found: %s\n", (char*)value);

	// ......................................................... size capacity

	printf ( "size %zu capacity %zu\n",hmapSize(table) , hmapCapacity(table) ) ;
 
 	// ......................................................... iterator

    for( itMap_t it = itMapBegin(table) ; it < itMapEnd(table) ; itMapNext(it) )
    {
       if ( itMapKey(it)  ) 
       {
		   printf ( "value %s\n",(char*)it->value );
	   }
    }       

	// ......................................................... free
	            
    hashMapFree(table);
    
    return 0;
}
