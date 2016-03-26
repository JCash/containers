#include <map>
#include <iostream>
#include "report.h"

static void report_time(std::ostream& stream, float t, float multiplier)
{
	if( multiplier == 0.0f )
	{
		if( t < 0.000001f )
			stream << t * 1000000000.0 << " ns";
		else if( t < 0.001f )
			stream << t * 1000000.0 << " \u00b5s";
		else if( t < 0.1f )
			stream << t * 1000.0 << " ms";
		else
			stream << t << " s";
	}
	else
	{
		if( multiplier == 1000000000.0f )
			stream << t * multiplier << " ns";
		else if( multiplier == 1000000.0f )
			stream << t * multiplier << " \u00b5s";
		else if( multiplier == 1000.0f )
			stream << t * multiplier << " ms";
		else if( multiplier == 1.0f )
			stream << t * multiplier << " s";
		else
			stream << t * multiplier;
	}
}

static void Report(size_t reportformat,
						const char* title, const char* container,
						double timemin, double timemax, double timemedian, double timeavg,
						const SMemoryStats& memstats,
						size_t num_iterations, size_t num_elements, float multiplier)
{
	if( reportformat == 0 )
	{
		printf("%s\t%s\tused %lu bytes in %lu allocations\n", container, title, memstats.peak_alloc_size, memstats.peak_num_allocs);
				
		std::cout << std::fixed << std::setprecision(4);
		std::cout << container << "\t" << title << "\titerations: " << num_iterations;
		std::cout << "\tavg: "; 	report_time(std::cout, timeavg, multiplier);
		std::cout << "\tmedian: "; 	report_time(std::cout, timemedian, multiplier);
		std::cout << "\tmin: "; 	report_time(std::cout, timemin, multiplier);
		std::cout << "\tmax: "; 	report_time(std::cout, timemax, multiplier);
		std::cout << std::endl;
	}
	else
	{
		std::cout << "\t\"" << title << "\": {" << std::endl;
		std::cout << "\t\t\"container\": \"" << container << "\"," << std::endl;
		std::cout << "\t\t\"title\": \"" << title << "\"," << std::endl;
		std::cout << "\t\t\"iterations\": " << num_iterations << "," << std::endl;
		std::cout << "\t\t\"time_avg\": " << timeavg << "," << std::endl;
		std::cout << "\t\t\"time_mean\": " << timemedian << "," << std::endl;
		std::cout << "\t\t\"time_min\": " << timemin << "," << std::endl;
		std::cout << "\t\t\"time_max\": " << timemax << "" << std::endl;
		std::cout << "\t\t\"memory_peak_num\": " << memstats.peak_num_allocs << "" << std::endl;
		std::cout << "\t\t\"memory_peak_size\": " << memstats.peak_alloc_size << "" << std::endl;
		std::cout << "\t}, " << std::endl;
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
				test.memory,
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
