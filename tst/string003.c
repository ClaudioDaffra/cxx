
#include "../src/cxx.h"
#include "../src/string8.h"

/*
	1)	gcc src/gc.c src/stdio.c src/string.c tst/string003.c 	-o bin/x	-Wall -pedantic -Wextra

	2)	sh buildLib.h
		clear  	; gcc tst/string003.c	lib/libcxx.so   -o bin/x	-Wall -Wextra -pedantic

	3)  cls     & cl 	src\gc.c src\stdio.c src\string.c tst\string003.c    /Febin\x.exe 	/utf-8 /WX
    
    4)  wbuildLib.bat
        cls & cl tst\string003.c lib\cxx.lib            /Febin\x.exe    /utf-8 /WX
*/

#define stringCheckCapacity(TYPE,ID,LEN)\
    if (LEN>=(ID).capacity)\
    {\
        while (LEN > (ID).capacity) (ID).capacity *= 2;\
       (ID).data = (TYPE*) gcRealloc (  (ID).data, (ID).capacity *  sizeof(TYPE)   );\
    };
    
#define stringFromS8(ID,STR)\
do{\
    size_t len=strlen(STR);\
    stringCheckCapacity(char,ID,len);\
    strcpy ( (ID).data , STR );\
    (ID).size = len;\
}while(0);

#define stringFromWS(ID,WSTR)\
do{\
    char* STR=cnvWStoS8(WSTR);\
    size_t len=strlen(STR);\
    stringCheckCapacity(char,ID,len);\
    strcpy ( (ID).data , STR );\
    (ID).size = len;\
}while(0);

#define stringLen(ID)   strlen((ID).data)
#define stringMBLen(ID) strmblen((ID).data)

int main() 
{
    gcStart();
    
    consoleSetMBS();
    
    //.......................... typedef def alloc

    stringTypeDef(char,s1) ;

    string_s1_t s1 ;

    stringAlloc(s1,8);

    //.......................... init
    
    stringFromS8 ( s1 , "precipitevolissimevolmente" ) ;

    printf ( "%s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringLen(s1) ) ;

    const char* temp = "Claudio Daffra" ;
    stringFromS8 ( s1 , temp ) ;

    printf ( "%s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringMBLen(s1) ) ;

    stringFromWS ( s1 , L"你好吗" ) ;

    printf ( "%s -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,stringSize(s1),stringCapacity(s1),stringEmpty(s1),stringMBLen(s1) ) ;
    
    //.......................... init
    
    //..........................    
    gcStop();
    
    return 0; 
} 



