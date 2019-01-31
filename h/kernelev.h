#ifndef _KERNELEV_H_
#define _KERNELEV_H_

#include "kernobj.h"
#include "kernsem.h"
#include "pcb.h"
#include "types.h"

class KernelEv : public KernelObj {
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
