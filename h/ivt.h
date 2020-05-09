#ifndef _IVT_H_
#define _IVT_H_

#include "kernelev.h"
#include "types.h"

enum IVTNumbers {
	IVTNO_TIMER         = 0x8,
	IVTNO_SYSCALL_ENTER = 0x60,
	IVTNO_SYSCALL_EXIT  = 0x61,
};

extern InterruptRoutine oldTimerInterrupt;

void initializeInterrupts();
void restoreInterrupts();

class IVTEntry {
public:
	static IVTEntry* get(IVTNo ivtNo) { return table_[ivtNo]; }

	IVTEntry(IVTNo ivtNo, InterruptRoutine newInterrupt);
	~IVTEntry();

	void signal() { if (event_) event_->signal(); }

	InterruptRoutine oldInterrupt;
	InterruptRoutine newInterrupt;

	friend class KernelEv;

private:
	static IVTEntry* table_[];

	IVTNo     ivtNo_;
	KernelEv* event_;
};

#define PREPAREENTRY(ivtNo, callOld)                    \
extern IVTEntry ivtEntry##ivtNo;                        \
                                                        \
void interrupt eventInterrupt##ivtNo(...) {             \
    ivtEntry##ivtNo.signal();                           \
    if (callOld) ivtEntry##ivtNo.oldInterrupt();        \
    dispatch();                                         \
}                                                       \
                                                        \
IVTEntry ivtEntry##ivtNo(ivtNo, eventInterrupt##ivtNo);

#endif
