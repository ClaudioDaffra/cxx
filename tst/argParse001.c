
#include "../src/cxx.h"

/*
	1)	clear   ; gcc src/argParse.c tst/argParse001.c  -o bin/x   -Wall -pedantic -Wextra

	2)	sh buildLib.sh
		clear   ; gcc tst/argParse001.c lib/libcxx.so 	-o bin/x 	-Wall -pedantic -Wextra
	
        ./bin/x /help
	
    3)  cls     & cl src\argParse.c tst\argParse001.c   /Febin\x.exe /WX /utf-8

    4)  wbuildLib.bat
        cls & cl tst\argParse001.c lib\cxx.lib          /Febin\x.exe /WX /utf-8
        
        C:\project\cxx>bin\x.exe -i "file.txt"
        file input [file.txt]
*/

int main ( int argc , const char** argv ) 
{
    //*********
    //  global
    //*********
    
    char *  fi=NULL ;
    char *  fo=NULL ;
    bool    fDebug=0 ;
    
    //*********
    //  ARGPARSE
    //*********
 
    argParseUsage ( usages ,
        "c12 [options] [[--,/] args]",
        "c12 [options] [[-   ] args]"
    ) ;

    argParseOption ( options ) 
    {
        OPT_HELP(),
        OPT_GROUP   ("Basic options"),
            OPT_STRING  ('i', "input"   , &fi       , "file input to read"  , NULL, 0, 0 ),
            OPT_STRING  ('o', "output"  , &fo       , "file output to write", NULL, 0, 0 ),
            OPT_BOOLEAN ('d', "debug"   , &fDebug   , "debug"               , NULL, 0, 0 ),
        OPT_END()
    };    
 
    argparse_t argparse;

    argParseInit( &argparse, options, usages, 0);

    argParseDescribe ( &argparse, 
        "\nC intepreter.", 
        "\nby Claudio Daffra (2019)."
    );

    argParseStart ( &argparse ) ;

    //*********
    //  MAIN
    //*********
 
    if ( fi != NULL )
    {
        fprintf ( stdout , "\n file input [%s]",fi  ) ;   
    }  
   
    if ( fo != NULL )
    {
        fprintf ( stdout , "\n file output [%s]",fo  ) ;   
    }  

    if ( fDebug != 0 )
    {
        fprintf ( stdout , "\n debug [%d]",fDebug  ) ;   
    } 
    
    fprintf ( stdout , "\n"  ) ;
 
    return 0;
} 



/**/


