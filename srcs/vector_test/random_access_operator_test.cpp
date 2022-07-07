//
// Created by amyroshn on 19/06/22.
//
#include "../../inc/ft_containers_test.hpp"

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
	type_print(beg == const_beg);
	type_print(beg != const_beg);
	type_print(beg > const_beg);
	type_print(beg < const_beg);
	type_print(beg >= const_beg);
	type_print(beg <= const_beg);


	type_print(end == const_end);
	type_print(end != const_end);
	type_print(end > const_end);
	type_print(end < const_end);
	type_print(end >= const_end);
	type_print(end <= const_end);


	type_print(beg == const_end);
	type_print(beg != const_end);
	type_print(beg > const_end);
	type_print(beg < const_end);
	type_print(beg >= const_end);
	type_print(beg <= const_end);


	type_print(end == const_beg);
	type_print(end != const_beg);
	type_print(end > const_beg);
	type_print(end < const_beg);
	type_print(end >= const_beg);
	type_print(end <= const_beg);

	//equality operator non const vs non const
	type_print(beg == end);
	type_print(beg != end);
	type_print(beg > end);
	type_print(beg < end);
	type_print(beg >= end);
	type_print(beg <= end);


	type_print(end == beg);
	type_print(end != beg);
	type_print(end > beg);
	type_print(end < beg);
	type_print(end >= beg);
	type_print(end <= beg);



	//addition / subtraction
	type_print(*(end - 5));
	type_print(*beg++);
	type_print(*const_beg++);
	type_print(*beg);
	*(beg -1) = 42;
	type_print(*const_beg);
	type_print(*--beg);
	type_print(*--const_beg);
	type_print(*end);
	type_print(*(const_beg + 1));
	type_print(*(1 + const_beg + 1));
	type_print(*(1 + const_beg));
	type_print(end - const_beg);
	type_print(const_end - const_beg - 3);
	type_print(const_end - const_beg + 32);
	*(beg + 4) = 999;
	beg += 4;
	type_print(*beg);
	beg[const_end - const_beg] = 222;
	type_print(beg[const_end - const_beg]);


	//OTHER

	beg++;
	const_end--;

	//equality operators const vs non const:
	type_print(beg == const_beg);
	type_print(beg != const_beg);
	type_print(beg > const_beg);
	type_print(beg < const_beg);
	type_print(beg >= const_beg);
	type_print(beg <= const_beg);


	type_print(end == const_end);
	type_print(end != const_end);
	type_print(end > const_end);
	type_print(end < const_end);
	type_print(end >= const_end);
	type_print(end <= const_end);


	type_print(beg == const_end);
	type_print(beg != const_end);
	type_print(beg > const_end);
	type_print(beg < const_end);
	type_print(beg >= const_end);
	type_print(beg <= const_end);


	type_print(end == const_beg);
	type_print(end != const_beg);
	type_print(end > const_beg);
	type_print(end < const_beg);
	type_print(end >= const_beg);
	type_print(end <= const_beg);

	//equality operator non const vs non const
	type_print(beg == end);
	type_print(beg != end);
	type_print(beg > end);
	type_print(beg < end);
	type_print(beg >= end);
	type_print(beg <= end);


	type_print(end == beg);
	type_print(end != beg);
	type_print(end > beg);
	type_print(end < beg);
	type_print(end >= beg);
	type_print(end <= beg);



	//addition / subtraction
	type_print(*(end - 5));
	type_print(*beg++);
	type_print(*const_beg++);
	type_print(*beg);
	*(beg -1) = 42;
	type_print(*const_beg);
	type_print(*--beg);
	type_print(*--const_beg);
	type_print(*end);
	type_print(*(const_beg + 1));
	type_print(*(1 + const_beg + 1));
	type_print(*(1 + const_beg));
	type_print(end - const_beg);
	type_print(const_end - const_beg - 3);
	type_print(const_end - const_beg + 32);
	*(beg + 4) = 999;
	beg += 4;
	type_print(*beg);
	beg[const_end - const_beg] = 222;
	type_print(beg[const_end - const_beg]);

	/********************* REVERSE ***************************/
	vector<std::string> test;
	test.push_back("q");
	test.push_back("w");
	test.push_back("e");
	test.push_back("r");
	test.push_back("t");
	test.push_back("y");
	test.push_back("u");
	test.push_back("i");
	test.push_back("o");
	test.push_back("p");
	test.push_back("[");
	test.push_back("]");
	test.push_back("a");
	test.push_back("s");
	test.push_back("d");
	test.push_back("f");
	test.push_back("g");
	test.push_back("h");
	test.push_back("j");
	test.push_back("k");
	test.push_back("l");
	test.push_back(";");
	test.push_back("z");
	test.push_back("x");
	test.push_back("c");
	test.push_back("v");
	test.push_back("b");
	test.push_back("n");
	test.push_back("m");
	test.push_back(",");
	test.push_back(".");
	print_vector(test);
	vector<std::string>::reverse_iterator start = test.rbegin();
	while (start++ != test.rend())
		std::cout << *start;
	std::cout << std::endl;
	type_print(*(--test.rend()));

}