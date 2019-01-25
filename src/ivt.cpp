#include "ivt.h"
#include "context.h"
#include "locks.h"
#include "types.h"
#include <dos.h>
#include <stdlib.h>

InterruptRoutine oldTimerInterrupt = NULL;

void initializeInterrupts()
{
	HARD_LOCKED(
		oldTimerInterrupt = getvect(IVTNO_TIMER);
		setvect(IVTNO_TIMER, Context::timerInterrupt);
	)
}

void restoreInterrupts()
{
	HARD_LOCKED(
		setvect(IVTNO_TIMER, oldTimerInterrupt);
	)
}

IVTEntry* IVTEntry::table_[256] = {0};

IVTEntry::IVTEntry(IVTNo ivtNo, InterruptRoutine newInterrupt)
	: ivtNo_(ivtNo), newInterrupt(newInterrupt), event_(NULL)
{
	table_[ivtNo] = this;
}

void IVTEntry::setEvent(KernelEv* event)
{
	event_ = event;
	HARD_LOCKED(
		oldInterrupt = getvect(ivtNo_);
		setvect(ivtNo_, newInterrupt);
	)
}

void IVTEntry::restore()
{
	event_ = NULL;
	HARD_LOCKED(
		setvect(ivtNo_, oldInterrupt);
	)
}
