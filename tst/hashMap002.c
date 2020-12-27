

#include <stdio.h>
#include <locale.h>
#include "../lib/hashMap.h"

// clear  ; gcc lib/hashMap.c tst/hashMap001.c -o bin/x -Wall -pedantic -Wextra
//
//

int main() 
{
	#ifdef __linux__
	setlocale(LC_ALL, "it_IT.UTF-8");
	#else
	#pragma("windows and other locale output console not implemetd yet!")
	#endif
	
	// ......................................................... new
	
    hashMap_t* table = hashMapNew(8);
	table->CMP = hashCompareWStr ;

	// ......................................................... insert

	hashMapPut(table, L"abc",L"123");
	hashMapPut(table, L"汉字",L"456");
	hashMapPut(table, L"ghi",L"789");
		
    wprintf(L"Key count: %d\n", (int)hmapSize(table));

	// ......................................................... get
	    
    void* value = hashMapGet(table, L"汉字");
    
    if(value) {
        wprintf(L"Found: %ls\n", (wchar_t*)value);
    }

	// ......................................................... size capacity

	wprintf ( L"size %zu capacity %zu\n",hmapSize(table) , hmapCapacity(table) ) ;
 
 	// ......................................................... iterator

    for( itMap_t it = itMapBegin(table) ; it < itMapEnd(table) ; itMapNext(it) )
    {
       if ( itMapKey(it)  ) 
       {
		   wprintf ( L"key %ls value %ls\n",(wchar_t*)it->key,(wchar_t*)it->value );
	   }
    }       

	// ......................................................... free
	            
    hashMapFree(table);
    
    return 0;
}
