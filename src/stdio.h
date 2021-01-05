#ifndef cdSTDIO
#define cdSTDIO

#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>


// questo per evitare warning comparazione ( signed wchar_t / unsigned wchar_t )
#define _WEOF (wchar_t)WEOF

// (not standard ) : error: use of undeclared identifier 'errno_t'
typedef int errno_t;

//

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
#include <io.h>
#include <fcntl.h>

#endif

#include <wchar.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>

typedef enum console_stream_e
{
    
    console_stream_ansi=100,
    console_stream_wide=200
    
} console_stream_t ;

extern console_stream_t std_stream;


extern void cdConsolesetUTF8    ( void    ) ;

#define consoleSetUTF8  cdConsolesetUTF8
void 	consoleSetMBS	(void) ;


#endif 



/**/


