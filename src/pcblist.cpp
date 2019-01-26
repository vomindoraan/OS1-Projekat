#include "pcblist.h"
#include "locks.h"
#include "pcb.h"
#include "schedule.h"

PCBList::~PCBList()
{
	LOCKED(
		while (popFront());
	)
}

void PCBList::pushBack(PCB* pcb)
{
	LOCKED(
		Node* node = new Node(pcb);
		if (!front_) {
			front_ = node;
		} else {
			back_->next = node;
		}
		back_ = node;
	)
}

PCB* PCBList::popFront()
{
	LOCKED(
		PCB* ret = NULL;
		if (front_) {
			ret = front_->pcb;
			Node* temp = front_;
			front_ = front_->next;
			if (!front_) back_ = NULL;
			delete temp;
		}
	)
	return ret;
}

void PCBList::rescheduleAll()
{
	LOCKED(
		for (PCB* pcb; pcb = popFront(); pcb->reschedule());
	)
}
