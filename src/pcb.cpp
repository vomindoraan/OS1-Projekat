#include "pcb.h"
#include "locks.h"

StackSize const PCB::MAX_STACK_SIZE = 0x1000; // 64KB

PCB::PCB(Thread* thread, StackSize stackSize, Time timeSlice)
    : thread_(thread), timeSlice_(timeSlice), timeLeft_(timeSlice), state_(NEW), savedLock_(0)
{
    if (stackSize > MAX_STACK_SIZE) stackSize = MAX_STACK_SIZE;
    stackCount_ = stackSize / sizeof(Word);
    stack_ = new Word[stackCount_];
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
}
