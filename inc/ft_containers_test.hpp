//
// Created by amyroshn on 19/06/22.
//

#ifndef FT_CONTAINER_FT_CONTAINERS_TEST_HPP
#define FT_CONTAINER_FT_CONTAINERS_TEST_HPP
#include "containers/vector.hpp"
#include <vector>
#include <iostream>

template <typename T>
void test_print(T t) {
	std::cout << t << std::endl;
}

template <typename T>
void test_vector_print(T& t) {
	std::cout << "size " << t.size() << " capacity " << t.capacity() << std::endl;
	for (typename T::iterator it = t.begin(); it != t.end(); it++)
		std::cout << *it << std::endl;
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


#endif //FT_CONTAINER_FT_CONTAINERS_TEST_HPP
