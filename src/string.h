
//
// cl cxx\src\stdio.c prova.c /Fex.exe /utf-8

#include <stdio.h> 
#include <stdlib.h>
#include <uchar.h> 
#include <wchar.h> 
#include <string.h>
#include <locale.h>
#include <limits.h>

// .............................................. string.h

#ifndef MB_CUR_MAX
    #if defined(_MSC_VER)
        #define MB_CUR_MAX __mb_cur_max
    #else
        #define MB_CUR_MAX 2
    #endif
#endif

/*

size_t      str16len    (char16_t* strarg   )
size_t      str32len    (char32_t* strarg   )
size_t      str8len     (char* strarg       )
size_t      strwlen     (wchar_t* strarg    )

wchar_t*    cnvS32toWS  (char32_t *str      ) 
wchar_t*    cnvS16toWS  (char16_t *str      )
wchar_t*    cnvS8toWS   (char * vIn         )

char*       cnvWStoS8   (wchar_t* ws        ) // MBS
char*       cnvR64toS8  (double r           )
char*       cnvI64toS8  (long long r        )
char*       cnvPTRtoS8  (void* r            )

*/

size_t str16len(char16_t* strarg) ;

size_t str32len(char32_t* strarg) ;

size_t str8len(char* strarg) ;

size_t strwlen(wchar_t* strarg) ;

wchar_t* cnvS32toWS(char32_t *str ) ;

wchar_t* cnvS16toWS(char16_t *str ) ;

wchar_t* cnvS8toWS(char * vIn) ;

char* cnvWStoS8( wchar_t* ws ) ;

char* cnvR64toS8(double r) ;

char* cnvI64toS8(long long r) ;

char* cnvPTRtoS8(void* r) ;



/**/



