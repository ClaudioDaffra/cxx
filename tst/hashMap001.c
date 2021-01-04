
#include "../src/cxx.h"

/*

    1) 	clear  ; gcc src/gc.c src/string.c src/hashMap.c tst/hashMap001.c -o  	-o bin/x	-Wall -pedantic -Wextra
    
    2) 	sh build.lib
		clear  ; gcc tst/hashMap001.c lib/libcxx.so 							-o bin/x	-Wall -pedantic -Wextra
		
    valgrind ./bin/x

    cls & cl lib\gc.c src\string.c src\hashMap.c tst\hashMap001.c         /Febin/x.exe    /WX

*/
 
size_t	f1(void *key, size_t count,void** value, void *user)
{
	(void)count;
	(void)user;
	printf ( "key : %-20s , value %p .\n",(char*)key , *value ) ;
	return 1;
}
   
int main()
{
	gcStart();
	
	setlocale(LC_ALL, "") ;

	char*source="claudio";

	// ...................................................... new
	
	hashMap_p hm = hashMapNew(0);

	// ...................................................... set
	
	hashMapSet(hm,cnvWStoS8(L"你好吗") 							, (void*) 100 );
	hashMapSet(hm,cnvWStoS8(L"§°çéè") 							, (void*) 200 );
	hashMapSet(hm,cnvWStoS8(L"°*§ç") 							, (void*) 300 );
	hashMapSet(hm,source 										, (void*) 400 );	
	hashMapSet(hm,cnvR64toS8 (235325325325325353.14159265358L)	, (void*) 500 );
	hashMapSet(hm,cnvI64toS8 (235325325325325353L) 				, (void*) 600 );
	hashMapSet(hm,cnvPTRtoS8 (&source) 							, (void*) gcStrDup("daffra") 	);		

	// ...................................................... get
	
	if (hashMapGet(hm, cnvWStoS8(L"你好吗")) )
			printf("found: %zu\n", (size_t)*hm->value);
	else 
			printf("error\n");
			
	if (hashMapGet(hm, cnvPTRtoS8 (&source)) )
			printf("found: %s\n", (char*)*hm->value);
	else 
			printf("error\n");	

	// ...................................................... iterator
	
	printf ("table size %zu capacity %zu :\n",hashMapSize(hm),hashMapCapacity(hm) ) ;

    for ( hashMapIt_t it=hashMapBegin(hm) ; it < hashMapEnd(hm); ++it )
    {
		if (*it!=NULL) 
		{
			if ((*it)->key!=NULL)
				if ((*it)->value!=NULL)
				
				printf ( "key(%-20s) \nvalue(%p) %zu \n\n", (*it)->key,(*it)->value , (size_t)(*it)->value ) ;
		}
	}

	// ...................................................... for each
	
	hashMapForEach(hm,f1,NULL);
	
	// ...................................................... delete
				
	hashMapDelete(hm);

	gcStop();
	
return 0;
}
