
#include "string.h"

// ............................................... str len 16 / 32

size_t str16len(char16_t* strarg)
{
   if(!strarg) return 0; 
   
   char16_t* str = strarg;
   
   for(;*str;++str)
     ; 
     
   return str-strarg;
}

size_t str32len(char32_t* strarg)
{
   if(!strarg) return 0; 
   
   char32_t* str = strarg;
   
   for(;*str;++str)
     ; 
     
   return str-strarg;
}

size_t str8len(char* strarg)
{
   if(!strarg) return 0; 
   
   char* str = strarg;
   
   for(;*str;++str)
     ; 
     
   return str-strarg;
}

size_t strwlen(wchar_t* strarg)
{
   if(!strarg) return 0; 
   
   wchar_t* str = strarg;
   
   for(;*str;++str)
     ; 
     
   return str-strarg;
}


// ............................................... convert String 16 / 32 to Multi Byte
//
// https://www.geeksforgeeks.org/c32rtomb-function-in-c-c/
//

wchar_t* cnvS32toWS(char32_t *str ) 
{ 
    // viene allocata la dimensione massima del vOut
    const size_t    size32  =   sizeof(char32_t);
    const size_t    sizew   =   sizeof(wchar_t ); 
    
    const size_t    slen    =   str32len(str)*size32+1 ;
    const size_t    slenw   =   str32len(str)*sizew +1 ;
 
    // per evitare stringhe NULL U""
    if ( slen==1 ) return NULL ;   
 
    // generalmente MB_CUR_MAX è ugauel a 2
    char*           s       =   malloc ( sizeof(char)*MB_CUR_MAX ) ;
    mbstate_t       p       =   {0}; 
    size_t          length  =   0; 
    int             j       =   0; 
    
    char*           sret    =   malloc( slen ) ;
    size_t          kret    =   0;

    while (str[j]) 
    { 
        length = c32rtomb(s, str[j], &p); // initializing the function
        if ((length == 0) || (length > MB_CUR_MAX)) break; 
        for (size_t i = 0; i < length; ++i) sret[kret++]=s[i] ;
        ++j; 
    } 
    sret[kret]=0; 
    // viene riallocata la dimensione effettiva del vOut
    sret = realloc ( sret , kret*sizeof(char)  );

    wchar_t* wcs =  malloc( slenw ) ;   
    size_t lengthw = mbsrtowcs(wcs, (const char**)&sret, kret, NULL);
    wcs = realloc ( wcs,lengthw*sizeof(wchar_t) );
 
    free(s);
    free(sret);
    
    return wcs; 
} 

wchar_t* cnvS16toWS(char16_t *str ) 
{ 
    // viene allocata la dimensione massima del vOut
    const size_t    size16  =   sizeof(char16_t);
    const size_t    sizew   =   sizeof(wchar_t ); 
    
    const size_t    slen    =   str16len(str)*size16+1 ;
    const size_t    slenw   =   str16len(str)*sizew +1 ;

    // per evitare stringhe NULL u""
    if ( slen==1 ) return NULL ;    
 
    // generalmente MB_CUR_MAX è ugauel a 2
    char*           s       =   malloc ( sizeof(char)*MB_CUR_MAX ) ;
    mbstate_t       p       =   {0}; 
    size_t          length  =   0; 
    int             j       =   0; 
    
    char*           sret    =   malloc( slen ) ;
    size_t          kret    =   0;

    while (str[j]) 
    { 
        length = c16rtomb(s, str[j], &p); // initializing the function
        if ((length == 0) || (length > MB_CUR_MAX)) break; 
        for (size_t i = 0; i < length; ++i) sret[kret++]=s[i] ;
        ++j; 
    } 
    sret[kret]=0; 
    
    // viene riallocata la dimensione effettiva del vOut
    sret = realloc ( sret , kret*sizeof(char)  );

    wchar_t* wcs =  malloc( slenw*sizeof(wchar_t) ) ;   
    size_t lengthw = mbsrtowcs(wcs, (const char**)&sret, kret, NULL);
    wcs = realloc ( wcs,lengthw*sizeof(wchar_t) );
   
    free(s);
    free(sret);
    
    return wcs; 
} 

wchar_t* cnvS8toWS(char * vIn)
{
    const size_t slen=strlen(vIn);
    wchar_t * vOut = malloc ( (slen+1) * sizeof(wchar_t) ) ;

    #if defined(_MSC_VER)   
    mbstowcs_s(NULL,vOut,(slen+1),vIn,slen);
    #else
	mbstowcs (vOut, vIn, slen+1 );
    #endif
  
    return vOut;
}


// ........................................................... convert ws to MB

char* cnvWStoS8( wchar_t* ws )
{
  size_t len = sizeof(wchar_t) * wcslen(ws) ;
  char* vOut = calloc ( sizeof(wchar_t),len );
  
  #if defined(_MSC_VER)
  size_t i=0;
  wcstombs_s(&i,vOut,len,ws,len) ;
  #else
  wcstombs ( vOut, ws, len ) ;
  #endif

  vOut=realloc(vOut,strlen(vOut)+1);

  return vOut ;
}

// ........................................................... convert real32 to S8 WS

