
//
// cl cxx\src\stdio.c prova.c /Fex.exe /utf-8

#include "cxx.h"

size_t 		str16len	(char16_t* strarg) ;
size_t 		str32len	(char32_t* strarg) ;
size_t 		str8len		(char* strarg) ;
size_t 		strwlen		(wchar_t* strarg) ;

wchar_t* 	cnvS32toWS	(char32_t *str ) ;
wchar_t* 	cnvS16toWS	(char16_t *str ) ;
wchar_t* 	cnvS8toWS	(char * vIn) ;

char* 		cnvWStoS8	(wchar_t* ws ) ;

char* 		cnvR32toS8  (float vIn);
wchar_t* 	cnvR32toWS	(float vIn);

char* 		cnvR64toS8	(double r) ;
wchar_t* 	cnvR64toWS	(double Vin) ;

char* 		cnvI64toS8	(long r	) ;
wchar_t* 	cnvI64toWS	(long vIn	) ;

char* 		cnvI80toS8	(long long r) ;
wchar_t* 	cnvI80toWS	(long long r) ;

char* 		cnvPTRtoS8	(void* r) ;
wchar_t* 	cnvPTRtoWS	(void* r) ;


/**/



