#include "locks.h"
#include "system.h"
#include <iostream.h>

int userMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	cout << "Start" << endl;
	System::start();

	HARD_LOCKED(
		cout << "User" << endl;
	);
	int ret = userMain(argc, argv);

	System::finish();
	cout << "Finish" << endl;

	return ret;
}
