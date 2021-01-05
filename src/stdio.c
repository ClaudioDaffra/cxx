

#include "stdio.h"

// .................................................................... stream

console_stream_t std_stream = console_stream_ansi; 

// .................................................................... setUTF8

#if defined(_WIN32) || defined(_WIN64) 

    void cdConsolesetUTF8(void)
    {
        //const wchar_t*   _fontName=L"SimSun-ExtB";
        const wchar_t   _fontName[]=L"SimSun-ExtB";
        SHORT           _fontWeight=FW_NORMAL;
        SHORT           _fontSizeY=16;
        SHORT           _fontSizeX=0;    

        // set font
        
        CONSOLE_FONT_INFOEX info ;
        info.cbSize       = sizeof(info);
        info.dwFontSize.Y = _fontSizeY; // 16
        info.dwFontSize.X = _fontSizeX; // 0    
        info.FontWeight   = _fontWeight;

        wcscpy_s( info.FaceName, _countof(_fontName) , _fontName ) ;
        
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &info);
        
        // set stream
        
         _wsetlocale(LC_ALL , L"it_IT.UTF-8" );  // set locale wide string
        _setmode(_fileno(stdout), _O_U8TEXT);    // set Locale for console
        _setmode(_fileno(stderr), _O_U8TEXT);    // set Locale for console    
        _setmode(_fileno(stdin ), _O_U8TEXT);    // set Locale for console      

        // set CHCP : 936 1252 > win7 : 65001
        
        int chcp=936;            
        SetConsoleCP( chcp ) ;             
        SetConsoleOutputCP( chcp ); 

        // questo per evitare errori di conversione delle stringhe esadecimali
        setlocale ( LC_NUMERIC , "C" ) ;
        std_stream = console_stream_wide ;

    } 
 
#else
   
    void cdConsolesetUTF8(void) 
    {
        setlocale(LC_ALL, "it_IT.UTF-8");

        // questo per evitare errori di conversione delle stringhe esadecimali   
        setlocale ( LC_NUMERIC , "C" ) ;
        
        std_stream = console_stream_wide ;
    }

#endif

void consoleSetMBS(void)
{
#ifdef _MSC_VER
    //const wchar_t*   _fontName=L"SimSun-ExtB";
    const wchar_t   _fontName[]=L"SimSun-ExtB";
    SHORT           _fontWeight=FW_NORMAL;
    SHORT           _fontSizeY=16;
    SHORT           _fontSizeX=0;    

    // set font
    
    CONSOLE_FONT_INFOEX info ;
    info.cbSize       = sizeof(info);
    info.dwFontSize.Y = _fontSizeY; // 16
    info.dwFontSize.X = _fontSizeX; // 0    
    info.FontWeight   = _fontWeight;

    wcscpy_s( info.FaceName, _countof(_fontName) , _fontName ) ;
    
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &info);
    int chcp=65001;            
    SetConsoleCP( chcp ) ;             
    SetConsoleOutputCP( chcp ); 
    
    setlocale(LC_ALL,"it_IT.utf8");
    setlocale(LC_NUMERIC , "C" ) ; 
    
#else

    setlocale(LC_ALL,"");
    setlocale(LC_NUMERIC , "C" ) ;	
    
#endif
}


/**/


