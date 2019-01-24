#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "types.h"

void tick();

class Context {
public:
	static void interrupt timerInterrupt(...);

	static bool lockTimedOut()  { return lockTimedOut_; }
	static void requestChange() { requested_ = true; }

private:
	Context() {}
	~Context() {}

	static bool volatile lockTimedOut_;
	static bool volatile requested_;
};

#endif
