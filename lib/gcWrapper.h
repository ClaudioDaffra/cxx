#ifndef gc_wrapper
#define gc_wrapper

#ifdef __linux__
#define _GNU_SOURCE 
#endif

#define free    gcFree
#define malloc  gcMalloc
#define realloc gcRealloc
#define calloc	gcCalloc
#define strdup  gcStrDup
#define wcsdup  gcWcsDup


#endif
