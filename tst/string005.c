
#include "../src/cxx.h"
#include "../src/utf8string.h"
#include "../src/mbstring.h"

/*
	1)	gcc src/gc.c src/stdio.c src/string.c tst/string005.c 	-o bin/x	-Wall -pedantic -Wextra

	2)	sh buildLib.h
		clear  	; gcc tst/string005.c	lib/libcxx.so   -o bin/x	-Wall -Wextra -pedantic

	3)  cls     & cl 	src\gc.c src\stdio.c src\string.c tst\string005.c    /Febin\x.exe 	/utf-8 /WX
    
    4)  wbuildLib.bat
        cls & cl tst\string005.c lib\cxx.lib            /Febin\x.exe    /utf-8 /WX
*/

#define mbstringCheckCapacity(TYPE,ID,LEN)\
    if (LEN>=(ID).capacity)\
    {\
        while (LEN > (ID).capacity) (ID).capacity *= 2;\
       (ID).data = (TYPE*) gcRealloc (  (ID).data, (ID).capacity *  sizeof(TYPE)   );\
    };
    
#define mbstringFromWS(ID,WSTR)\
do{\
    char* STR=cnvWStoS8(WSTR);\
    size_t len=strlen(STR);\
    mbstringCheckCapacity(char,ID,len);\
    strcpy ( (ID).data , STR );\
    (ID).size = len;\
}while(0);


#define mbstringLen(ID) strmblen((ID).data)

int main() 
{
    gcStart();
    
    consoleSetMBS();
    
    //.......................... typedef def alloc

    mbstringTypeDef(char,s1) ;

    mbstring_s1_t s1 ;

    mbstringAlloc(s1,8);

    // multi byte mbstring

    mbstringFromWS ( s1 , L"你好吗" ) ;

    printf ( "%s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,mbstringSize(s1),mbstringCapacity(s1),mbstringEmpty(s1),mbstringLen(s1) ) ;
    
    //.......................... init
    
    //..........................    
    gcStop();
    
    return 0; 
} 

