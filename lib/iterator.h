#ifndef cdIterator
#define cdIterator

#define iterator(TYPE)      TYPE*
#define itNext(IT)          (IT++)
#define itPrev(IT)          (IT--) 
#define itAdvance(IT,N)     (IT+=N)         
#define itRetreat(IT,N)     (IT-=N)
#define itDifference(P1,P2) ((ptrdiff_t)((char*)P2 - (char*)P1))
/*
#define itBegin(ID) &(ID).data[0]
#define itEnd(ID)   &(ID).data[(ID).size]
*/

#endif



/**/


