#include "kernsem.h"
#include "locks.h"
#include "pcb.h"
#include "schedule.h"

int KernelSem::wait(int toBlock)
{
    LOCKED(
        if (toBlock) {
            if (--val_ < 0) {
                block();
                return 1;
            }
            return 0;
        }

        if (val_ <= 0) return -1;
        --val_;
        return 0;
    )
}

void KernelSem::signal()
{
    LOCKED(
        if (val_++ < 0) deblock();
    )
}

void KernelSem::block()
{
    LOCKED(
        PCB::running->state(PCB::BLOCKED);
        blocked_.pushBack(PCB::running);
        dispatch();
    )
}

void KernelSem::deblock()
{
    LOCKED(

    )
}
