#include "kernelev.h"
#include "ivt.h"

KernelEv::KernelEv(IVTNo ivtNo)
	: ivtNo_(ivtNo), pcb_(PCB::runningPCB), sem_(0)
{
	IVTEntry::get(ivtNo_)->setEvent(this);
}

KernelEv::~KernelEv()
{
	IVTEntry::get(ivtNo_)->restore();
}

void KernelEv::wait()
{
	LOCKED(
		if (PCB::runningPCB == pcb_) sem_.wait(1);
	)
}

void KernelEv::signal()
{
	LOCKED(
		sem_.signal();
	)
}
