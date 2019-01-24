#include "locks.h"
// #include "ivt.h"
#include <iostream.h>

int userMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	HARD_LOCKED(cout << "Start" << endl);

	// initIVT();
	// restoreIVT();

	HARD_LOCKED(cout << "Finish" << endl);

	return 0;
}
