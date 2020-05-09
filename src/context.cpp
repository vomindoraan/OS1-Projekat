#include "context.h"
#include "ivt.h"
#include "kernpcb.h"
#include "syscall.h"
#include "system.h"
#include <dos.h>

bool volatile Context::lockTimedOut_ = false;
bool volatile Context::requested_    = false;

static Register volatile tsp, tss, tbp;
static bool     volatile inSyscall;

void interrupt Context::timerInterrupt(...)
{
	bool unlimited = System::runningPCB->unlimitedDuration();
	Time& timeLeft = System::runningPCB->timeLeft_;

	if (!requested_) {
		oldTimerInterrupt();
		System::sleepList->wakeUp();
		tick();

		if (!unlimited && timeLeft > 0) {
			--timeLeft;
			if (timeLeft == 0 && lock) lockTimedOut_ = true;
		}
	} else if (lockTimedOut_) {
		lockTimedOut_ = false;
	}

	if (requested_ || (!unlimited && timeLeft == 0 && !lock)) {
		if (!inSyscall) {
			asm {
				mov tss, ss;
				mov tsp, sp;
				mov tbp, bp;
			}
			System::runningPCB->ss_ = tss;
			System::runningPCB->sp_ = tsp;
			System::runningPCB->bp_ = tbp;
			System::runningPCB->savedLock_ = lock;
		}

		if (System::runningPCB->state() == PCB::RUNNING
			&& System::runningPCB != System::idlePCB)
		{
			System::runningPCB->state(PCB::READY);
			Scheduler::put(System::runningPCB);
		}

		System::runningPCB = Scheduler::get();
		if (!System::runningPCB) System::runningPCB = System::idlePCB;
		System::runningPCB->state(PCB::RUNNING);
		System::runningPCB->timeLeft_ = System::runningPCB->timeSlice_;

		if (!inSyscall) {
			tss = System::runningPCB->ss_;
			tsp = System::runningPCB->sp_;
			tbp = System::runningPCB->bp_;
			asm {
				mov ss, tss;
				mov sp, tsp;
				mov bp, tbp;
			}
			lock = System::runningPCB->savedLock_;
		}

		requested_ = false;
	}
}

void interrupt Context::syscallEnter(...)
{
	Register paramsSeg, paramsOff;
	asm {
		mov paramsSeg, ax;
		mov paramsOff, bx;
	}
	System::kernelPCB->syscallParams = (Syscall*) MK_FP(paramsSeg, paramsOff);

	asm {
		mov tss, ss;
		mov tsp, sp;
		mov tbp, bp;
	}
	System::runningPCB->ss_ = tss;
	System::runningPCB->sp_ = tsp;
	System::runningPCB->bp_ = tbp;
	System::runningPCB->savedLock_ = lock;

	System::kernelPCB->initializeStack(KernelPCB::syscallWrapper, false);

	lock = 1; // Prevent preemption in kernel thread
	inSyscall = true;
	tss = System::kernelPCB->ss_;
	tsp = System::kernelPCB->sp_;
	tbp = System::kernelPCB->bp_;
	asm {
		mov ss, tss;
		mov sp, tsp;
		mov bp, tbp;
	}
}

void interrupt Context::syscallExit(...)
{
	System::runningPCB->timeLeft_ = System::runningPCB->timeSlice_;

	inSyscall = false;
	tss = System::runningPCB->ss_;
	tsp = System::runningPCB->sp_;
	tbp = System::runningPCB->bp_;
	asm {
		mov ss, tss;
		mov sp, tsp;
		mov bp, tbp;
	}
	lock = System::runningPCB->savedLock_;
}
