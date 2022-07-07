//
// Created by amyroshn on 06/07/22.
//

#include "../../inc/ft_containers_test.hpp"

using namespace ft;

void map_iter() {
	map<const int, int> test;
	print_map_size(test);
	for (int i = 0; i < 11; i++) {
		test.insert(make_pair(i, i * 2));
	}
	print_map_size(test);
	print_map(test);
	map<const int, int>::iterator it = test.begin();
	map<const int, int>::const_iterator itc = test.begin();
	map<const int, int>::reverse_iterator rit(test.rbegin());
	map<const int, int>::const_reverse_iterator ritc(test.rbegin());
	std::cout << "it" << std::endl;
	pair_print(*it);
	it++;
	pair_print(*it);
	++it;
	pair_print(*it);
	it--;
	pair_print(*it);
	--it;
	pair_print(*it);

	std::cout << "rit" << std::endl;

	pair_print(*rit);
	rit++;
	pair_print(*rit);
	++rit;
	pair_print(*rit);
	rit--;
	pair_print(*rit);
	--rit;
	pair_print(*rit);

	std::cout << "ritc" << std::endl;
	pair_print(*ritc);
	ritc++;
	pair_print(*ritc);
	++ritc;
	pair_print(*ritc);
	ritc--;
	pair_print(*ritc);
	--ritc;
	pair_print(*ritc);

	std::cout << "itc" << std::endl;

	pair_print(*itc);
	itc++;
	pair_print(*itc);
	++itc;
	pair_print(*itc);
	itc--;
	pair_print(*itc);
	--itc;
	pair_print(*itc);

	while (it != test.end())
		pair_print(*it++);
	while (rit != test.rend())
		pair_print(*rit++);
	while (ritc != test.rend())
		pair_print(*ritc++);
	while (itc != test.end())
		pair_print(*itc++);
	print_map_size(test);
}

void map_access() {
	map<const std::string, int> test;
	print_map_size(test);
	test["cheese"] = 1;
	test["banana"] = 2;
	test["grape"] = 3;
	test["mangue"] = 4;
	test["coco"] = 5;
	test["orange"] = 6;
	test["fraise"] = 7;
	test["cerise"] = 8;
	print_map(test);
}

void map_leaks() {
	map<const int, LeakTest> test;
	for (int i = 0; i < 10000; i++) {
		LeakTest a(i);
		test.insert(make_pair(i, a));
	}
	print_map_size(test);
}

void map_iter_cap_access() {
	//map_iter();
	//map_access();
	//map_leaks();
	map<const int, int> test;
	for (int i = 1; i < 10000000; i++) {
		test.insert(make_pair(i,i));
		if (i % 500 == 0)
			test.erase(test.begin(), test.end());
	}
}