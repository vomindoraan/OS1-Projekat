#ifndef _OBJMAP_H_
#define _OBJMAP_H_

#include "types.h"
#include "kernobj.h"
#include "locks.h"

class ObjMap {
public:
	ObjMap(ID initSize = 10);
	~ObjMap();

	KernelObj* get(ID id) const;
	void       set(ID id, KernelObj* obj);
	KernelObj* remove(ID id);

private:
	ID          size_;
	KernelObj** contents_;
};

#endif
