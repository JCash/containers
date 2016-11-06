#pragma once

#include <map>
#include <string>
#include <vector>
#include "timeit.h"

struct STestReport
{
	std::string testname;
	size_t	iterations;
	size_t	elements;
	double	timemin;
	double	timemax;
	double	timemedian;
	double	timeavg;
	
    size_t  memory_size;
    size_t  memory_allocations;
};

struct SReport
{
	std::string containername;
	std::vector<STestReport> tests;
};

typedef SReport report_t;

void report(int reportformat, const report_t& results, int verbose);
