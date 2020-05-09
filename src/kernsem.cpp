#include "kernsem.h"
#include "locks.h"
#include "schedule.h"
#include "system.h"

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
		System::runningPCB->state(PCB::BLOCKED);
		blocked_.pushBack(System::runningPCB);
		dispatch();
	)
}

void KernelSem::deblock()
{
	LOCKED(
		if (!blocked_.empty()) {
			blocked_.popFront()->reschedule();
		}
	)
}
