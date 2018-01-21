#include <map>
#include <iostream>
#include "report.h"

#if defined(__APPLE__)
    #include "TargetConditionals.h"
    #if defined(TARGET_OS_IPHONE)
		extern void Printf(const char*, ...);
	#endif
#else
	#define Printf printf
#endif

static float convert_time(float t, float multiplier)
{
	if( multiplier == 0.0f )
	{
		if( t < 0.000001f )
			t *= 1000000000.0;
		else if( t < 0.001f )
			t *= 1000000.0;
		else if( t < 0.1f )
			t *= 1000.0;
	}
	else
	{
		t *= multiplier;
	}
	return t;
}

static const char* get_unit(float t, float multiplier)
{
	if( multiplier == 0.0f )
	{
		if( t < 0.000001f )
			return "ns";
		else if( t < 0.001f )
			return "\u00b5s";
		else if( t < 0.1f )
			return "ms";
		else
			return "s";
	}
	else
	{
		t *= multiplier;
		if( multiplier == 1000000000.0f )
			return "ns";
		else if( multiplier == 1000000.0f )
			return "\u00b5s";
		else if( multiplier == 1000.0f )
			return "ms";
		else if( multiplier == 1.0f )
			return "s";
	}
	return "";
}

static void Report(size_t reportformat,
						const char* title, const char* container,
						double timemin, double timemax, double timemedian, double timeavg,
						size_t memory_allocations, size_t memory_size,
						size_t num_iterations, size_t num_elements, float multiplier)
{
	if( reportformat == 0 )
	{
		Printf("%s\t%s\tused %zu bytes in %zu allocations\n", container, title, memory_size, memory_allocations);
		Printf("%s\t%s\titerations: %zu\tavg: %f %s\tmedian: %f %s\tmin: %f %s\tmax: %f %s", container, title, num_iterations,
				convert_time(timeavg, multiplier), get_unit(timeavg, multiplier),
				convert_time(timemedian, multiplier), get_unit(timemedian, multiplier),
				convert_time(timemin, multiplier), get_unit(timemin, multiplier),
				convert_time(timemax, multiplier), get_unit(timemax, multiplier));
		fflush(stdout);
		fflush(stderr);
/*
		std::cout << std::fixed << std::setprecision(4);
		std::cout << container << "\t" << title << "\titerations: " << num_iterations;
		std::cout << "\tavg: "; 	report_time(std::cout, timeavg, multiplier);
		std::cout << "\tmedian: "; 	report_time(std::cout, timemedian, multiplier);
		std::cout << "\tmin: "; 	report_time(std::cout, timemin, multiplier);
		std::cout << "\tmax: "; 	report_time(std::cout, timemax, multiplier);
		std::cout << std::endl;
		*/
	}
	//else
	{
		// std::cout << "\t\"" << title << "\": {" << std::endl;
		// std::cout << "\t\t\"container\": \"" << container << "\"," << std::endl;
		// std::cout << "\t\t\"title\": \"" << title << "\"," << std::endl;
		// std::cout << "\t\t\"iterations\": " << num_iterations << "," << std::endl;
		// std::cout << "\t\t\"time_avg\": " << timeavg << "," << std::endl;
		// std::cout << "\t\t\"time_mean\": " << timemedian << "," << std::endl;
		// std::cout << "\t\t\"time_min\": " << timemin << "," << std::endl;
		// std::cout << "\t\t\"time_max\": " << timemax << "" << std::endl;
		// std::cout << "\t\t\"memory_peak_num\": " << memory_allocations << "" << std::endl;
		// std::cout << "\t\t\"memory_peak_size\": " << memory_size << "" << std::endl;
		// std::cout << "\t}, " << std::endl;
	}
}

void report(int reportformat, const report_t& results, int verbose)
{
	for( size_t i = 0; i < results.tests.size(); ++i )
	{
		const STestReport& test = results.tests[i];
		Report(reportformat,
				test.testname.c_str(), results.containername.c_str(),
				test.timemin, test.timemax, test.timemedian, test.timeavg,
				test.memory_allocations, test.memory_size,
				test.iterations, test.elements, 1000.0f);
	}

	if( reportformat == 0 )
	{
	}
	else
	{
		std::cout << "\"container\": \"" << results.containername << "\"" << std::endl;
		std::cout << "}" << std::endl;
	}
}
