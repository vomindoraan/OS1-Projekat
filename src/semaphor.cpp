#include "semaphor.h"
#include "kernsem.h"

Semaphore::Semaphore(int init)
{
	myImpl = new KernelSem(init);
}

Semaphore::~Semaphore()
{
	delete myImpl;
}

int Semaphore::wait(int toBlock)
{
	return myImpl->wait(toBlock);
}

void Semaphore::signal()
{
	myImpl->signal();
}

int Semaphore::val() const
{
	return myImpl->val();
}
