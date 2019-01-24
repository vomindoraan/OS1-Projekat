#include "ivt.h"
#include "context.h"
#include "locks.h"
// #include "syscall.h"
#include "types.h"
#include <dos.h>
#include <stdlib.h>

InterruptRoutine oldTimerInterrupt = NULL;

void initIVT()
{
	HARD_LOCKED(
		oldTimerInterrupt = getvect(IVTNO_TIMER);
		setvect(IVTNO_TIMER,         Context::timerInterrupt);
		// setvect(IVTNO_SYSCALL_ENTER, syscallEnter);
		// setvect(IVTNO_SYSCALL_EXIT,  syscallExit);
	)
}

void restoreIVT()
{
	HARD_LOCKED(
		setvect(IVTNO_TIMER,         oldTimerInterrupt);
		// setvect(IVTNO_SYSCALL_ENTER, NULL);
		// setvect(IVTNO_SYSCALL_EXIT,  NULL);
	)
}
