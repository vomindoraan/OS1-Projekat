#include "kernevt.h"
#include "ivt.h"
#include "system.h"

KernelEvt::KernelEvt(IVTNo ivtNo)
	: KernelObj(), ivtNo_(ivtNo), pcb_(System::runningPCB), sem_(0)
{
	IVTEntry::get(ivtNo_)->event = this;
}

KernelEvt::~KernelEvt()
{
	IVTEntry::get(ivtNo_)->event = NULL;
}

void KernelEvt::wait()
{
	LOCKED(
		if (System::runningPCB == pcb_) sem_.wait(1);
	)
}

void KernelEvt::signal()
{
	LOCKED(
		sem_.signal();
	)
}
