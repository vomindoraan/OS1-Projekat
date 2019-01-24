#include "sleeplst.h"
#include "locks.h"

SleepList::~SleepList()
{
	LOCKED(
		while (first_) {
			Node* temp = first_;
			first_ = first_->next;
			delete temp;
		}
	)
}

void SleepList::add(PCB* pcb, Time timeToSleep)
{
	LOCKED(
		Node* newNode = new Node(pcb, currentTime_ + timeToSleep);

		Node* curr = first_;
		Node* prev = NULL;
		while (curr && curr->wakeUpTime < newNode->wakeUpTime) {
			prev = curr;
			curr = curr->next;
		}

		(prev ? prev->next : first_) = newNode;
		newNode->next = curr;
	)
}

void SleepList::wakeUp()
{
	LOCKED(
		if (first_) {
			++currentTime_;

			while (first_ && first_->wakeUpTime <= currentTime_) {
				Node* temp = first_;
				first_->pcb->state(PCB::READY);
				Scheduler::put(first_->pcb);
				first_ = first_->next;
				delete temp;
			}
		} else {
			currentTime_ = 0;
		}
	)
}
