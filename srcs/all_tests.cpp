//
// Created by amyroshn on 09/07/22.
//

#include "../inc/ft_containers_test.hpp"

double print_used_time(struct timeval& begin) {
	long seconds;
	long microseconds;
	double elapsed;
	struct timeval end;
	gettimeofday(&end, 0);
	seconds = end.tv_sec - begin.tv_sec;
	microseconds = end.tv_usec - begin.tv_usec;
	elapsed = seconds + microseconds*1e-6;
	return elapsed;
}

double run_vector_tests(bool run_benchmark) {
	struct timeval begin;
	gettimeofday(&begin, 0);
	{
		random_access_iterator_test();
		constructor_destructor_test();
		capacity_test();
		access_test();
		modifiers_test();
	}
	if (run_benchmark)
		vector_benchmark();
	return print_used_time(begin);
}

double run_stack_tests(bool run_benchmark) {
	struct timeval begin;
	gettimeofday(&begin, 0);
	stack_test();
	if (run_benchmark)
		stack_bench();
	return print_used_time(begin);
}


double  run_map_tests(bool run_benchmark) {
	struct timeval begin;
	gettimeofday(&begin, 0);
	map_iter();
	map_access();
	map_constructors();
	map_leaks();
	map_modifiers_tests();
	map_operations();
	if (run_benchmark)
		map_bench();
	return print_used_time(begin);
}


double  run_set_tests(bool run_benchmark) {
	struct timeval begin;
	gettimeofday(&begin, 0);
	set_iter();
	set_constructors();
	set_modifiers_tests();
	set_operations();
	if (run_benchmark)
		set_bench();
	return print_used_time(begin);
}
