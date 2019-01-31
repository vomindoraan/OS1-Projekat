#ifndef _TYPES_H_
#define _TYPES_H_

#include <stddef.h>

typedef int bool;
#define false 0
#define true  1

typedef unsigned int  Word;
typedef unsigned int  Register;

typedef unsigned long StackSize;
typedef unsigned int  Time; // 55 ms multiples
typedef          int  ID;

typedef unsigned char IVTNo;
typedef void interrupt (*InterruptRoutine)(...);

typedef void (*WrapperFunc)();

#endif
