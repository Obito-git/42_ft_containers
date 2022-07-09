#include <string>
#include <stack>
#include "../inc/ft_containers_test.hpp"
#include <string>
#include <map>
#include <iterator>
#include <sys/time.h>
using namespace ft;

int main()
{
	long seconds;
	long microseconds;
	double elapsed;
	struct timeval begin, end;
	gettimeofday(&begin, 0);
	/******************* VECTOR ************************/
	/*
	random_access_iterator_test();
	constructor_destructor_test();
	capacity_test();
	access_test();
	modifiers_test();
	vector_benchmark();

	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	std::cout << "vector " << elapsed << " seconds" << std::endl;
	 */
	/******************* STACK ************************/
	/*
	gettimeofday(&begin, 0);

	stack_test();
	stack_bench();

	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	std::cout << "stack " << elapsed << " seconds" << std::endl;
	 */
	/******************* MAP ************************/

	gettimeofday(&begin, 0);

	//map_iter_cap_access();
	map_bench();

	map<const int, int> a;

	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	std::cout << "map " << elapsed << " seconds" << std::endl;

	return 0;
}
