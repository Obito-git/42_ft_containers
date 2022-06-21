//
// Created by amyroshn on 19/06/22.
//
#include "ft_containers_test.hpp"

using namespace ft;



void random_access_iterator_test() {
	vector<int> a(5);
	for (int i = 0; i < 10; i++)
		a.push_back(i);
	vector<int>::iterator beg = a.begin();
	vector<int>::const_iterator const_beg = a.begin();
	vector<int>::iterator end = a.end() - 1;
	vector<int>::const_iterator const_end = a.end() - 1;

	//equality operators const vs non const:
	test_print(beg == const_beg);
	test_print(beg != const_beg);
	test_print(beg > const_beg);
	test_print(beg < const_beg);
	test_print(beg >= const_beg);
	test_print(beg <= const_beg);


	test_print(end == const_end);
	test_print(end != const_end);
	test_print(end > const_end);
	test_print(end < const_end);
	test_print(end >= const_end);
	test_print(end <= const_end);


	test_print(beg == const_end);
	test_print(beg != const_end);
	test_print(beg > const_end);
	test_print(beg < const_end);
	test_print(beg >= const_end);
	test_print(beg <= const_end);


	test_print(end == const_beg);
	test_print(end != const_beg);
	test_print(end > const_beg);
	test_print(end < const_beg);
	test_print(end >= const_beg);
	test_print(end <= const_beg);

	//equality operator non const vs non const
	test_print(beg == end);
	test_print(beg != end);
	test_print(beg > end);
	test_print(beg < end);
	test_print(beg >= end);
	test_print(beg <= end);


	test_print(end == beg);
	test_print(end != beg);
	test_print(end > beg);
	test_print(end < beg);
	test_print(end >= beg);
	test_print(end <= beg);



	//addition / subtraction
	test_print(*(end - 5));
	test_print(*beg++);
	test_print(*const_beg++);
	test_print(*beg);
	*(beg -1) = 42;
	test_print(*const_beg);
	test_print(*--beg);
	test_print(*--const_beg);
	test_print(*end);
	test_print(*(const_beg + 1));
	test_print(*(1 + const_beg + 1));
	test_print(*(1 + const_beg));
	test_print(end - const_beg);
	test_print(const_end - const_beg - 3);
	test_print(const_end - const_beg + 32);
	*(beg + 4) = 999;
	beg += 4;
	test_print(*beg);
	beg[const_end - const_beg] = 222;
	test_print(beg[const_end - const_beg]);

}