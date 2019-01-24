#include "ivt.h"
#include "context.h"
#include "locks.h"
#include "types.h"
#include <dos.h>
#include <stdlib.h>

InterruptRoutine oldTimerInterrupt = NULL;

void initIVT()
{
	HARD_LOCKED(
		oldTimerInterrupt = getvect(IVTNO_TIMER);
		setvect(IVTNO_TIMER, Context::timerInterrupt);
	)
}

void restoreIVT()
{
	HARD_LOCKED(
		setvect(IVTNO_TIMER, oldTimerInterrupt);
	)
}
