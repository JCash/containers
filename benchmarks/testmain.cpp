
#include <string.h>
#include <iostream>
#include "defines.h"
#include "report.h"

extern void test(size_t reportformat, size_t num_iterations, size_t num_elements, report_t& results, int verbose);

int main(int argc, char **argv)
{
	size_t num_elements = 5000;
	size_t num_iterations = 20;
	size_t reportformat = 0; // 0 = stdout, 1 = json
	int verbose = 0;
	if( argc > 1 )
		num_elements = atoi(argv[1]);
	if( argc > 2 )
		num_iterations = atoi(argv[2]);
	if( argc > 3 )
		reportformat = atoi(argv[3]);

	/*
	for( int i = 1; i < argc; ++i )
	{
		if(strcmp("-v", argv[i]) == 0 || strcmp("--verbose", argv[i]) == 0)
			verbose = 1;
		else if(strcmp("-n", argv[i]) == 0)
			num_elements = 1;
	}
	*/
	verbose = 0;

	report_t results;
	test(reportformat, num_iterations, num_elements, results, verbose);
	report(reportformat, results, verbose);
	return 0;
}
