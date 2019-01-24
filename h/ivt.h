#ifndef _IVT_H_
#define _IVT_H_

#include "types.h"

enum IVTNumbers {
	IVTNO_TIMER         = 0x8,
	IVTNO_SYSCALL_ENTER = 0x60,
	IVTNO_SYSCALL_EXIT  = 0x61,
};

extern InterruptRoutine oldTimerInterrupt;

void initIVT();
void restoreIVT();

#endif
