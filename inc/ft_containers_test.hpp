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
#include <stdlib.h>
#include <iterator>
#include <sys/time.h>


#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
#define COUNT (MAX_RAM / (int)sizeof(Buffer))



struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

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
void print_set(T& test) {
	typename T::iterator it = test.begin();
	while (it != test.end()) {
		std::cout << "val " << *it << std::endl;
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

template<typename T>
class LeakTest {
public:
	T i;
	T *a;
	LeakTest() {
		a = new T;
	}
	LeakTest(const LeakTest& t): i(t.i) {
		a = new T;
		*a = *t.a;
		(void) t;
	}
	LeakTest(T ii) : i(ii){
		a = new T;
		*a = ii;
	}

	LeakTest &operator=(const LeakTest& other) {
		if (&other != this) {
			delete a;
			a = new T;
			*a = *other.a;
			i = other.i;
		}
		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const LeakTest &test) {
		os << test.i;
		return os;
	}

	virtual ~LeakTest() {
		delete a;
	}
};

double print_used_time(struct timeval& begin);

/******************************************************************/
/************************ VECTOR **********************************/
/******************************************************************/

void random_access_iterator_test();
void constructor_destructor_test();
void capacity_test();
void access_test();
void modifiers_test();
void vector_benchmark();
double run_vector_tests(bool run_benchmark);


/*****************************************************************/
/************************ STACK **********************************/
/*****************************************************************/

void stack_test();
void stack_bench();
double run_stack_tests(bool run_benchmark);

/*****************************************************************/
/************************ MAP   **********************************/
/*****************************************************************/

double  run_map_tests(bool run_benchmark);
void map_iter();
void map_access();
void map_constructors();
void map_leaks();
void map_modifiers_tests();
void map_operations();
void map_bench();

/*****************************************************************/
/************************ SET   **********************************/
/*****************************************************************/

double  run_set_tests(bool run_benchmark);
void set_iter();
void set_constructors();
void set_modifiers_tests();
void set_operations();
void set_bench();



double subject_test(const char* arg);

#endif //FT_CONTAINER_FT_CONTAINERS_TEST_HPP
