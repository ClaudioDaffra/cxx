
#include "../src/cxx.h"
#include "../src/stringw.h"

/*
	1)	gcc src/gc.c src/stdio.c src/string.c tst/string004.c 	-o bin/x	-Wall -pedantic -Wextra

	2)	sh buildLib.h
		clear  	; gcc tst/string004.c	lib/libcxx.so   -o bin/x	-Wall -Wextra -pedantic

	3)  cls     & cl 	src\gc.c src\stdio.c src\string.c tst\string004.c    /Febin\x.exe 	/utf-8 /WX
    
    4)  wbuildLib.bat
        cls & cl tst\wstring004.c lib\cxx.lib            /Febin\x.exe    /utf-8 /WX
*/

#define wstringCheckCapacity(TYPE,ID,LEN)\
    if (LEN>=(ID).capacity)\
    {\
        while (LEN > (ID).capacity) (ID).capacity *= 2;\
       (ID).data = (TYPE*) gcRealloc (  (ID).data, (ID).capacity *  sizeof(TYPE)   );\
    };
    
#define wstringFromWS(ID,STR)\
do{\
    size_t len=wcslen(STR);\
    wstringCheckCapacity(wchar_t,ID,len);\
    wcscpy ( (ID).data , STR );\
    (ID).size = len;\
}while(0);

#define wstringFromS8(ID,STR) wstringFromWS( ID , cnvS8toWS((char*)STR) ) 

#define wstringLen(ID)   wcslen((ID).data)


int main() 
{
    gcStart();
    
    consoleSetUTF8();
    
    //.......................... typedef def alloc

    wstringTypeDef(wchar_t,s1) ;

    wstring_s1_t s1 ;

    wstringAlloc(s1,8);

    //.......................... init
    
    wprintf (L"\n");
    
    wstringClear(s1);
    
    wprintf ( L"s1 clear s1:[%ls] len(%zu).\n",s1.data,wcslen(s1.data));

    //.......................... from wchar_t*
    
    wstringFromWS ( s1 , L"precipitevolissimevolmente" ) ;

    wprintf ( L"%ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) ) ;

    //.......................... from char*

    const char* temp = "Claudio Daffra" ;
    wstringFromS8 ( s1 , temp ) ;

    wprintf ( L"%ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) ) ;

  
    //.......................... push Back "Claudio Daffra" + L'X' + L'Y'
    
    wstringPushBack( s1 , L'X' ) ;
    wstringPushBack( s1 , L'Y' ) ;    
    
    wprintf ( L"after push back XY s1 [%ls].\n",wstringData(s1) ) ;

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;

    wstringPopBack(s1); 
    
    wprintf ( L"after pop back s1 [%ls].\n",wstringData(s1) ) ;

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
        
    //..........................  front back at

    wprintf ( L"front [%lc] back [%lc] at[3]==[%lc].\n",wstringFront(s1),wstringBack(s1),wstringAt(s1,3) ) ;
    
    //..........................  shrink to fit
    
    wstringShrinkToFit(s1);

    wprintf ( L"[s1] %ls -> size %zu capacity %zu empty %u len(%zu)\n"
        ,s1.data,wstringSize(s1),wstringCapacity(s1),wstringEmpty(s1),wstringLen(s1) )   ;
        
    //..........................   

    wstringDealloc(s1);
    
    gcStop();
    
    return 0; 
} 



