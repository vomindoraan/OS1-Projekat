#ifndef _KERNOBJ_H_
#define _KERNOBJ_H_

#include "types.h"

class KernelObj {
public:
	KernelObj() : id_(uniqueId_++) {}
	KernelObj(KernelObj const& o) : id_(uniqueId_++) {}
	KernelObj& operator=(KernelObj const& o) { id_ = uniqueId_++; return *this; }

	ID id() const { return id_; }

	friend class System;

private:
	static ID uniqueId_;
	ID id_;
};

#endif
