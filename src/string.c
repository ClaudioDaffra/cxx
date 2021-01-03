
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
    // viene allocata la dimensione massima del buffer
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
    // viene riallocata la dimensione effettiva del buffer
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
    // viene allocata la dimensione massima del buffer
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
    
    // viene riallocata la dimensione effettiva del buffer
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


// ........................................................... convert

char* cnvWStoS8( wchar_t* ws )
{
  size_t len = sizeof(wchar_t) * wcslen(ws) ;
  char* buffer = calloc ( sizeof(wchar_t),len );
  
  #if defined(_MSC_VER)
  size_t i=0;
  wcstombs_s(&i,buffer,len,ws,len) ;
  #else
  wcstombs ( buffer, ws, len ) ;
  #endif

  buffer=realloc(buffer,strlen(buffer)+1);

  return buffer ;
}

char* cnvR64toS8(double r)
{
    const unsigned char maxBufferLen=32;
    char* buffer=calloc(sizeof(char),maxBufferLen);
    const size_t digits=8;
    
    #if defined(_MSC_VER)
    _gcvt_s( buffer, 32, r, digits );
    #else
    gcvt(r,digits,buffer);
    #endif

    return buffer ;
}

char* cnvI64toS8(long long r)
{
    const unsigned char maxBufferLen=32;
    char* buffer=calloc(sizeof(char),maxBufferLen);
    snprintf(buffer, maxBufferLen, "%lld", r);

    return buffer ;
}

char* cnvPTRtoS8(void* r)
{
    const unsigned char maxBufferLen=32;
    char* buffer=calloc(sizeof(char),maxBufferLen);
    snprintf(buffer, maxBufferLen, "%p", r);
   
    return buffer ;
}  



