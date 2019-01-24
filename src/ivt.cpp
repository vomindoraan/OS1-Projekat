#include "ivt.h"
#include "context.h"
// #include "syscall.h"
#include "types.h"
#include <dos.h>
#include <stdlib.h>

InterruptRoutine oldTimer = NULL;

void initIVT()
{
	oldTimer = getvect(IVTNO_TIMER);
	setvect(IVTNO_TIMER,         contextTimer);
	setvect(IVTNO_SYSCALL_ENTER, syscallEnter);
	setvect(IVTNO_SYSCALL_EXIT,  syscallExit);
}

void restoreIVT()
{
	setvect(IVTNO_TIMER,         oldTimer);
	setvect(IVTNO_SYSCALL_ENTER, NULL);
	setvect(IVTNO_SYSCALL_EXIT,  NULL);
}
