#pragma once

#include "allocator.h"

template<typename SetupFunc, typename Func, typename... FuncArgs>
void CalcMemory(SMemoryStats& out, SetupFunc setupfunc, Func func, FuncArgs&... args)
{
	setupfunc(args...);

	memset(&out, 0, sizeof(out));
	allocator_base::reset();

	func(args...);

	out = allocator_base::stats;
}

