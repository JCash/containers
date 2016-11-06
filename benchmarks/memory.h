#pragma once

#include <stdlib.h>

void InitMemoryHooks();

void ResetMemoryStats();

void GetMemoryStats(size_t& num_allocs, size_t& alloc_size);
