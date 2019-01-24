#ifndef _TYPES_H_
#define _TYPES_H_

typedef int bool;
#define false 0
#define true  1

typedef unsigned long StackSize;
typedef unsigned int  Time; // 55 ms multiples
typedef int           ID;

typedef unsigned char IVTNo;
typedef void interrupt (*InterruptRoutine)(...);

#endif
