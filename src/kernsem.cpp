#include "kernsem.h"
#include "locks.h"
#include "pcb.h"
#include "schedule.h"

int KernelSem::wait(int toBlock)
{
    int ret = 0;
    LOCKED(
        if (toBlock) {
            if (--val_ < 0) {
                block();
                ret = 1;
            }
        } else if (val_ <= 0) {
            ret = -1;
        } else {
            --val_;
        }
    )
    return ret;
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
				static int i = 0;
		HARD_LOCKED(
			if (i < 20) {
			cout << "BLOCK   " << PCB::running << " " << PCB::running->savedLock_ << " " << PCB::running->state() << endl;
			i++;
			}
		);
        PCB::running->state(PCB::BLOCKED);
        blocked_.pushBack(PCB::running);
        dispatch();
    )
}

void KernelSem::deblock()
{
    LOCKED(
						static int i = 0;
		HARD_LOCKED(
			if (i < 20) {
			cout << "UNBLOCK " << PCB::running << " " << PCB::running->savedLock_ << " " << PCB::running->state() << endl;
			i++;
			}
		);
        if (!blocked_.empty()) {
            PCB* pcb = blocked_.popFront();
            pcb->state(PCB::READY);
            Scheduler::put(pcb);
        }
    )
}
