//
// Created by amyroshn on 19/06/22.
//

#ifndef FT_CONTAINER_FT_CONTAINERS_TEST_HPP
#define FT_CONTAINER_FT_CONTAINERS_TEST_HPP
#include "../vector.hpp"
#include "../stack.hpp"
#include "../set.hpp"
#include "../map.hpp"
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <iostream>
#include <string>
#include <list>
#include <deque>

template <typename T>
void type_print(T t) {
	std::cout << t << std::endl;
}

template <typename T>
void pair_print(T& it) {
	std::cout << "Key: " << it.first << ", val " << it.second << std::endl;
}


template <typename T>
void print_map_size(T& c) {
	std::cout << "Size: " << c.size() << std::endl;
	std::cout << "Max size: " << c.max_size() << std::endl;
}

template <typename T>
void print_map(T& test) {
	typename T::iterator it = test.begin();
	while (it != test.end()) {
		std::cout << "Key: " << it->first << ", val " << it->second << std::endl;
		it++;
	}
	print_map_size(test);
}

template <typename T>
void print_vector_size(T& c) {
	std::cout << "Size: " << c.size() << std::endl;
	std::cout << "Capacity: " << c.capacity() << std::endl;
	std::cout << "Max size: " << c.max_size() << std::endl;
}

template <class T>
void print_vector(T& test) {
	typename T::iterator it1 = test.begin();
	while (it1 != test.end()) {
		std::cout << "Val: " << *it1 << std::endl;
		it1++;
	}
	print_vector_size(test);
}

class LeakTest {
public:
	int i;
	int *a;
	LeakTest() {
		a = new int;
		*a = 42;
	}
	LeakTest(const LeakTest& t) {
		a = new int;
		*a = *t.a;
		(void) t;
	}
	LeakTest(int ii) : i(ii){
		a = new int;
		*a = ii;
	}

	LeakTest &operator=(const LeakTest& other) {
		if (&other != this) {
			delete a;
			a = new int;
			*a = *other.a;
		}
		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const LeakTest &test) {
		os << *test.a;
		return os;
	}

	virtual ~LeakTest() {
		delete a;
	}
};

/******************************************************************/
/************************ VECTOR **********************************/
/******************************************************************/

void random_access_iterator_test();
void constructor_destructor_test();
void capacity_test();
void access_test();
void modifiers_test();
void vector_benchmark();


void stack_test();
void stack_bench();

void map_iter_cap_access();


#endif //FT_CONTAINER_FT_CONTAINERS_TEST_HPP
