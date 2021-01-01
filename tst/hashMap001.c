
#include "../src/hashMap.h"

/*

    clear  ; gcc src/gc.c src/hashMap.c tst/hashMap001.c -o  bin/x           -Wall -pedantic -Wextra
    valgrind ./bin/x

    cls & cl lib\gc.c src\hashMap.c tst\hashMap001.c         /Febin/x.exe    /W4

*/
    
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
		
	hashMapDelete(hm);

	gcStop();
	
return 0;
}
