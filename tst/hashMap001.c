
#include "../src/hashMap.h"

// clear  ; gcc src/gc.c src/hashMap.c tst/hashMap001.c -o bin/x -Wall -pedantic -Wextra
//
//

int main()
{
	gcStart();
	
	setlocale(LC_ALL, "") ;


	char*source="claudio";

	hashMap_t hm = hashMapNew(0);

	hashMapSet(hm,cnvWS2S(L"你好吗") 							, (void*) 100 );
	hashMapSet(hm,cnvWS2S(L"§°çéè") 							, (void*) 200 );
	hashMapSet(hm,cnvWS2S(L"°*§ç") 								, (void*) 300 );
	hashMapSet(hm,source 										, (void*) 400 );	
	hashMapSet(hm,cnvD2S (235325325325325353.14159265358L) 		, (void*) 500 );
	hashMapSet(hm,cnvL2S (235325325325325353L) 					, (void*) 600 );
	hashMapSet(hm,cnvP2S (&source) 								, (void*) &source 	);		


	if (hashMapGet(hm, cnvWS2S(L"你好吗")) )
			printf("found: %zu\n", (size_t)*hm->value);
	else 
			printf("error\n");
			
	if (hashMapGet(hm, cnvD2S(235325325325325353.14159265358L)) )
			printf("found: %zu\n", (size_t)*hm->value);
	else 
			printf("error\n");	

	
	hashMapDelete(hm);

	gcStop();
	
return 0;
}

