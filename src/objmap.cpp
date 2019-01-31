#include "objmap.h"

ObjMap::ObjMap(ID initSize)
	: size_(initSize)
{
	LOCKED(
		contents_ = new KernelObj*[size_];
	)
	for (ID i = 0; i < size_; i++) contents_[i] = NULL;
}

ObjMap::~ObjMap()
{
	LOCKED(
		delete[] contents_;
	)
}

KernelObj* ObjMap::get(ID id) const
{
	KernelObj* ret = NULL;
	LOCKED(
		if (id >= size_) return NULL;
		ret = contents_[id];
	)
	return ret;
}

void ObjMap::set(ID id, KernelObj* obj)
{
	LOCKED(
		if (id > size_) {
			ID newSize = (id > size_*2) ? id+1 : size_*2;
			KernelObj** newContents = new KernelObj*[newSize];
			for (ID i = 0; i < newSize; i++) {
				newContents[i] = (i < size_) ? contents_[i] : NULL;
			}
			delete[] contents_;
			size_ = newSize;
			contents_ = newContents;
		}
		contents_[id] = obj;
	)
}

KernelObj* ObjMap::remove(ID id) {
	KernelObj* ret = NULL;
	LOCKED(
		if (id < size_) {
			ret = contents_[id];
			contents_[id] = NULL;
		}
	)
	return ret;
}
