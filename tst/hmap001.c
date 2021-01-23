
#include "../src/cxx.h"
#include "../src/hmap.h"

/*

    cl  src\hmap.c tst\hmap001.c src\gc.c   /Fex.exe /WX
    gcc src\hmap.c tst\hmap001.c src\gc.c   -o x.exe -Wall -Wextra  
     
    gcc src/gc.c src/hmap.c tst/hmap001.c    -o x     -Wall -Wextra  

*/

//------------------------------------------------------------
// MAIN
//------------------------------------------------------------

int main(void)
{
    gcStart();
 
    //

    //hmap_t* x = hmap.New();
 
    hmapType(x);
 
    hmapNew(x);
 
    //
 
	hmap.insert(x, "xxx", "yyy");
	hmap.insert(x, "key", "value");
	
	printf ( "\n key value = %s  ", (char *) hmap.find(x, "key") ) ;
	
	printf ( "\n NO key value = %s  ", (char *) hmap.find(x, "null") ) ;
	
	printf ( "\n count = %lu / %lu ",   (long unsigned )hmap.size(x)	, (long unsigned )hmap.max_size(x)	) ;	
 	
	hmap.erase(x, "key" );	
 
	printf ( "\n ERASE key value = %s  ", (char *) hmap.find(x, "key") ) ;	
	
	printf ( "\n count = %lu / empty ? %d ",   (long unsigned )hmap.size(x)	, hmap.empty(x)	) ;	

	// INSERT	
	  
	hmap.insert(x, "key1", "value1" );
	hmap.insert(x, "key2", "value2" );
	hmap.insert(x, "key3", "value3" );

	// Iterator

	printf ( "\n begin %p " , hmap.begin(x) ) ;
	printf ( "\n end   %p " , hmap.end(x) ) ;

	for ( hmapIt_t* it=hmap.begin(x) ; it != hmap.end(x) ; it = hmap.next(x,it) )  
	{
		printf ( "\n ((%s,%s)) ", (const char*)it->data , (char*)hmap.find( x, (char*)it->data) );
	}
 
	// AT
    
	printf ( "\n AT[2] ((%s)) ", (char*)hmap.at(x,2) ) ;	

	// COPY
		
	hmap_t* y = hmap.New();
 
	hmap.copy ( y , x ) ;

	for ( hmapIt_t* it=hmap.begin(y) ; it != hmap.end(y) ; it = hmap.next(y,it) )  
	{
		printf ( "\n ((KEY::%s VALUE::%s)) ", (const char*)it->data , (char*)hmap.find(x, (char*)it->data) );
	}
 
	// GET Iterator FROM KEY
	
	hmapIt_t* it = hmap.Iterator ( x , "key1" );

	printf ( " value %s.\n",(char*)it->data ) ;
	// CLEAR Delete	
 
	hmap.clear ( x ) ;	

	//hmap.Delete ( x ) ; // NO MORE MEMORY LEAK !
	hmap.Delete ( y ) ;	

    printf ("\n"); 

    //
 
    gcStop() ;
 
  return 0;
}
	
/*  OK

==13879== 
==13879== HEAP SUMMARY:
==13879==     in use at exit: 0 bytes in 0 blocks
==13879==   total heap usage: 44 allocs, 44 frees, 18,176 bytes allocated
==13879== 
==13879== All heap blocks were freed -- no leaks are possible
==13879== 
==13879== For counts of detected and suppressed errors, rerun with: -v
==13879== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/


/*
    E:\c--\tst>x.exe

     key value = value
     NO key value = (null)
     count = 2 / 1024
     ERASE key value = (null)
     count = 1 / empty ? 0
     begin a314d0
     end   0
     ((xxx,yyy))
     ((key1,value1))
     ((key2,value2))
     ((key3,value3))
     AT[2] ((key2))
     ((KEY::xxx VALUE::yyy))
     ((KEY::key1 VALUE::value1))
     ((KEY::key2 VALUE::value2))
     ((KEY::key3 VALUE::value3))
    E:\c--\tst>

*/

