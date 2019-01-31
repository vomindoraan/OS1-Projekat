#include "syscall.h"
#include <stdarg.h>

Syscall::Syscall(size_t size, Operation op, ...)
	: size(size), params(new Word[size])
{
	va_list args;
	va_start(args, op);

	params[0] = op;
	for (size_t i = 1; i < size; ++i) {
		params[i] = va_arg(args, Word);
	}

	va_end(args);
}
