#include "pcb.h"
#include "locks.h"
#include <dos.h>

StackSize const PCB::MAX_STACK_SIZE = 0x1000; // 64KB

PCB::PCB(Thread* thread, StackSize stackSize, Time timeSlice)
    : thread_(thread), timeSlice_(timeSlice), timeLeft_(timeSlice), state_(NEW), savedLock_(0)
{
    if (stackSize > MAX_STACK_SIZE) stackSize = MAX_STACK_SIZE;
    stackCount_ = stackSize / sizeof(Word);
    stack_ = new Word[stackCount_];

    stack_[stackCount_ -  1] = 0x0200;               // PSWI=1
    stack_[stackCount_ -  2] = FP_SEG(PCB::wrapper); // CS
    stack_[stackCount_ -  3] = FP_OFF(PCB::wrapper); // IP

    ss_ =       FP_SEG(stack_ + stackCount_ - 12);
    sp_ = bp_ = FP_OFF(stack_ + stackCount_ - 12);
}

PCB::~PCB()
{
    waiting_.rescheduleAll();
    delete[] stack_;
}

void PCB::waitToComplete()
{
    LOCKED(
        if (PCB::running != this && state() != PCB::TERMINATED && thread() != /* TODO */) {
            PCB::running->state(PCB::BLOCKED);
            waiting_.pushBack(PCB::running);
            dispatch();
        }
    )
}

void PCB::wrapper()
{
    PCB::running->thread_->run();

    LOCKED(
        PCB::running->state(PCB::TERMINATED);
        PCB::running->waiting_.rescheduleAll();
        dispatch();
    )
}
