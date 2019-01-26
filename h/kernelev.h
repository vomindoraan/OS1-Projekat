#ifndef _KERNELEV_H_
#define _KERNELEV_H_

#include "kernsem.h"
#include "pcb.h"
#include "types.h"

class KernelEv {
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();

	void wait();
	void signal();

private:
	IVTNo     ivtNo_;
	PCB*      pcb_;
	KernelSem sem_;
};

#endif
