#ifndef _SLEEPLST_H_
#define _SLEEPLST_H_

#include "pcb.h"
#include "types.h"

class SleepList {
public:
	SleepList() : first_(NULL), currentTime_(0) {}
	~SleepList();

	void add(PCB* pcb, Time timeToSleep);
	void wakeUp();

private:
	struct Node {
		PCB*  pcb;
		Time  wakeUpTime;
		Node* next;

		Node(PCB* pcb, Time wakeUpTime, Node* next = NULL)
			: pcb(pcb), wakeUpTime(wakeUpTime), next(next)
		{}
	};

	Node* first_;
	Time  currentTime_;
};

#endif
