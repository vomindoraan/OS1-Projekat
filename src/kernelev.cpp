#include "kernelev.h"
#include "ivt.h"
#include "system.h"

KernelEv::KernelEv(IVTNo ivtNo)
	: KernelObj(), ivtNo_(ivtNo), pcb_(System::runningPCB), sem_(0)
{
	IVTEntry::get(ivtNo_)->bind(this);
}

KernelEv::~KernelEv()
{
	IVTEntry::get(ivtNo_)->restore();
}

void KernelEv::wait()
{
	LOCKED(
		if (System::runningPCB == pcb_) sem_.wait(1);
	)
}

void KernelEv::signal()
{
	LOCKED(
		sem_.signal();
	)
}
