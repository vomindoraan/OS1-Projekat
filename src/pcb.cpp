#include "pcb.h"
#include "idle.h"
#include "locks.h"
#include <dos.h>

StackSize const PCB::MAX_STACK_SIZE = 0x1000; // 64KB
PCB* PCB::running = NULL;

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

void PCB::waitToComplete()
{
    LOCKED(
        /* Can't wait on itself nor on terminated threads nor on the idle thread */
        if (PCB::running != this && state() != PCB::TERMINATED && this != Idle::instance()) {
			cout << "blockkkkkkkkkkkkkkkkkkkkkk" << PCB::running << endl;
            PCB::running->state(PCB::BLOCKED);
            waiting_.pushBack(PCB::running);
			dispatch();
        }
    )
    // TODO: Maybe move dispatch out of LOCKED
}

void PCB::initializeStack(WrapperFunc wrapper)
{
    stack_ = new Word[stackCount_];

    stack_[stackCount_ - 1] = 0x0200;          // PSWI=1
    stack_[stackCount_ - 2] = FP_SEG(wrapper); // CS
    stack_[stackCount_ - 3] = FP_OFF(wrapper); // IP

    ss_ =       FP_SEG(stack_ + stackCount_ - 12);
    sp_ = bp_ = FP_OFF(stack_ + stackCount_ - 12);
}

void PCB::threadWrapper()
{
    PCB::running->thread_->run();

    LOCKED(
        PCB::running->state(PCB::TERMINATED);
        PCB::running->waiting_.rescheduleAll();
        dispatch();
    )
}
