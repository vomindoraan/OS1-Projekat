#include "event.h"
#include "kernelev.h"

Event::Event(IVTNo ivtNo)
{
	LOCKED(
		myImpl = new KernelEv(ivtNo)
	);
}

Event::~Event()
{
	LOCKED(
		delete myImpl;
	)
}

void Event::wait()
{
	LOCKED(
		myImpl->wait();
	)
}

void Event::signal()
{
	LOCKED(
		myImpl->signal();
	)
}
