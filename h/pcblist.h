#ifndef _PCBLIST_H_
#define _PCBLIST_H_

#include "types.h"

class PCB;

class PCBList {
public:
	PCBList() : front_(NULL), back_(NULL) {}
	~PCBList();

	PCB* front() const { return front_->pcb; }
	PCB* back()  const { return back_->pcb; }
	bool empty() const { return !front_; }

	void pushBack(PCB* pcb);
	PCB* popFront();

	void rescheduleAll();

private:
	struct Node {
		PCB*  pcb;
		Node* next;

		Node(PCB* pcb, Node* next = NULL) : pcb(pcb), next(next) {}
	};

	Node* front_;
	Node* back_;
};

#endif
