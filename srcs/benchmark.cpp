//
// Created by amyroshn on 06/07/22.
//

#include "../inc/ft_containers_test.hpp"

using namespace ft;

void vector_benchmark() {
	{
		vector<long> test;
		for (long l = -5000000; l < 5000000; l++)
			test.push_back(l);
		print_vector_size(test);
		test.insert(test.begin() + 333333, 100000, 42);
		print_vector_size(test);
		test.assign(5000000, 4242);
		print_vector_size(test);
		test.erase(test.begin() + 100000, test.begin() + 1000000);
		print_vector_size(test);
		test.clear();
		print_vector_size(test);
	}
	vector<long> test(1000000, 42);
	test.erase(test.begin() + 10000, test.begin() + 50000);
	test.erase(test.begin() + 100000, test.begin() + 200000);
	test.erase(test.begin() + 500000, test.begin() + 600000);
	print_vector_size(test);
	test.clear();
	print_vector_size(test);
	test.insert(test.begin(), 10000000, 42);
	print_vector_size(test);
	test.assign(666666, 99);
	print_vector_size(test);
	vector<long> test2;
	for (int i = -100000000; i < 100000000; i++)
		test2.push_back(i);
	test2.insert(test2.begin() + 10000000, test.begin(), test.end());
	print_vector_size(test2);
	test.assign(test2.begin(), test2.end());
	print_vector_size(test);
}

void stack_bench() {
	stack<long> a;
	for (long i = -100000000; i < 100000000; i++) {
		a.push(i);
	}
	type_print(a.empty());
	type_print(a.size());
	type_print(a.top());
	while (!a.empty())
		a.pop();
	type_print(a.empty());
	type_print(a.size());
}


void map_bench() {
	map<const int, int> m;
	for (int i = 1; i < 100000; i++) {
		m.insert(make_pair(i, i));
		if (i == 99999)
			m.size();
	}
	//print_map(m);
}