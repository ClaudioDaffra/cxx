
//
// cl cxx\src\stdio.c prova.c /Fex.exe /utf-8

#include "cxx.h"

// ........................................... strlen

size_t 		str16len	(char16_t* 	    strarg) ;
size_t 		str32len	(char32_t* 	    strarg) ;
size_t 		str8len		(char* 		    strarg) ;
size_t 		strwlen		(wchar_t* 	    strarg) ;
size_t      strmblen    (const char*    strarg) ;
#define     strmbslen(VIN)  strmblen(VIN)
 
// ........................................... cnv vIn <-> s8

wchar_t* 	cnvS32toWS	(char32_t *	vIn ) ;
wchar_t* 	cnvS16toWS	(char16_t *	vIn ) ;
wchar_t* 	cnvS8toWS	(char * 	vIn	) ;

char* 		cnvWStoS8	(wchar_t* vIn) ;
#define     cnvWStoMBS(VIN)  cnvWStoS8(VIN)

// ........................................... cnv number

char* 		cnvI32toS8	(int vIn);
wchar_t* 	cnvI32toWS	(int vIn);

#define		cnvI16toS8(VIN)	cnvI32toS8((int)VIN)	
#define		cnvI16toWS(VIN)	cnvI32toWS((int)VIN)	

char* 		cnvI64toS8	(long vIn) ;
wchar_t* 	cnvI64toWS	(long vIn) ;

char* 		cnvI80toS8	(long long vIn) ;
wchar_t* 	cnvI80toWS	(long long vIn) ;

char* 		cnvPTRtoS8	(void* vIn) ;
wchar_t* 	cnvPTRtoWS	(void* vIn) ;

char* 		cnvR32toS8  (float vIn);
wchar_t* 	cnvR32toWS	(float vIn);

char* 		cnvR64toS8	(double vIn) ;
wchar_t* 	cnvR64toWS	(double Vin) ;



/**/


