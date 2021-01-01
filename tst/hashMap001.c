
#include "../src/hashMap.h"

// clear  ; gcc src/gc.c src/hashMap.c tst/hashMap001.c -o bin/x -Wall -pedantic -Wextra
//
//

int main()
{
	// ...................................................... start
	
	gcStart();

	setlocale(LC_ALL, "") ;

	// ...................................................... new

	hashMap_t hm = hashMapNew(0);

	// ...................................................... set
	
	char*source="claudio";	
	
	hashMapSet(hm,cnvWS2S(L"你好吗") 							, (void*) gcIntDup(100) );
	hashMapSet(hm,cnvWS2S(L"§°çéè") 							, (void*) gcIntDup(101) );
	hashMapSet(hm,cnvWS2S(L"°*§ç") 								, (void*) gcIntDup(102) );
	hashMapSet(hm,source 										, (void*) gcIntDup(103) );	
	hashMapSet(hm,cnvD2S (235325325325325353.14159265358L) 		, (void*) gcIntDup(104) );
	hashMapSet(hm,cnvL2S (235325325325325353L) 					, (void*) gcIntDup(105) );
	hashMapSet(hm,cnvP2S (&source) 								, (void*) gcIntDup(106) );		

	// ...................................................... get

	if (hashMapGet(hm, cnvWS2S(L"你好吗")) )
			printf("found: %d\n", *(int*) (*hm->value) ) ;
	else 
			printf("error\n");
	
	if (hashMapGet(hm, cnvD2S(235325325325325353.14159265358L)) )
			printf("found: %d\n", *(int*) (*hm->value) ) ;
	else 
			printf("error\n");	

	// ...................................................... iterator
	
	printf ("table size %d capacity %d :\n",hashMapSize(hm),hashMapCapacity(hm) ) ;

    for ( hashMapIt_t it=hashMapBegin(hm) ; it < hashMapEnd(hm); ++it )
    {
		if (*it!=NULL) 
		{
			if ((*it)->key!=NULL)
			
				printf ( "key(%20s) value(%p)\n", (*it)->key,(*it)->value ) ;
		
		}
	}

	// ...................................................... free
	
	hashMapDelete(hm);

	// ...................................................... stop
	printf("\n");
	gcStop();

	return 0;
}

