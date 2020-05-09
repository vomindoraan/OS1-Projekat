#ifndef _KERNEVT_H_
#define _KERNEVT_H_

#include "kernobj.h"
#include "kernsem.h"
#include "pcb.h"
#include "types.h"

class KernelEvt : public KernelObj {
public:
	KernelEvt(IVTNo ivtNo);
	~KernelEvt();

	void wait();
	void signal();

private:
	IVTNo     ivtNo_;
	PCB*      pcb_;
	KernelSem sem_;
};

#endif
