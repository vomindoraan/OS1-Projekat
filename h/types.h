#ifndef _TYPES_H_
#define _TYPES_H_

enum bool { false, true };

typedef unsigned long StackSize;
typedef unsigned int  Time; // 55 ms multiples
typedef int           ID;

typedef unsigned char IVTNo;
typedef void interrupt (*InterruptRoutine)(...);

#endif
