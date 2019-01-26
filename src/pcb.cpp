#include "pcb.h"
#include "idle.h"
#include "locks.h"
#include "sleeplst.h"
#include <dos.h>

Word      const PCB::PSW_INIT_VALUE = 0x0200; // I=1
StackSize const PCB::MAX_STACK_SIZE = 0x1000; // 64KB

PCB* PCB::runningPCB = NULL;

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* thread)
	: thread_(thread), stack_(NULL)
	, timeSlice_(timeSlice), timeLeft_(timeSlice), state_(NEW), savedLock_(0)
{
	if (stackSize > MAX_STACK_SIZE) stackSize = MAX_STACK_SIZE;
	stackCount_ = stackSize / sizeof(Word);

	if (thread) initializeStack(PCB::threadWrapper);
}

PCB::~PCB()
{
	waiting_.rescheduleAll();
	if (stack_) delete[] stack_;
}

void PCB::initializeStack(WrapperFunc wrapper)
{
	stack_ = new Word[stackCount_];

	stack_[stackCount_ - 1] = PSW_INIT_VALUE;  // PSW
	stack_[stackCount_ - 2] = FP_SEG(wrapper); // CS
	stack_[stackCount_ - 3] = FP_OFF(wrapper); // IP

	ss_ =       FP_SEG(stack_ + stackCount_ - 12);
	sp_ = bp_ = FP_OFF(stack_ + stackCount_ - 12);
}

void PCB::waitToComplete()
{
	LOCKED(
		/* Can't wait on itself nor on terminated threads nor on the idle thread */
		if (PCB::runningPCB != this && state() != PCB::TERMINATED && this != idlePCB) {
			PCB::runningPCB->state(PCB::BLOCKED);
			waiting_.pushBack(PCB::runningPCB);
			dispatch();
		}
	)
}

void PCB::sleep(Time timeToSleep)
{
	if (!timeToSleep) return;
	LOCKED(
		PCB:runningPCB->state(PCB::BLOCKED);
		sleepList->add(PCB::runningPCB, timeToSleep);
		dispatch();
	)
}

void PCB::threadWrapper()
{
	PCB::runningPCB->thread_->run();

	LOCKED(
		PCB::runningPCB->state(PCB::TERMINATED);
		PCB::runningPCB->waiting_.rescheduleAll();
		dispatch();
	)
}
