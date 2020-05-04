#include "ivt.h"
#include "context.h"
#include "locks.h"
#include "types.h"
#include <dos.h>

InterruptRoutine oldTimerInterrupt = NULL;

void initializeInterrupts()
{
	HARD_LOCKED(
		oldTimerInterrupt = getvect(IVTNO_TIMER);
		setvect(IVTNO_TIMER,         Context::timerInterrupt);
		setvect(IVTNO_SYSCALL_ENTER, Context::syscallEnter);
		setvect(IVTNO_SYSCALL_EXIT,  Context::syscallExit);
	)
}

void restoreInterrupts()
{
	HARD_LOCKED(
		setvect(IVTNO_TIMER,         oldTimerInterrupt);
		setvect(IVTNO_SYSCALL_ENTER, NULL);
		setvect(IVTNO_SYSCALL_EXIT,  NULL);
	)
}

IVTEntry* IVTEntry::table_[256] = {0};

IVTEntry::IVTEntry(IVTNo ivtNo, InterruptRoutine newInterrupt)
	: ivtNo_(ivtNo), newInterrupt(newInterrupt), event_(NULL)
{
	table_[ivtNo] = this;
	HARD_LOCKED(
		oldInterrupt = getvect(ivtNo_);
		setvect(ivtNo_, newInterrupt);
	)
}

IVTEntry::~IVTEntry()
{
	HARD_LOCKED(
		setvect(ivtNo_, oldInterrupt);
	)
	table_[ivtNo] = NULL;
}