char* cnvR32toS8(float vIn)
{
	char vOutChar [17];
	
	#if defined(_MSC_VER)
	_gcvt_s(vOutChar,sizeof(vOutChar),vIn,8);
	#else
	gcvt(vIn,8,vOutChar);
	#endif

	return strdup(vOutChar);
}

wchar_t* cnvR32toWS(float vIn)
{
	char vOutChar [17];
	
	#if defined(_MSC_VER)
	_gcvt_s(vOutChar,sizeof(vOutChar),vIn,8);
	#else
	gcvt(vIn,8,vOutChar);
	#endif

	wchar_t vOut[17];

	#if defined (_MSC_VER)
	mbstowcs_s(NULL,vOut,sizeof(vOut)/2,vOutChar,sizeof(vOutChar));
	#else
	mbstowcs (vOut, vOutChar, sizeof(vOut)/2 );
	#endif

	return wcsdup(vOut);
}

// ........................................................... convert real64 to S8 WS

char* cnvR64toS8(double vIn)
{
    const unsigned char maxBufferLen=32;
    char* vOut=calloc(sizeof(char),maxBufferLen);
    const size_t digits=8;
    
    #if defined(_MSC_VER)
    _gcvt_s( vOut, 32, vIn, digits );
    #else
    gcvt(vIn,digits,vOut);
    #endif

    return vOut ;
}

wchar_t* cnvR64toWS(double vIn)
{
	char vOutChar [26];
	#if defined (_MSC_VER)
	_gcvt_s(vOutChar,sizeof(vOutChar),vIn,17);
	#else
	gcvt(vIn,17,vOutChar);
	#endif	
	
	wchar_t vOut[26];
	
	#if defined (_MSC_VER)
	mbstowcs_s(NULL,vOut,sizeof(vOut)/2,vOutChar,sizeof(vOutChar));
	#else
	mbstowcs (vOut, vOutChar, sizeof(vOut)/2 );
	#endif
	
	return wcsdup(vOut);
}

// ........................................................... convert I80 to S8 --

char* cnvI80toS8(long long vIn)
{
    const unsigned char maxBufferLen=32;
    char* vOut=calloc(sizeof(char),maxBufferLen);
    snprintf(vOut, maxBufferLen, "%lld", vIn);

    return vOut ;
}

wchar_t* cnvI80toWS(long long vIn)
{
    const unsigned char maxBufferLen=32;
    wchar_t* vOut=calloc(sizeof(wchar_t),maxBufferLen);
    swprintf(vOut, maxBufferLen, L"%lld", vIn);

    return wcsdup(vOut) ;
}


// ........................................................... convert I64 to S8 WS

char* cnvI32toS8(int vIn)
{
	char vOut [12];
	
	#if defined (_MSC_VER)
	_itoa_s(vIn,vOut,sizeof(vOut),10);
	#else
	sprintf( vOut, "%d", vIn);
	#endif

    return strdup(vOut) ;
}

wchar_t* cnvI32toWS(int vIn)
{
#if defined (_MSC_VER)
    wchar_t vOut [12];	
    _itow_s(vIn,vOut,sizeof(vOut)/2,10);
    return wcsdup(vOut);	
#else
    const unsigned char maxBufferLen=32;
    wchar_t* vOut=calloc(sizeof(wchar_t),maxBufferLen);
    swprintf(vOut, maxBufferLen, L"%d", vIn);
    return vOut ;
#endif
}


// ........................................................... convert I64 to S8 WS

char* cnvI64toS8(long vIn)
{
    const unsigned char maxBufferLen=32;
    char* vOut=calloc(sizeof(char),maxBufferLen);
    snprintf(vOut, maxBufferLen, "%ld", vIn);

    return vOut ;
}

wchar_t* cnvI64toWS(long vIn)
{
#if defined (_MSC_VER)
    wchar_t vOut [12];	
    _itow_s(vIn,vOut,sizeof(vOut)/2,10);
    return wcsdup(vOut);	
#else
    const unsigned char maxBufferLen=32;
    wchar_t* vOut=calloc(sizeof(wchar_t),maxBufferLen);
    swprintf(vOut, maxBufferLen, L"%ld", vIn);
    return vOut ;
#endif
}

// ........................................................... convert I64 to S8 WS

char* cnvPTRtoS8(void* vIn)
{
    const unsigned char maxBufferLen=32;
    char* vOut=calloc(sizeof(char),maxBufferLen);
    
    #if defined (_MSC_VER)
    snprintf(vOut, maxBufferLen, "0x%p", vIn);
    #else
    snprintf(vOut, maxBufferLen, "%p", vIn);
    #endif
    
    return vOut ;
}  

wchar_t* cnvPTRtoWS(void* vIn)
{
    const unsigned char maxBufferLen=32;
    wchar_t* vOut=calloc(sizeof(wchar_t),maxBufferLen+1);
    
    #if defined (_MSC_VER)    
    swprintf(vOut, maxBufferLen*sizeof(wchar_t), L"0x%p", vIn);
    #else
    swprintf(vOut, maxBufferLen*sizeof(wchar_t), L"%p", vIn);
    #endif    
    
    return vOut ;
}  



/**/



